#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_sysctl.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"


/* Peripheral definitions for EK-TM4C123G board */
// I2C port
#define OLED_I2C_BASE               I2C0_BASE
#define OLED_I2C_SYSCTL_PERIPH      SYSCTL_PERIPH_I2C0

// GPIO for I2C pins
#define OLED_GPIO_PORT_BASE         GPIO_PORTB_BASE
#define OLED_GPIO_SYSCTL_PERIPH     SYSCTL_PERIPH_GPIOB
#define OLED_I2C_SCL                GPIO_PIN_2
#define OLED_I2C_SDA                GPIO_PIN_3

#define OLED_I2C_PINS               (OLED_I2C_SCL | OLED_I2C_SDA)

// GPIO pin configuer
#define OLED_GPIO_I2C_SCL           GPIO_PB2_I2C0SCL
#define OLED_GPIO_I2C_SDA           GPIO_PB3_I2C0SDA

// commands define
#define OLED_I2C_ADDR              0x3C
#define OLED_I2C_DAT               0x40
#define OLED_I2C_CMD               0x00
#define WRITE                      false
#define READ                       true
#define OLED_CMD                   1
#define OLED_DAT                   0
#define OLED_DELAY                 600





extern void DelayXms(uint16_t xms);
extern void OLED_I2CInit(void);
extern void OLED_DrawPiexl(uint8_t u8X,uint8_t u8Y,bool bFILL);
extern void OLED_FillScreen(void);
extern void LCDDrawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,bool FILL);
extern void OLED_ClearScreen();
extern void OLED_DisplayChinese(uint8_t u8X,uint8_t u8Y,uint8_t number);
extern void OLED_DisplayChar(uint8_t u8X,uint8_t u8Y,uint8_t chr);
extern void OLED_DisplayNumber(uint8_t u8X,uint8_t u8Y,double num,uint8_t dec_dig);
extern void OLED_DisplayString(uint8_t u8X,uint8_t u8Y,uint8_t *pfstring);

#endif /* OLED_H_ */
