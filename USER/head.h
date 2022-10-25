/*************
 坂本制作
main所需包含的所有头文件

 2018.3.17
**************/
#ifndef _HEAD_H
#define _HEAD_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_uart.h"


#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include "grlib/grlib.h"

#include "APIS/delay.h"
#include "APIS/uartstdio.h"
#include "APIS/TIMER_Init.h"
#include "APIS/PWM_Init.h"
#include "APIS/ADC_Init.h"
#include "APIS/I2C_Init.h"
#include "APIS/QEI_Init.h"
#include "APIS/SPI_Init.h"
#include "APIS/SPI_drv.h"

#include "BSP/OLED/oled.h"
#include "BSP/OLED/oled_font.h"
#include "BSP/sensor/tmp75.h"
#include "BSP/sensor/sonar.h"
#include "BSP/ADC/ads1118.h"
#include "BSP/ADC/ads1115.h"
#include "BSP/DAC/dac5618.h"
#include "BSP/DAC/dac8571.h"
#include "BSP/DDS/ADF435X.h"
#include "BSP/HMI/HMI.h"
#include "BSP/DDS/ad9959.h"
#include "BSP/DSP/Win_Fun_Gen.h"


#include "USER/Init.h"
#include "USER/Handle.h"


#endif
