/*************
 坂本制作
ADC的配置文件

 2018.2.10
**************/
#include "APIS/ADC_Init.h"

volatile bool  badcflag = false;
uint32_t Ch0Value=0;
uint32_t Ch1Value=0;
//默认均为模块0  序列号0 8次硬件采样    64次采样因子
//对应的端口如下
//Ch0:PE3           Ch1:PE2
//Ch0:PE1           Ch1:PE0    (开发板上没引出)
//Ch0:PD3 (error)   Ch1:PD2
//Ch0:PD1           Ch1:PD0
//Ch0:PE5           Ch1:PE4
//Ch0:PB4           Ch1:PB5
adc_data_t adc_array[6]=
{
    {
        .SYSCTL_PERIPH_ADC=SYSCTL_PERIPH_ADC0,
        .SYSCTL_PERIPH_GPIO_ADC=SYSCTL_PERIPH_GPIOE,
        .GPIO_PORT_ADC_BASE=GPIO_PORTE_BASE,
        .GPIO_PIN_ADC=GPIO_PIN_2 | GPIO_PIN_3,
        .ADC_BASE=ADC0_BASE,
        .INT_ADC=ADC_REF_INT,
        .ADC_CTL_0=ADC_CTL_CH0,
        .ADC_CTL=ADC_CTL_CH1 |ADC_CTL_END | ADC_CTL_IE,
        .ADC_CLK=ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL,
        .ADC_INT_EVENT=INT_ADC0SS0,
        .ADC_MODE=ADC_TRIGGER_PROCESSOR,
    },
    {
        .SYSCTL_PERIPH_ADC=SYSCTL_PERIPH_ADC0,
        .SYSCTL_PERIPH_GPIO_ADC=SYSCTL_PERIPH_GPIOE,
        .GPIO_PORT_ADC_BASE=GPIO_PORTE_BASE,
        .GPIO_PIN_ADC=GPIO_PIN_0 | GPIO_PIN_1,
        .ADC_BASE=ADC0_BASE,
        .INT_ADC=ADC_REF_INT,
        .ADC_CTL_0=ADC_CTL_CH2,
        .ADC_CTL=ADC_CTL_CH3 |ADC_CTL_END | ADC_CTL_IE,
        .ADC_CLK=ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL,
        .ADC_INT_EVENT=INT_ADC0SS0,
        .ADC_MODE=ADC_TRIGGER_PROCESSOR,
    },
    {
        .SYSCTL_PERIPH_ADC=SYSCTL_PERIPH_ADC0,
        .SYSCTL_PERIPH_GPIO_ADC=SYSCTL_PERIPH_GPIOD,
        .GPIO_PORT_ADC_BASE=GPIO_PORTD_BASE,
        .GPIO_PIN_ADC=GPIO_PIN_2 | GPIO_PIN_3,
        .ADC_BASE=ADC0_BASE,
        .INT_ADC=ADC_REF_INT,
        .ADC_CTL_0=ADC_CTL_CH4,
        .ADC_CTL=ADC_CTL_CH5 |ADC_CTL_END | ADC_CTL_IE,
        .ADC_CLK=ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL,
        .ADC_INT_EVENT=INT_ADC0SS0,
        .ADC_MODE=ADC_TRIGGER_PROCESSOR,
    },
    {
        .SYSCTL_PERIPH_ADC=SYSCTL_PERIPH_ADC0,
        .SYSCTL_PERIPH_GPIO_ADC=SYSCTL_PERIPH_GPIOD,
        .GPIO_PORT_ADC_BASE=GPIO_PORTD_BASE,
        .GPIO_PIN_ADC=GPIO_PIN_0 | GPIO_PIN_1,
        .ADC_BASE=ADC0_BASE,
        .INT_ADC=ADC_REF_INT,
        .ADC_CTL_0=ADC_CTL_CH6,
        .ADC_CTL=ADC_CTL_CH7 |ADC_CTL_END | ADC_CTL_IE,
        .ADC_CLK=ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL,
        .ADC_INT_EVENT=INT_ADC0SS0,
        .ADC_MODE=ADC_TRIGGER_PROCESSOR,
    },
    {
        .SYSCTL_PERIPH_ADC=SYSCTL_PERIPH_ADC0,
        .SYSCTL_PERIPH_GPIO_ADC=SYSCTL_PERIPH_GPIOE,
        .GPIO_PORT_ADC_BASE=GPIO_PORTE_BASE,
        .GPIO_PIN_ADC=GPIO_PIN_4 | GPIO_PIN_5,
        .ADC_BASE=ADC0_BASE,
        .INT_ADC=ADC_REF_INT,
        .ADC_CTL_0=ADC_CTL_CH8,
        .ADC_CTL=ADC_CTL_CH9 |ADC_CTL_END | ADC_CTL_IE,
        .ADC_CLK=ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL,
        .ADC_INT_EVENT=INT_ADC0SS0,
        .ADC_MODE=ADC_TRIGGER_PROCESSOR,
    },
    {
        .SYSCTL_PERIPH_ADC=SYSCTL_PERIPH_ADC0,
        .SYSCTL_PERIPH_GPIO_ADC=SYSCTL_PERIPH_GPIOB,
        .GPIO_PORT_ADC_BASE=GPIO_PORTB_BASE,
        .GPIO_PIN_ADC=GPIO_PIN_4 | GPIO_PIN_5,
        .ADC_BASE=ADC0_BASE,
        .INT_ADC=ADC_REF_INT,
        .ADC_CTL_0=ADC_CTL_CH10,
        .ADC_CTL=ADC_CTL_CH11 |ADC_CTL_END | ADC_CTL_IE,
        .ADC_CLK=ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL,
        .ADC_INT_EVENT=INT_ADC0SS0,
        .ADC_MODE=ADC_TRIGGER_PROCESSOR,
    },
};

