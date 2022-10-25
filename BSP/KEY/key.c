/*
 * key.c
 *
 *  Created on: 2018年2月4日
 *      Author: 坂本
 */

#include "BSP/KEY/key.h"

int SW4_count=0,SW0_count=0;


//中断服务程序
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
*   函  数  名: KeyConfigure
*   功能说明: 按键初始化函数
*   入口参数: none
*   返  回  值: none
*************************************************************
*/
void KeyConfigure(int mode)
{
	//使能外设——GPIOF
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//解锁PF0
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE+GPIO_O_CR)=GPIO_PIN_0;
	//设置GPIO_PF0|GPIO_PF4为输入并弱上拉以等待按键按下
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
*   函  数  名: KeyScan
*   功能说明: 按键检测函数
*   入口参数: PF=0 -->PF0;PF=4 -->PF4
*   返  回  值: true-->按键按下
*************************************************************
*/
void KeyScan()
{
	uint8_t ReadPin;
    ReadPin=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
    if(ReadPin!=(GPIO_PIN_4|GPIO_PIN_0))
    {
        //延时20ms，消抖
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
        //抬起检测
        while(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
        {
        }
    }
}

