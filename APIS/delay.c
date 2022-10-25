/*************
 �౾����
PWM�������ļ�

 2018.2.10
**************/
#include "delay.h"


void delay_us(unsigned long y)
{
    MAP_SysCtlDelay(y*(MAP_SysCtlClockGet()/3000000));
}

void delay_ms(unsigned long y)
{
    MAP_SysCtlDelay(y*(MAP_SysCtlClockGet()/3000));
}

void delay_s(unsigned long y)
{
    MAP_SysCtlDelay(y*(MAP_SysCtlClockGet()/3));
}
