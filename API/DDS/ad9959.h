#ifndef _AD9959_H_
#define _AD9959_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"

#include "BPS/delay.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
/*****************Keywords define***********************/
#ifndef u8
    #define u8 unsigned char
#endif

#ifndef u16
    #define u16 unsigned short
#endif
    
#ifndef u32
    #define u32 unsigned long
#endif
    
#ifndef u64
    #define u64 unsigned long long
#endif   
//AD9959�Ĵ�����ַ����
#define CSR_ADD   0x00   //CSR  ͨ��ѡ��Ĵ���
#define FR1_ADD   0x01   //FR1  ���ܼĴ���1
#define FR2_ADD   0x02   //FR2  ���ܼĴ���2
#define CFR_ADD   0x03   //CFR  ͨ�����ܼĴ���
#define CFTW0_ADD 0x04   //CTW0 ͨ��Ƶ��ת���ּĴ���
#define CPOW0_ADD 0x05   //CPW0 ͨ����λת���ּĴ���
#define ACR_ADD   0x06   //ACR  ���ȿ��ƼĴ���
#define LSRR_ADD  0x07   //LSR  ͨ������ɨ��Ĵ���
#define RDW_ADD   0x08   //RDW  ͨ����������ɨ��Ĵ���
#define FDW_ADD   0x09   //FDW  ͨ����������ɨ��Ĵ���
//AD9959�ܽź궨��
#define PS0_SET			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2,GPIO_PIN_2)
#define PS0_CLR			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2,0)
#define PS1_SET			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3,GPIO_PIN_3)
#define PS1_CLR			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3,0)
#define PS2_SET			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4,GPIO_PIN_4)
#define PS2_CLR			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4,0)
#define PS3_SET			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5,GPIO_PIN_5)
#define PS3_CLR			    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5,0)
#define SDIO0_SET	        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0)
#define SDIO0_CLR		    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,0)
#define SDIO1_SET		    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,GPIO_PIN_1)
#define SDIO1_CLR	    	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,0)
#define SDIO2_SET	    	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,GPIO_PIN_2)
#define SDIO2_CLR	    	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,0)
#define AD9959_PWR_SET		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,GPIO_PIN_4)
#define AD9959_PWR_CLR		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0)
#define Reset_SET		    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5,GPIO_PIN_5)
#define Reset_CLR		    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5,0)
#define UPDATE_SET		    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0,GPIO_PIN_0)
#define UPDATE_CLR		    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0,0)
#define CS_SET		        GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1,GPIO_PIN_1)
#define CS_CLR		        GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1,0)
#define SCLK_SET		    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2,GPIO_PIN_2)
#define SCLK_CLR		    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2,0)
#define SDIO3_SET		    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_3,GPIO_PIN_3)
#define SDIO3_CLR		    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_3,0)


void IntReset(void);	  //AD9959��λ
void IO_Update(void);   //AD9959��������
void Intserve(void);		   //IO�ڳ�ʼ��
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp);
void Init_AD9959(void);
void Write_frequence(u8 Channel,u32 Freq);
void Write_Amplitude(u8 Channel, u16 Ampli);
void Write_Phase(u8 Channel,u16 Phase);
void Write_Quadrature(uint32_t Freq);














#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************

#endif // __BUTTONS_H__

