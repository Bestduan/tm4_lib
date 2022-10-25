/*************
 坂本制作
ADC的配置文件

 2018.2.10
**************/
#ifndef ADC_Init_H_
#define ADC_Init_H_


#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_adc.h"

#include "driverlib/gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"

typedef struct
{
    uint32_t    SYSCTL_PERIPH_ADC;
    uint32_t    SYSCTL_PERIPH_GPIO_ADC;

    uint32_t    GPIO_PORT_ADC_BASE;
    uint8_t     GPIO_PIN_ADC;

    uint32_t    ADC_BASE;
    uint32_t    ADC_CTL;
    uint32_t    ADC_CTL_0;
    uint32_t    ADC_CLK;
    uint32_t    ADC_MODE;
    uint32_t    ADC_INT_EVENT;
    uint32_t    INT_ADC;
}adc_data_t;


extern uint32_t Ch0Value;
extern uint32_t Ch1Value;
extern volatile bool  badcflag;
extern adc_data_t adc_array[6];


extern void ADCIntHander(void);
extern void ADC_MSP_Hander(int mode);
extern void ConfigureADC(int ADCstyle,void (*adc_pfnHandler)(void));
extern void ADC_Trig(int mode);

#endif
