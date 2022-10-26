/*
 * key.c
 *
 *  Created on: 2018��2��4��
 *      Author: �౾
 */

#include "key.h"

int SW4_count=0,SW0_count=0;


//�жϷ������
static void IntHandler_GPIOF(void)
{
    uint32_t IntStatus;
    IntStatus=GPIOIntStatus(GPIO_PORTF_BASE,true);
    GPIOIntClear(GPIO_PORTF_BASE,IntStatus);
    if((IntStatus & GPIO_PIN_0|GPIO_PIN_4) == GPIO_PIN_0)
    {
        SW0_count++;
        GPIOIntDisable(GPIO_PORTF_BASE,GPIO_INT_PIN_0|GPIO_INT_PIN_4);
    }
    else if((IntStatus & GPIO_PIN_0|GPIO_PIN_4) == GPIO_PIN_4)
    {
        SW4_count++;
        GPIOIntDisable(GPIO_PORTF_BASE,GPIO_INT_PIN_0|GPIO_INT_PIN_4);
    }
    else if((IntStatus & GPIO_PIN_0|GPIO_PIN_4) == GPIO_PIN_0|GPIO_PIN_4)
    {
        SW0_count++;
        SW4_count++;
        GPIOIntDisable(GPIO_PORTF_BASE,GPIO_INT_PIN_0|GPIO_INT_PIN_4);
    }
}
/*
*************************************************************
*   ��  ��  ��: KeyConfigure
*   ����˵��: ������ʼ������
*   ��ڲ���: none
*   ��  ��  ֵ: none
*************************************************************
*/
void KeyConfigure(int mode)
{
	//ʹ�����衪��GPIOF
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//����PF0
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE+GPIO_O_CR)=GPIO_PIN_0;
	//����GPIO_PF0|GPIO_PF4Ϊ���벢�������Եȴ���������
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4,
						GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	if(mode==1)
	{
	    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_INT_PIN_0);
	    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_INT_PIN_4);
	    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4,GPIO_FALLING_EDGE);
	    GPIOIntRegister(GPIO_PORTF_BASE,IntHandler_GPIOF);
	    IntEnable(INT_GPIOF);
	}
}


/*
*************************************************************
*   ��  ��  ��: KeyScan
*   ����˵��: ������⺯��
*   ��ڲ���: PF=0 -->PF0;PF=4 -->PF4
*   ��  ��  ֵ: true-->��������
*************************************************************
*/
void KeyScan()
{
	uint8_t ReadPin;
    ReadPin=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
    if(ReadPin!=(GPIO_PIN_4|GPIO_PIN_0))
    {
        //��ʱ20ms������
        SysCtlDelay(8*(SysCtlClockGet()/3000));
        ReadPin=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
        if(ReadPin!=(GPIO_PIN_4|GPIO_PIN_0))
        {
            switch(ReadPin)
            {
                case GPIO_PIN_4 : SW4_count++;break;
                case GPIO_PIN_0 : SW0_count++;break;
                case     0      : SW4_count++;
                                  SW0_count++;break;
            }
        }
        //̧����
        while(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
        {
        }
    }
}

