#include "dac5618.h"

/*******************************************
Function name              :TLV5618_SDAPort_In
Function use               :Set SDA port as input.
Function parameter         :None
Function return            :None
********************************************/
void TLV5618_Port_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
}

/*******************************************
�������ƣ�TLV5618_Init
��    �ܣ���ʼ��SPI����
��    ������
����ֵ  ����
********************************************/
void TLV5618_Init(void)      //DAC5618  SPI��ʼ��
{
    TLV5618_CS_HIGH;         //����Ƭѡ
    delay_us(3);
    TLV5618_SCL_SET;         //����ʱ����
    delay_us(3);             //����ʱ
    TLV5618_SDA_CLR;         //�õ�������
    delay_us(3);
}
/*******************************************
�������ƣ�DAC_Conver
��    �ܣ���һ��16λ����������������Ӧ
��    ����temp-16λ����������
����ֵ  ����
********************************************/

void DAC_Conver(uint temp)
{
        unsigned char i;
        TLV5618_Port_Init(); //��������Ϊ���
        TLV5618_CS_LOW;       //����Ƭѡ���������ݴ���
        TLV5618_SCL_SET;
        for(i=0;i<16;i++)
        {
        	if((temp & 0x8000) ==0) 
                {TLV5618_SDA_CLR;} //�������λΪ0���õ������ߣ���������
            else
                {TLV5618_SDA_SET;}
            TLV5618_SCL_CLR;
            delay_us(1);
            temp<<=1;
            TLV5618_SCL_SET;        //�����ض�ȡ����
        }
        TLV5618_CS_HIGH;   //����Ƭѡ���ر����ݴ���
}

/*******************************************
�������ƣ� VoltToData
��    �ܣ���ģ���ѹֵת��Ϊ16λ��������
��    ����out_volt-ģ���ѹֵ
����ֵ  ��16λ��������
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
********************************************/
uint VoltToData(float out_volt) //˵��refΪ�ο�Դ��out_voltΪ���ģ���ѹֵ
{
   int temp2;
   temp2=(unsigned int)((out_volt*4096)/(4*2.048));
   return(temp2&0x0fff);
}//����ѹֵת��Ϊ��Ӧ��12λ����������

/*******************************************
�������ƣ� Write_A
��    �ܣ���Aͨ��д����
��    ����out_volt-ģ���ѹֵ
����ֵ  ����
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
        //0xc000|  ǰ�����4λΪ1100������λ��������ģʽ���������ģ�д���ݵ�Aͨ��
********************************************/
void Write_A(float out_volt)
{
   int Data_A;
   Data_A=0xc000|VoltToData(out_volt);//Aͨ��
   DAC_Conver(Data_A);
}

/*******************************************
�������ƣ� Write_B
��    �ܣ���Aͨ��д����
��    ����out_volt-ģ���ѹֵ
����ֵ  ����
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
        //0xc000|  ǰ�����4λΪ1100������λ��������ģʽ���������ģ�д���ݵ�Aͨ��
********************************************/
void Write_B(float out_volt)
{
   int Data_A;
   Data_A=0x4000|VoltToData(out_volt);//Bͨ��
   DAC_Conver(Data_A);
}

/*******************************************
Function name              :DAC5618_DemoTask
Function use               :Write the voltage to the dac5618
Function parameter         :None
Function return            :None
********************************************/
void DAC5618_VoltageSet(int DAC5618_Channel,float DAC5618Value)
{
    TLV5618_Init();
    if(DAC5618_Channel==1)                  //���Ϊͨ��1����д������
        Write_A(DAC5618Value);
    if(DAC5618_Channel==2)                  //���Ϊͨ��2����д������
        Write_B(DAC5618Value);
}


