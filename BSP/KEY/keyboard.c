#include "BSP/KEY/keyboard.h"

int keyvalue=0;

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

int keyboardscan()
{
    keyvalue=0;
    C_all_out;
    R_all_in;
    C_all_low;
    R[0] = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_1);
    R[1] = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_2);
    R[2] = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3);
    R[3] = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1);
    if((R[0]&GPIO_PIN_1)!=GPIO_PIN_1)
    {
        delay_ms(10);
        R[0] = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_1);
        if((R[0]&GPIO_PIN_1)!=GPIO_PIN_1)
        {
            keyvalue+=12;
        }
    }

    else if((R[1]&GPIO_PIN_2)!=GPIO_PIN_2)
    {
        delay_ms(10);
        R[1] = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_2);
        if((R[1]&GPIO_PIN_2)!=GPIO_PIN_2)
        {
            keyvalue+=8;
        }
    }

    else if((R[2]&GPIO_PIN_3)!=GPIO_PIN_3)
    {
        delay_ms(10);
        R[2] = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3);
        if((R[2]&GPIO_PIN_3)!=GPIO_PIN_3)
        {
            keyvalue+=4;
        }
    }

    else if((R[3]&GPIO_PIN_1)!=GPIO_PIN_1)
    {
        delay_ms(10);
        R[3] = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1);
        if((R[3]&GPIO_PIN_1)!=GPIO_PIN_1)
        {
            keyvalue+=0;
        }
    }

    R_all_out;
    C_all_in;
    R_all_low;
    C[0] = GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7);
    C[1] = GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6);
    C[2] = GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_5);
    C[3] = GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_4);
    if((C[0]&GPIO_PIN_7)!=GPIO_PIN_7)
    {
        delay_ms(10);
        C[0] = GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7);
        if((C[0]&GPIO_PIN_7)!=GPIO_PIN_7)
        {
            keyvalue+=1;
        }
    }

    else if((C[1]&GPIO_PIN_6)!=GPIO_PIN_6)
    {
        delay_ms(10);
        C[1] = GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6);
        if((C[1]&GPIO_PIN_6)!=GPIO_PIN_6)
        {
            keyvalue+=2;
        }
    }

    else if((C[2]&GPIO_PIN_5)!=GPIO_PIN_5)
    {
        delay_ms(10);
        C[2] = GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_5);
        if((C[2]&GPIO_PIN_5)!=GPIO_PIN_5)
        {
            keyvalue+=3;
        }
    }

    else if((C[3]&GPIO_PIN_4)!=GPIO_PIN_4)
    {
        delay_ms(10);
        C[3] = GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_4);
        if((C[3]&GPIO_PIN_4)!=GPIO_PIN_4)
        {
            keyvalue+=4;
        }
    }
    if(keyvalue!=0)
    {
        UARTprintf(0,"%d\n",keyvalue);
        UARTprintf(1,"%d\n",keyvalue);
        return 1;
    }
    else
        return 0;
}



