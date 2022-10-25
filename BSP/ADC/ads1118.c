/*************
 �౾����
ADS1118�������ļ�

 2018.2.10
**************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"

#include "BSP/ADC/ads1118.h"



//*********************ȫ�ֱ���********************

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
*   ��  ��  ��: ADS1118_Configure
*   ����˵��: ads1118 �Ĵ��������ú���
*   ��ڲ���: none
*   ��  ��  ֵ: none
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
*   ��  ��  ��: ADS1118_DataGet
*   ����˵��: �ôӼĴ����ж�ȡ��ԭʼ.
*   ��ڲ���: none
*   ��  ��  ֵ: none
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
*   ��  ��  ��: ADS1118_DataGetFloat
*   ����˵��: ����ø�����
*   ��ڲ���: DataReadBuffer�ĵ�ֵַ
*   ��  ��  ֵ: none
*************************************************************
*/
void ADS1118_DataGet(float *pfDataValue)
{
    uint16_t ui16DataBuffer = 0;

    ADS1118_DataGetRaw( &ui16DataBuffer );

    *pfDataValue = ( ((float)( (int16_t)ui16DataBuffer ))*g_fADS1118VoltageFactors[ui16RangeConvert] / 1000.0 );
}









