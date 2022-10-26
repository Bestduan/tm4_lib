/*************
 �౾����
tmp75�������ļ�

 2018.2.10
**************/
#ifndef TMP75_H_
#define TMP75_H_

// The iic address of tmp75.
#define TMP_ADR                0x48

// Some register.
#define TMP_TEMP_REG                0x0
#define TMP_CONFIG_REG              0x01
#define TMP_LOW_REG                 0x02
#define TMP_HIGH_REG                0x03

// Configure.
#define TMP_12                      0x60

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"

#include "BPS/I2C_Init.h"

extern float temp_fdegree;
extern double rate;


extern void TMP75_configure();
extern void TMP75_function();


#endif /* TMP75_H_ */
