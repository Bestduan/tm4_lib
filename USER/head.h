/*************
 �౾����
main�������������ͷ�ļ�

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

#include "BPS/delay.h"
#include "BPS/uartstdio.h"
#include "BPS/TIMER_Init.h"
#include "BPS/PWM_Init.h"
#include "BPS/ADC_Init.h"
#include "BPS/I2C_Init.h"
#include "BPS/QEI_Init.h"
#include "BPS/SPI_Init.h"
#include "BPS/SPI_drv.h"

#include "API/OLED/oled.h"
#include "API/OLED/oled_font.h"
#include "API/sensor/tmp75.h"
#include "API/sensor/sonar.h"
#include "API/ADC/ads1118.h"
#include "API/ADC/ads1115.h"
#include "API/DAC/dac5618.h"
#include "API/DAC/dac8571.h"
#include "API/DDS/ADF435X.h"
#include "API/HMI/HMI.h"
#include "API/DDS/ad9959.h"
#include "API/DSP/Win_Fun_Gen.h"


#include "USER/Init.h"
#include "USER/Handle.h"


#endif
