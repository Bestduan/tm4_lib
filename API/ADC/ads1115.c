//*****************************************************************************
//文件名：ADS1115.c
//文件功能：低速高精度12位4路AD驱动函数库
//Joye.
//2017.7.16
//*****************************************************************************
#include "ads1115.h"

char Channel_Value;			//通道编码
short D_ADS; 		//转换的数字量
unsigned int Config;			//配置参数
unsigned char Writebuff[4],Readbuff[3];			//发送缓冲区
unsigned char Result[2]; 				//接受缓冲区

//******************************************
//函数名称：ADS1115_IO_Init
//函数功能：初始化GPIO口
//参    数：无
//返还值：  无
//******************************************
void ADS1115_IO_Init(void)
{	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);									//使能GPIOD
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);						//SCL-->PD.0端口配置
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0,									//2mA弱上拉输出
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);						//SDA-->PD.2端口配置
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2,									//2mA弱上拉输出
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
}

//******************************************
//函数名称：ADS1115_SDAPort_In
//函数功能：将SDA口设置为输入
//参    数：无
//返还值：  无
//******************************************
void ADS1115_SDAPort_In(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);							//使能GPIOD
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);						//SDA-->PD.3端口配置
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2,							//2mA弱上拉输入
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);		
}

//******************************************
//函数名称：ADS1115_SDAPort_Out
//函数功能：将SDA口设置为输出
//参    数：无
//返还值：  无
//******************************************
void ADS1115_SDAPort_Out(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);							//使能GPIOD
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);						//SDA-->PD.2端口配置
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2,							//2mA弱上拉输出
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
}

//******************************************
//函数名称：ADS1115_I2C_Start
//函数功能：发送I2C启动信号
//参    数：无
//返还值：  无
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
//函数名称：ADS1115_I2C_Stop
//函数功能：发送I2C停止信号
//参    数：无
//返还值：  无
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
//函数名称：ADS1115_I2C_Ack
//函数功能：发送I2C响应信号
//参    数：无
//返还值：  无
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
//函数名称：ADS1115_I2C_Nack
//函数功能：发送I2C无应答信号
//参    数：无
//返还值：  无
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
//函数名称：ADS1115_I2C_Check
//函数功能：检测I2C应答信号
//参    数：无
//返还值：  TRUE (1)--从机应答
//					FALSE(0)--从机无应答
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
//函数名称：ADS1115_Write_1_Byte
//函数功能：发送一个字节
//参    数：要发送的字节
//返还值：  TRUE (1)--从机应答
//					FALSE(0)--从机无应答
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
//函数名称：ADS1115_Write_N_Byte
//函数功能：发送多个字节
//参    数：*writebuffer--指向存放内容的指针
//                	 num--字节数
//返还值：  TRUE (1)--从机应答
//					FALSE(0)--从机无应答
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
//函数名称：ADS1115_Read_1_Byte
//函数功能：接收一个字节
//参    数：None
//返还值：  data_Value -- 所接收的字节
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
//函数名称：ADS1115_Read_N_Byte
//函数功能：接收多个字节
//参    数： *readbuff -- 指向存放接收内容的数组的指针
//返还值：  data_Value -- 所接收的内容
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
//函数名称：ADS1115_Init
//函数功能：初始化ADS1115
//参    数： S_MUX_0,S_MUX_1  --  共同决定通道编号
//返还值：  无
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
//函数名称：ADS1115_WriteWord
//函数功能：将储存在Writebuff中的数据发送出去
//参    数： 无
//返还值：   无
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
//函数名称：ADS1115_ReadWord
//函数功能：接收数据并储存在Readbuff中
//参    数： 无
//返还值：   无
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
//函数名称：ADS1115_Getdata
//函数功能：读取单端输入的电压值
//参    数：Channel --通道编号 
//返还值：  short D_ADS -- 读取的数字量
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
    D_ADS=Result[0]*256+Result[1];  //转换的数字量

  	return D_ADS;
}





