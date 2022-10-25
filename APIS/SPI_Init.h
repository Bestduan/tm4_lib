/*************
 坂本制作
SPI的配置文件

 2018.2.10
**************/
#ifndef SPI_Init_H_
#define SPI_Init_H_

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "inc/hw_ints.h"

typedef struct
{
    uint32_t    SYSCTL_PERIPH_SSI;
    uint32_t    SYSCTL_PERIPH_GPIO;

    uint32_t    GPIO_PORT_SSI_BASE;
    uint32_t    GPIO_SSI_CLK;
    uint32_t    GPIO_SSI_FSS;
    uint32_t    GPIO_SSI_RX;
    uint32_t    GPIO_SSI_TX;
    uint8_t     GPIO_SSI_PINS;

    uint32_t    SSI_PROTOCOL;
    uint32_t    SSI_BIT_RATE;
    uint32_t    SSI_DATA_WIDTH;

    uint32_t    SSI_BASE;
}spi_data_t;

extern const spi_data_t spi_array[4];

extern void ConfigureSPI(int mode,void (* SSI_Handler)(void));


#endif
