#include "dac8811.h"

/*******************************************
�������ƣ�Dac7811__IO_Init
��    �ܣ���ʼ��SPI��������
��    ������
����ֵ  ����
********************************************/
void DAC8811_IO_Init()        //DAC7811 SPI��ʼ��
{
  //Init GPIOM
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
  // Check if the peripheral access is enabled.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM))
	{
	}	
	GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
	
	GPIOPadConfigSet(GPIO_PORTM_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

/*******************************************
�������ƣ�DAC_Conver
��    �ܣ���һ��16λ����������������Ӧ
��    ����temp-16λ����������
����ֵ  ����
********************************************/

void DAC8811_Transform(uint16_t temp)
{
        uint8_t i;
        DAC8811_CLK_CLR;
        delay_us(1);
        DAC8811_CS_CLR;     //����Ƭѡ���������ݴ���
        delay_us(1);   
        for(i=0;i<16;i++)
        {
        	if(temp & 0x8000) {DAC8811_SDA_SET;} //�������λΪ0���õ������ߣ���������
            else  {DAC8811_SDA_CLR;}
            DAC8811_CLK_SET;
            delay_us(1);
            temp<<=1;
            delay_us(1);
            DAC8811_CLK_CLR;        //�����ض�ȡ����
        }
        DAC8811_CS_SET;
        delay_us(1);
        DAC8811_CLK_SET; 
}

/*******************************************
�������ƣ� VoltOfData
��    �ܣ���ģ���ѹֵת��Ϊ16λ��������
��    ����out_volt-ģ���ѹֵ
����ֵ  ��16λ��������
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
********************************************/
uint16_t VoltOfData(float out_volt) //˵��refΪ�ο�Դ��out_voltΪ���ģ���ѹֵ
{ 
   int temp2;
   temp2=(unsigned int)(out_volt*10700+32768);
   return(temp2&0xffff);
}//����ѹֵת��Ϊ��Ӧ��16λ����������

/*******************************************
�������ƣ� Write_Data
��    �ܣ���ͨ��д����
��    ����out_volt-ģ���ѹֵ
����ֵ  ����
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
        //0xc000|  ǰ�����4λΪ1100������λ��������ģʽ���������ģ�д���ݵ�Aͨ��
********************************************/
void Write_Data(float out_volt)
{
   int Data;
   Data=VoltOfData(out_volt);
   DAC8811_Transform(Data);
}

/*******************************************
Function name              :ADS1115_DemoTask
Function use               :Run the AD9959 to set Frequency of channel 2,3
Function parameter         :None
Function return            :None
********************************************/
void DAC8811_DemoTask(float DAC8811Value)
{	
	DAC8811_IO_Init();
	Write_Data(DAC8811Value);
}

