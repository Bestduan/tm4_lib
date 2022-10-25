/*
 * key.h
 *
 *  Created on: 2018年2月4日
 *      Author: 坂本
 */

#ifndef KEY_H_
#define KEY_H_

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"

#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"



//*********************外部调用变量声明*********************
extern int SW4_count;
extern int SW0_count;
//*********************外部调用函数声明*********************
extern void KeyConfigure(int mode);
extern void KeyScan();

#endif /* KEY_H_ */
