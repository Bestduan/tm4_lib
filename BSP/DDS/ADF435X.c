#include "BSP/DDS/ADF435X.h"

//sbit CLK=P2^5;
//sbit LE=P2^2;
//sbit DATA=P1^2;

#define R0 0X2C0000
#define R1 0X800E1A9
#define R2 0x1B004E42
#define R3 0X4B3
#define R4 0XCC803C
#define R5 0X580005
unsigned long R4_V;
//Function that writes to the ADF435x via the SPI port.
//--------------------------------------------------------------------------------


/***************************************************************************
Function name     :ADF435X_IO_Init
Function use      :Init the using IO ports of ADF435X
Function parameter:None
Function return   :None
***************************************************************************/
void ADF435X_IO_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);                      //浣胯兘GPIOA

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);               //SDIO--B2
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2,                     //2mA寮变笂鎷夎緭鍑�
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0);               //SCLK--B0
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0,                     //2mA寮变笂鎷夎緭鍑�
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);               //LE--B5
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_5,                     //2mA寮变笂鎷夎緭鍑�
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}



/***************************************************************************
Function name     :ADF435X_W_SPI
Function use      :Use SPI to write 32 bits data to ADF435X
Function parameter:ulong BUF--------------The 32 bits of data you want to write to ADF435X
Function return   :None
***************************************************************************/
void ADF435X_W_SPI(ulong BUF)
{
    unsigned char j = 0;
    unsigned long ValueToWrite = 0;
    ValueToWrite =BUF;
    ADF435X_SCLK_RESET;    //CLK=0;
    ADF435X_LE_RESET;      //LE=0;
    for(j=0; j<32; j++)
    {
        if(0x80000000 == (ValueToWrite & 0x80000000))
        {
            ADF435X_SDIO_SET;    //Send one to SDO pin
        }               
        else
        {
            ADF435X_SDIO_RESET;    ////Send zero to SDO pin
        }                  
       ADF435X_SCLK_SET;
       ValueToWrite <<= 1; //Rotate data
       ADF435X_SCLK_RESET;
    }
    ADF435X_SCLK_RESET;    //CLK=0;
    ADF435X_LE_SET;        //LE=1;
    ADF435X_LE_RESET;      //LE=0;
}


/***************************************************************************
Function name     :ADF435X_W_Freq
Function use      :Write frequence ADF435X
Function parameter:ulong Freq-------------The Frequence
Function return   :None
***************************************************************************/
void  ADF435X_W_Freq(ulong Freq)	 
{
    float Freq_temp=1.0;
    unsigned long 	INT,FRAC,MODE=1000;
    unsigned long   R0_temp=0;
    unsigned long   R4_temp=0;
    unsigned long   Out_Divider,RF_Divider;
    if((34375<=Freq)&&(Freq<68750))  {Out_Divider=6;RF_Divider=64;}
    if((68750<=Freq)&&(Freq<137500)) {Out_Divider=5;RF_Divider=32;}
    if((137500<=Freq)&&(Freq<275000)){Out_Divider=4;RF_Divider=16;}
    if((275000<=Freq)&&(Freq<550000)){Out_Divider=3;RF_Divider=8;}
    if((550000<=Freq)&&(Freq<1100000)){Out_Divider=2;RF_Divider=4;}
    if((1100000<=Freq)&&(Freq<2200000)){Out_Divider=1;RF_Divider=2;}
    if((2200000<=Freq)&&(Freq<4400000)){Out_Divider=0;RF_Divider=1;}

    R4_temp=((R4_V&0XFF8FFFFF)|(Out_Divider<<20));
    ADF435X_W_SPI(R4_temp);
 
    //Freq_temp=Freq;
    Freq_temp=(float)Freq*(float)RF_Divider/10000.0;
    INT  = (int)Freq_temp;
	FRAC = (Freq_temp-(float)INT)*(float)MODE;
    R0_temp=((INT<<15)|(FRAC<<3))&0x7fffff8;
    ADF435X_W_SPI(R0_temp);
    R4_V=R4_temp;
}


/***************************************************************************
Function name     :ADF435X_W_Amp
Function use      :Write amplitude to ADF435X
Function parameter:uchar  Amp--------------The Amplitude
Function return   :None
***************************************************************************/
void ADF435X_W_Amp(uchar Amp)
{
    unsigned long Amp_temp,R4_temp;
    Amp_temp= Amp;
    R4_temp=((R4_V&0XFFFFFFE7)|(Amp_temp<<3));
    ADF435X_W_SPI(R4_temp);
    R4_V=R4_temp;
}


/***************************************************************************
Function name     :ADF4350_Init
Function use      :Init the ADF4350
Function parameter:None
Function return   :None
***************************************************************************/
void ADF4350_Init(void)
{ 
    ADF435X_W_SPI(R0);
    ADF435X_W_SPI(R1);
    ADF435X_W_SPI(R2);
    ADF435X_W_SPI(R3);
    ADF435X_W_SPI(R4);
    ADF435X_W_SPI(R5);   
 
    ADF435X_W_SPI(R0);
    ADF435X_W_SPI(R1);
    ADF435X_W_SPI(R2);
    ADF435X_W_SPI(R3);
    ADF435X_W_SPI(R4);
    ADF435X_W_SPI(R5);

    R4_V=R4;
}

/***************************************************************************
Function name     :ADF4351_Init
Function use      :Init the ADF4351
Function parameter:None
Function return   :None
***************************************************************************/
void ADF4351_Init(void)
{ 
    ADF435X_W_SPI(R5);
    delay_us(50);
    ADF435X_W_SPI(R4);
    delay_us(50);
    ADF435X_W_SPI(R3);
    delay_us(50);
    ADF435X_W_SPI(R2);
    delay_us(50);
    ADF435X_W_SPI(R1);
    delay_us(50);
    ADF435X_W_SPI(R0);   
    delay_ms(2);
    ADF435X_W_SPI(R5);
    delay_us(50);
    ADF435X_W_SPI(R4);
    delay_us(50);
    ADF435X_W_SPI(R3);
    delay_us(50);
    ADF435X_W_SPI(R2);
    delay_us(50);
    ADF435X_W_SPI(R1);
    delay_us(50);
    ADF435X_W_SPI(R0);
    delay_us(50);

    R4_V=R4;
}
