#ifndef _DAC8811_H
#define _DAC8811_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"

#include "BPS/delay.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef unsigned char   uchar;
typedef unsigned int    uint;
//GPIO_InitTypeDef GPIO_Initure;
#define DAC8811_SDA_SET        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, GPIO_PIN_6);
#define DAC8811_SDA_CLR        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, 0);       
                 
#define DAC8811_CLK_SET       GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5, GPIO_PIN_5);
#define DAC8811_CLK_CLR        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5, 0);       
                 
#define DAC8811_CS_SET        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_4, GPIO_PIN_4);
#define DAC8811_CS_CLR        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_4, 0);



void DAC8811_IO_Init(void);
void DAC8811_Transform(uint16_t temp);
void Write_Data(float out_volt);
uint16_t VoltOfData(float out_volt);

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */
