/*************
 坂本制作
PWM的配置文件

 2018.2.10
**************/
#ifndef _DELAY_H
#define _DELAY_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"

#include "driverlib/gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"


extern void delay_us(unsigned long y);
extern void delay_ms(unsigned long y);
extern void delay_s (unsigned long y);




#endif



