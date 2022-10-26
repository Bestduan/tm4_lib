/*
 * key.h
 *
 *  Created on: 2018��2��4��
 *      Author: �౾
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

//*********************�ⲿ���ñ�������*********************
extern int SW4_count;
extern int SW0_count;
//*********************�ⲿ���ú�������*********************
extern void KeyConfigure(int mode);
extern void KeyScan();

#endif /* KEY_H_ */
