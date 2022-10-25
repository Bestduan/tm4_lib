//*****************************************************************************
//�ļ�����ADS1115.c
//�ļ����ܣ����ٸ߾���12λ4·AD����������
//Joye.
//2017.7.16
//*****************************************************************************
#include "BSP/ADC/ads1115.h"

char Channel_Value;			//ͨ������
short D_ADS; 		//ת����������
unsigned int Config;			//���ò���
unsigned char Writebuff[4],Readbuff[3];			//���ͻ�����
unsigned char Result[2]; 				//���ܻ�����

//******************************************
//�������ƣ�ADS1115_IO_Init
//�������ܣ���ʼ��GPIO��
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_IO_Init(void)
{	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);									//ʹ��GPIOD
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);						//SCL-->PD.0�˿�����
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0,									//2mA���������
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);						//SDA-->PD.2�˿�����
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2,									//2mA���������
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
}

//******************************************
//�������ƣ�ADS1115_SDAPort_In
//�������ܣ���SDA������Ϊ����
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_SDAPort_In(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);							//ʹ��GPIOD
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);						//SDA-->PD.3�˿�����
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2,							//2mA����������
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);		
}

//******************************************
//�������ƣ�ADS1115_SDAPort_Out
//�������ܣ���SDA������Ϊ���
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_SDAPort_Out(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);							//ʹ��GPIOD
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);						//SDA-->PD.2�˿�����
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2,							//2mA���������
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
}

//******************************************
//�������ƣ�ADS1115_I2C_Start
//�������ܣ�����I2C�����ź�
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_I2C_Start(void)
{
	ADS1115_SCL_SET;       //SCL=1;
	ADS1115_SDA_SET;       //SDA=1;
	delay_us(15);
	ADS1115_SDA_CLR;       //SDA=0;
	delay_us(15);
	ADS1115_SCL_CLR;       //SCL=0;
	delay_us(15);
}

//******************************************
//�������ƣ�ADS1115_I2C_Stop
//�������ܣ�����I2Cֹͣ�ź�
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_I2C_Stop(void)
{ 
    ADS1115_SDA_CLR;       //SDA=0;
    delay_us(15);
    ADS1115_SCL_SET;       //SCL=1;
    delay_us(15);
    ADS1115_SDA_SET;       //SDA=1;
    delay_us(15);
}

//******************************************
//�������ƣ�ADS1115_I2C_Ack
//�������ܣ�����I2C��Ӧ�ź�
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_I2C_Ack(void)
{
    ADS1115_SDA_CLR;       //SDA=0;
    delay_us(1);
    ADS1115_SCL_SET;       //SCL=1;
    delay_us(15);
    ADS1115_SCL_CLR;       //SCL=0;
    delay_us(1);
    ADS1115_SDA_SET;       //SDA=1;
    delay_us(15);
}

//******************************************
//�������ƣ�ADS1115_I2C_Nack
//�������ܣ�����I2C��Ӧ���ź�
//��    ������
//����ֵ��  ��
//******************************************
void ADS1115_I2C_Nack(void)
{
		ADS1115_SDA_SET;       //SDA=1;
		delay_us(1);
		ADS1115_SCL_SET;       //SCL=1;
		delay_us(15);
		ADS1115_SCL_CLR;       //SCL=0;
		delay_us(1);
		ADS1115_SDA_CLR;       //SDA=0;   
		delay_us(15);
}

//******************************************
//�������ƣ�ADS1115_I2C_Check
//�������ܣ����I2CӦ���ź�
//��    ������
//����ֵ��  TRUE (1)--�ӻ�Ӧ��
//					FALSE(0)--�ӻ���Ӧ��
//******************************************
unsigned char ADS1115_I2C_Check(void)
{
    unsigned char slaveack;
    
    ADS1115_SDA_SET;       //SDA=1;
    delay_us(1);
    ADS1115_SCL_SET;       //SCL=1;
    ADS1115_SDAPort_In(); //Set SDA port as input.
    delay_us(15);
    slaveack = ADS1115_SDA_IN;   //Read the status of SDA port.
    ADS1115_SCL_CLR;       //SCL=0;
    delay_us(15);
		ADS1115_SDAPort_Out();	//Set SDA port as output.
	
    if(slaveack)    return FALSE;
    else            return TRUE;
}

//******************************************
//�������ƣ�ADS1115_Write_1_Byte
//�������ܣ�����һ���ֽ�
//��    ����Ҫ���͵��ֽ�
//����ֵ��  TRUE (1)--�ӻ�Ӧ��
//					FALSE(0)--�ӻ���Ӧ��
//******************************************
void ADS1115_Write_1_Byte(unsigned char DataByte)
{
	int i;

	for(i=0;i<8;i++)
	{
		if(DataByte&0x80)  //if((DataByte<<i)&0x80)
		  ADS1115_SDA_SET;       //SDA=1;
		else
			ADS1115_SDA_CLR;       //SDA=0;
		    delay_us(15);
			ADS1115_SCL_SET;         //SCL=1;
			delay_us(15);
			ADS1115_SCL_CLR;         //SCL=0;
			delay_us(15);
			DataByte <<= 1;
	}
		ADS1115_SDA_SET;             //SDA=1;
		delay_us(1);
}

//******************************************
//�������ƣ�ADS1115_Write_N_Byte
//�������ܣ����Ͷ���ֽ�
//��    ����*writebuffer--ָ�������ݵ�ָ��
//                	 num--�ֽ���
//����ֵ��  TRUE (1)--�ӻ�Ӧ��
//					FALSE(0)--�ӻ���Ӧ��
//******************************************
unsigned char ADS1115_Write_N_Byte(unsigned char *writebuffer,unsigned char num)
{
	int i;

	for(i=0;i<num;i++)
	{
		ADS1115_Write_1_Byte(*writebuffer);
		if(ADS1115_I2C_Check())
		{
			writebuffer ++;
		}
		else
		{
			ADS1115_I2C_Stop();
		    return FALSE;
		}
	}
	ADS1115_I2C_Stop();
	return TRUE;
}