//对应的端口如下
//Ch0:PE3           Ch1:PE2
//Ch0:PE1           Ch1:PE0    (开发板上没引出)
//Ch0:PD3 (error)   Ch1:PD2
//Ch0:PD1           Ch1:PD0
//Ch0:PE5           Ch1:PE4
//Ch0:PB4           Ch1:PB5
void ConfigureADC(int ADCstyle,void (*adc_pfnHandler)(void))
{
        SysCtlPeripheralEnable(adc_array[ADCstyle].SYSCTL_PERIPH_ADC);
        SysCtlPeripheralEnable(adc_array[ADCstyle].SYSCTL_PERIPH_GPIO_ADC);

        GPIOPinTypeADC(adc_array[ADCstyle].GPIO_PORT_ADC_BASE,
                       adc_array[ADCstyle].GPIO_PIN_ADC);

        ADCClockConfigSet(adc_array[ADCstyle].ADC_BASE,adc_array[ADCstyle].ADC_CLK,1);
        ADCReferenceSet(adc_array[ADCstyle].ADC_BASE,adc_array[ADCstyle].INT_ADC);
        ADCSequenceConfigure(adc_array[ADCstyle].ADC_BASE, 0 ,
                             adc_array[ADCstyle].ADC_MODE, 0);

        ADCSequenceStepConfigure(adc_array[ADCstyle].ADC_BASE, 0, 0,
                                 adc_array[ADCstyle].ADC_CTL_0);
        ADCSequenceStepConfigure(adc_array[ADCstyle].ADC_BASE, 0, 1,
                                 adc_array[ADCstyle].ADC_CTL);

        ADCHardwareOversampleConfigure(adc_array[ADCstyle].ADC_BASE,64);
        ADCSequenceEnable(adc_array[ADCstyle].ADC_BASE, 0);

        IntEnable(adc_array[ADCstyle].ADC_INT_EVENT);
        ADCIntRegister(adc_array[ADCstyle].ADC_BASE, 0 ,adc_pfnHandler);
        ADCIntEnable(adc_array[ADCstyle].ADC_BASE, 0);
}

void ADC_MSP_Hander(int mode)
{
    uint32_t ui32AdcValue[2] = {0,0};

    ADCIntClear(adc_array[mode].ADC_BASE, 0);
    ADCSequenceDataGet(adc_array[mode].ADC_BASE, 0, ui32AdcValue);

    Ch0Value = ((float)ui32AdcValue[0])*(3300.0/4096.0);
    Ch1Value = ((float)ui32AdcValue[1])*(3300.0/4096.0);

    badcflag = true;
}

void   __attribute__((weak))  ADCIntHander(void)
{
    ADC_MSP_Hander(0);
}

//对应的端口如下
//Ch0:PE3           Ch1:PE2
//Ch0:PE1           Ch1:PE0    (开发板上没引出)
//Ch0:PD3 (error)   Ch1:PD2
//Ch0:PD1           Ch1:PD0
//Ch0:PE5           Ch1:PE4
//Ch0:PB4           Ch1:PB5
void ADC_Trig(int mode)
{
    int timerout=10;
    ADCProcessorTrigger(adc_array[mode].ADC_BASE, 0);
    while((true!=badcflag)&&timerout)
    {
        timerout--;
        SysCtlDelay(SysCtlClockGet()/(3000));
    }
    badcflag = false;
}

