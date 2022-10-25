#include "dac8571.h"


void DAC8571_IO_Init(void)
{
	//Init GPIOM
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    // Check if the peripheral access is enabled.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
	{
	}	
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
	
	GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	DAC8571_A0_L;
	DAC8571_SDA_H;
	DAC8571_SCLK_H;
}

void DAC8571_write(unsigned int data)
{
	int i;
	
	for(i=0;i<8;i++)
	{
		delay_us(5);
		if(((data>>7)&0x01))
			DAC8571_SDA_H;
		else
			DAC8571_SDA_L;
		delay_us(5);
		DAC8571_SCLK_H;
		delay_us(5);
		DAC8571_SCLK_L;
		data=data<<1;
	}
	DAC8571_SDA_H;
	delay_us(5);
	DAC8571_SCLK_H;
	delay_us(5);
	DAC8571_SCLK_L;
}


void DAC8571_setvol(float vol)
{
	unsigned int v;
	vol=vol/4.096f;
	v=((unsigned int)(vol*32768.0f));
	DAC8571_SDA_L;
	delay_us(5);
	DAC8571_SCLK_L;
	DAC8571_write(0x98);
	DAC8571_write(0x10);
	DAC8571_write(((v>>7)&0Xff));
	DAC8571_write((v&0xff));
	
	DAC8571_SDA_L;
	delay_us(5);
	DAC8571_SCLK_H;
	delay_us(5);
	DAC8571_SDA_H;
	delay_us(5);
}
