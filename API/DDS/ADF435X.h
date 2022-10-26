 /*-----------------------------------------------
  ���ƣ�AD9854��������
  ��д��Liu
  ���ڣ�2014.3
  �޸ģ���
  ���ݣ�
------------------------------------------------*/
#ifndef __ADF435X_H__
#define __ADF435X_H__

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "BPS/delay.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

#ifndef ulong
#define ulong  unsigned long int
#endif    


#define       ADF435X_SDIO_SET     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2 , GPIO_PIN_2) //SDIO--A4
#define       ADF435X_SDIO_RESET   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2 , 0)
#define       ADF435X_SCLK_SET     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 , GPIO_PIN_0) //SCLK--A3
#define       ADF435X_SCLK_RESET   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 , 0)
#define       ADF435X_LE_SET       GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5 , GPIO_PIN_5) //LE--A2
#define       ADF435X_LE_RESET     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5 , 0)

void ADF435X_IO_Init(void);
void ADF4350_Init(void);  //INIT ADF4350
void ADF4351_Init(void);  //INIT ADF4351
void ADF435X_W_Freq(ulong Freq);
void ADF435X_W_Amp(uchar Amp);

#endif
