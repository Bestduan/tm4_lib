#include "USER/head.h"

int main(void)
{
//    uint32_t sweep_fre_r = 75;
//    uint32_t sweep_fre;
    systemInit();
    Kaiser(50,16,30);
    while(1)
    {
        if(UARTRead(0,UART_rec)==0)
        {
            Kaiser(50,8192,30);
        }
        delay_ms(1);
    }

//    while(Ch1Value<100)
//    {
//        ADC_Trig(0);
//        sweep_fre_r = sweep_fre_r + 5;
//        sweep_fre = sweep_fre_r * 1000;
//        ADF435X_W_Freq(sweep_fre);
//        ADF435X_W_Amp(3);
//        delay_ms(1);
//    }
//    UARTprintf(0,"Ch0Value is %d mv\n",Ch0Value);
//    UARTprintf(0,"Ch1Value is %d mv\n",Ch1Value);
//    delay_ms(400);
//    DAC5618_VoltageSet(1,0.8);
}