//******************************************
//�������ƣ�ADS1115_Read_1_Byte
//�������ܣ�����һ���ֽ�
//��    ����None
//����ֵ��  data_Value -- �����յ��ֽ�
//******************************************
unsigned char ADS1115_Read_1_Byte(void)
{
    unsigned char data_Value = 0, FLAG, i;
	
    for(i=0;i<8;i++)
    { 
        
        ADS1115_SDA_SET;         //SDA=1;
        delay_us(15);
        ADS1115_SCL_SET;         //SCL=1;
        ADS1115_SDAPort_In();	 //Set SDA port as input.
        delay_us(15);
        FLAG=ADS1115_SDA_IN;
        data_Value <<= 1;
	    if(FLAG)
            data_Value |= 0x01;

        ADS1115_SCL_CLR;         //SCL=0;
        delay_us(15);
        ADS1115_SDAPort_Out();	 //Set SDA port as output.
    }
    return data_Value;
}

//******************************************
//�������ƣ�ADS1115_Read_N_Byte
//�������ܣ����ն���ֽ�
//��    ���� *readbuff -- ָ���Ž������ݵ������ָ��
//����ֵ��  data_Value -- �����յ�����
//******************************************
void ADS1115_Read_N_Byte(unsigned char*readbuff, unsigned char num)
{
	unsigned char i;
	
	for(i=0;i<num;i++)
	{
		readbuff[i]=ADS1115_Read_1_Byte();
		if(i==num-1)
			ADS1115_I2C_Nack();  //read bytes uncontinously
		else 
			ADS1115_I2C_Ack();   //read bytes continously
	}
	ADS1115_I2C_Stop();

}

//******************************************
//�������ƣ�ADS1115_Init
//�������ܣ���ʼ��ADS1115
//��    ���� S_MUX_0,S_MUX_1  --  ��ͬ����ͨ�����
//����ֵ��  ��
//******************************************
void ADS1115_Init(u8 S_MUX_0, u8 S_MUX_1)
{

	
	if (S_MUX_0 == 0 && S_MUX_1 == 0)
	Config = OS+MUX_A0+PGA+DR+COMP_QUE+MODE;
	if (S_MUX_0 == 0 && S_MUX_1 == 1) 
	Config = OS+MUX_A1+PGA+DR+COMP_QUE+MODE;
	if (S_MUX_0 == 1 && S_MUX_1 == 0)
	Config = OS+MUX_A2+PGA+DR+COMP_QUE+MODE;
	if (S_MUX_0 == 1 && S_MUX_1 == 1)
	Config = OS+MUX_A3+PGA+DR+COMP_QUE+MODE;
    
    Writebuff[0]=ADDRESS_W;
    Writebuff[1]=Pointer_1;
    Writebuff[2]=Config/256;
    Writebuff[3]=Config%256;
        
    Readbuff[0]=ADDRESS_W;
    Readbuff[1]=Pointer_0;
        
    Readbuff[2]=ADDRESS_R;
}

//******************************************
//�������ƣ�ADS1115_WriteWord
//�������ܣ���������Writebuff�е����ݷ��ͳ�ȥ
//��    ���� ��
//����ֵ��   ��
//******************************************
void ADS1115_WriteWord(void)
{
     int t;
     ADS1115_I2C_Start();   
     do
     {
          t=ADS1115_Write_N_Byte(Writebuff,4);
     }while(t==0);                                  //Write 4 bytes in Writebuff to ADS1115.
}

//******************************************
//�������ƣ�ADS1115_ReadWord
//�������ܣ��������ݲ�������Readbuff��
//��    ���� ��
//����ֵ��   ��
//******************************************
void ADS1115_ReadWord(void)
{
    int t;
    ADS1115_I2C_Start();                           //Write 2 bytes.
    do
    {
      t=ADS1115_Write_N_Byte(Readbuff,2);
    }while(t==0);

    ADS1115_I2C_Start();                           //Write 2 bytes.
    do
    {
      t=ADS1115_Write_N_Byte(&Readbuff[2],1);
    }while(t==0);
    
    ADS1115_Read_N_Byte(Result,2);                 //Read 2 bytes.

}

//******************************************
//�������ƣ�ADS1115_Getdata
//�������ܣ���ȡ��������ĵ�ѹֵ
//��    ����Channel --ͨ����� 
//����ֵ��  short D_ADS -- ��ȡ��������
//******************************************
short ADS1115_Getdata(u8 Channel)
{
	u8 S_MUX_0, S_MUX_1;

	switch(Channel)
	{
		case 0:
			S_MUX_0 = 0;
			S_MUX_1 = 0;
			Channel_Value = Channel + '0';
			break;
		case 1:
			S_MUX_0 = 0;
			S_MUX_1 = 1;
			Channel_Value = Channel + '0';
			break;
		case 2:
			S_MUX_0 = 1;
			S_MUX_1 = 0;
			Channel_Value = Channel + '0';
			break;
		case 3:
			S_MUX_0 = 1;
			S_MUX_1 = 1;
			Channel_Value = Channel + '0';
			break;
		default :
			break;
	}
//    AD_START;
	delay_us(1);
    ADS1115_Init(S_MUX_0, S_MUX_1);
    ADS1115_WriteWord();
    delay_us(1);
    ADS1115_ReadWord();
    delay_us(1);
//		AD_END;
    D_ADS=Result[0]*256+Result[1];  //ת����������

  	return D_ADS;
}





