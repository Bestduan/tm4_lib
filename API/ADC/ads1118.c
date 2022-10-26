/*************
 坂本制作
ADS1118的配置文件

 2018.2.10
**************/
#include "ads1118.h"



//*********************全局变量********************

uint16_t ui16RangeConvert;

static const float g_fADS1118VoltageFactors[] =
{
    187.5,                              // Range = +/- 6.144V
    125.0,                              // Range = +/- 4.096V
    62.5,                               // Range = +/- 2.048V
    31.25,                              // Range = +/- 1.024V
    15.625,                             // Range = +/- 0.512V
    7.8125,                             // Range = +/- 0.256V
    7.8125,                             // Range = +/- 0.256V
    7.8125                              // Range = +/- 0.256V
};


/*
*************************************************************
*   函  数  名: ADS1118_Configure
*   功能说明: ads1118 寄存器初配置函数
*   入口参数: none
*   返  回  值: none
*************************************************************
*/
void ADS1118_Configure()
{
    SSIDataPut(ADS1118_SSI_BASE,ADS1118_CONFIG_0);
    while(SSIBusy(ADS1118_SSI_BASE));
    ui16RangeConvert = ( ADS1118_CONFIG_0 >> 9 ) & 0x07;
}

/*
*************************************************************
*   函  数  名: ADS1118_DataGet
*   功能说明: 得从寄存器中读取的原始.
*   入口参数: none
*   返  回  值: none
*************************************************************
*/
static void ADS1118_DataGetRaw(uint16_t *pui16DataValue)
{
    uint32_t ui32DataReadBuffer = 0;
    while((SSIDataGetNonBlocking(ADS1118_SSI_BASE,&ui32DataReadBuffer) != 0));

    ui32DataReadBuffer = 0;
    SSIDataPut(ADS1118_SSI_BASE,0xAAAF);
    while(SSIBusy(ADS1118_SSI_BASE));

    SSIDataGet(ADS1118_SSI_BASE,&ui32DataReadBuffer);

    while(SSIBusy(ADS1118_SSI_BASE));

    *pui16DataValue = ui32DataReadBuffer;
}

/*
*************************************************************
*   函  数  名: ADS1118_DataGetFloat
*   功能说明: 计算得浮点数
*   入口参数: DataReadBuffer的地址值
*   返  回  值: none
*************************************************************
*/
void ADS1118_DataGet(float *pfDataValue)
{
    uint16_t ui16DataBuffer = 0;

    ADS1118_DataGetRaw( &ui16DataBuffer );

    *pfDataValue = ( ((float)( (int16_t)ui16DataBuffer ))*g_fADS1118VoltageFactors[ui16RangeConvert] / 1000.0 );
}









