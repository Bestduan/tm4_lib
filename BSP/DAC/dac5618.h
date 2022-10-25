#ifndef _DAC5618_H
#define _DAC5618_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "APIS/delay.h"

#include "APIS/uartstdio.h"

#include "APIS/delay.h"

typedef unsigned char   uchar;
typedef unsigned int    uint;
//GPIO_InitTypeDef GPIO_Initure;
#define TLV5618_SCL_SET        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define TLV5618_SCL_CLR        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0)
                 
#define TLV5618_CS_HIGH        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_PIN_3)
#define TLV5618_CS_LOW         GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0)
                 
#define TLV5618_SDA_SET        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define TLV5618_SDA_CLR        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0)



extern void TLV5618_Port_Init(void);
extern void TLV5618_Init(void);
extern void DAC_Conver(uint temp);
extern void Write_A(float out_volt);
extern void Write_B(float out_volt);
extern uint VoltToData(float out_volt); //说明ref为参考源out_volt为输出模拟电压值
extern void DAC5618_VoltageSet(int DAC5618_Channel,float DAC5618Value);


#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */
