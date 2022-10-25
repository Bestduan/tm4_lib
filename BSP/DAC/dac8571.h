#ifndef _DAC8571_H
#define _DAC8571_H

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

#include "APIS/delay.h"
#include "APIS/I2C_Init.h"

#define DAC8571_SDA_H							GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define DAC8571_SDA_L							GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0)

#define DAC8571_SCLK_H							GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define DAC8571_SCLK_L							GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0)

#define DAC8571_A0_H							GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define DAC8571_A0_L							GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0)


extern void DAC8571_IO_Init(void);
extern void DAC8571_setvol(float vol);
extern void DAC8571_vol(float vol);

#endif


