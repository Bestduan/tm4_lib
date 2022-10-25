/*************
 坂本制作
配置初始化文件

 2018.3.17
**************/
#include "USER/Init.h"

void systemInit()
{
     SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
     GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3);
     GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3,
                          GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
     ConfigureUART(0,115200);
     FPULazyStackingEnable();
     FPUEnable();
     ConfigureADC(0,ADCIntHander);
//     ADS1115_IO_Init();
     DAC8571_IO_Init();
//     TLV5618_Port_Init();
//     ADF435X_IO_Init();
//     ADF4351_Init();
}
