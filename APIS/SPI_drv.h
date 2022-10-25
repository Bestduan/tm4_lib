/*
 * SPI_dev.h
 *
 *  Created on: 2018年9月19日
 *      Author: duan
 */

#ifndef APIS_SPI_DRV_H_
#define APIS_SPI_DRV_H_


/*=====标准库头文件 =============*/
#include <stdint.h>
#include <stdbool.h>

/*===== TivaWare 驱动库头文件====*/
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "inc/hw_memmap.h"

// * GPIO_PB2__ -> SYNC
// * GPIO_PE4__ -> SCLK
// * GPIO_PA6__ -> CS
// * GPIO_PB4__ -> DIN --- 接ADS1256 DOUT
// * GPIO_PE5__ -> DOUT --- 接ADS1256 DIN
// * GPIO_PA5__ -> DRDY
// * GPIO_PA7__ -> RESET


//SPI引脚定义
#define SPI_SCLK_GPIO_PORT			GPIO_PORTE_BASE
#define SPI_SCLK_GPIO_PIN			GPIO_PIN_4

#define SPI_CS_GPIO_PORT			GPIO_PORTA_BASE
#define SPI_CS_GPIO_PIN				GPIO_PIN_6

#define SPI_DIN_GPIO_PORT			GPIO_PORTB_BASE
#define SPI_DIN_GPIO_PIN			GPIO_PIN_4

#define SPI_DOUT_GPIO_PORT			GPIO_PORTE_BASE
#define SPI_DOUT_GPIO_PIN			GPIO_PIN_5



#define DRDY_GPIO_PORT				GPIO_PORTA_BASE
#define DRDY_GPIO_PIN				GPIO_PIN_5

#define SYNC_GPIO_PORT				GPIO_PORTB_BASE
#define SYNC_GPIO_PIN				GPIO_PIN_2

#define RESET_GPIO_PORT				GPIO_PORTA_BASE
#define RESET_GPIO_PIN				GPIO_PIN_7



/*===设置输入输出===*/




/*===设置高低电平====*/

#define SPI_SCLK_H()		GPIOPinWrite(SPI_SCLK_GPIO_PORT,SPI_SCLK_GPIO_PIN,SPI_SCLK_GPIO_PIN)
#define SPI_SCLK_L()		GPIOPinWrite(SPI_SCLK_GPIO_PORT,SPI_SCLK_GPIO_PIN,0x0)

#define SPI_CS_H()			GPIOPinWrite(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,SPI_CS_GPIO_PIN)
#define SPI_CS_L()			GPIOPinWrite(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,0x0)

#define SPI_DIN_H()			GPIOPinWrite(SPI_DIN_GPIO_PORT,SPI_DIN_GPIO_PIN,SPI_DIN_GPIO_PIN)
#define SPI_DIN_L()			GPIOPinWrite(SPI_DIN_GPIO_PORT,SPI_DIN_GPIO_PIN,0x0)

#define SPI_DOUT_H()		GPIOPinWrite(SPI_DOUT_GPIO_PORT,SPI_DOUT_GPIO_PIN,SPI_DOUT_GPIO_PIN)
#define SPI_DOUT_L()		GPIOPinWrite(SPI_DOUT_GPIO_PORT,SPI_DOUT_GPIO_PIN,0x0)

#define SPI_SYNC_H()		GPIOPinWrite(SYNC_GPIO_PORT,SYNC_GPIO_PIN,SYNC_GPIO_PIN)
#define SPI_SYNC_L()		GPIOPinWrite(SYNC_GPIO_PORT,SYNC_GPIO_PIN,0x0)

#define SPI_RESET_H()		GPIOPinWrite(RESET_GPIO_PORT,RESET_GPIO_PIN,RESET_GPIO_PIN)
#define SPI_RESET_L()		GPIOPinWrite(RESET_GPIO_PORT,RESET_GPIO_PIN,0x0)

/*===读引脚====*/
#define SPI_READ_DIN()		GPIOPinRead(SPI_DIN_GPIO_PORT,SPI_DIN_GPIO_PIN)
#define SPI_READ_DRDY()		GPIOPinRead(DRDY_GPIO_PORT,DRDY_GPIO_PIN)



//*********************外部调用函数声明*********************
extern void SPI_Delayus(unsigned long y);
extern void SPI_Init(void);
extern void SPI_Write_Byte(uint8_t TxByte);
extern uint8_t SPI_Read_Byte(void);

#endif /* DRV_SPI_H_ */
