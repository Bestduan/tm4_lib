/*
 * keyboard.h
 *
 *  Created on: 2018Äê7ÔÂ14ÈÕ
 *      Author: Marvellous
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "USER/head.h"
#include "driverlib/gpio.h"

uint32_t C[4],R[4];
extern int keyvalue;

/**************
PB4--C4
PA5--C3
PA6--C2
PA7--C1
PF1--R1
PE3--R2
PE2--R3
PE1--R4
*************/

#define  C_all_high GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_PIN_4);\
                    GPIOPinWrite((GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
#define  C_all_low  GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,0x0);\
                    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,0x0);
#define  C_all_out  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_4);\
                    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
#define  C_all_in   GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_PIN_4);\
                    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);\
                    GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);\
                    GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
#define  R_all_high GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1);\
                    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
#define  R_all_low  GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0x0);\
                    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x0);
#define  R_all_out  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);\
                    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
#define  R_all_in   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_1);\
                    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);\
                    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);\
                    GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);


extern int keyboardscan();

#endif /* KEYBOARD_H_ */
