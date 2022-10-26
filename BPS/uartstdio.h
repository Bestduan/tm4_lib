/*************
 坂本制作
UART的配置文件

 2018.2.10
**************/
#ifndef __UARTSTDIO_H__
#define __UARTSTDIO_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_uart.h"

#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"

#if UART_DMA==1
#include "driverlib/udma.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define  UART_LEN   50
#define  UART_DMA    0
#define  UART_INT    0

extern int8_t  UART_rec[UART_LEN];

typedef struct uart_data_t
{
    uint32_t SYSCTL_PERIPH_UART;
    uint32_t SYSCTL_PERIPH_GPIO_UART;

    uint32_t GPIO_PORT_UART_BASE;
    uint32_t GPIO_UART_TX;
    uint32_t GPIO_UART_RX;
    uint8_t  GPIO_PIN_UART;

    uint32_t UART_BASE;
}uart_data_t;



#if UART_INT==1
extern void ConfigureINTUART(int mode, int band, void (*uart_pfnHandler)(void));
extern void UART_MSP_Handler(int mode);
extern volatile bool bUARTflag;
#endif

#if UART_DMA==1
extern void ConfigureUART_DMA(int mode,int8_t *RXstr,int8_t *TXstr);
#endif

extern void ConfigureUART(int mode, int band);
extern void UARTprintf(int style, int8_t *pcString, ...);
extern int  UARTRead(int mode,int8_t *pui8Buffer);



#ifdef __cplusplus
}
#endif

#endif
