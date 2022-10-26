/*************
 坂本制作
PWM的配置文件

 2018.2.10
**************/
#ifndef PWM_INIT_H_
#define PWM_INIT_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"

#include "driverlib/interrupt.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

typedef struct
{
    uint32_t SYSCTL_PERIPH_PWM;
    uint32_t SYSCTL_PERIPH_GPIO_PWM;

    uint32_t GPIO_PORT_PWM_BASE;
    uint32_t GPIO_M_PWM;
    uint8_t  GPIO_PIN_PWM;

	uint8_t  DIV;
    uint32_t PWM_DIV;
    uint32_t PWM_BASE;
    uint32_t PWM_GEN;
    uint32_t PWM_MODE;

    uint32_t PWM_OUT_BIT;
    uint32_t PWM_OUT;

}pwm_data_t;

//*********************外部调用函数声明*********************
extern void ConfigurePWM(int mode,int pwmstyle);
extern void PWMSet(int mode,int pwmstyle,uint32_t fre,uint8_t duty);
extern void MotoSet(int mode,int pwmstyle,long int limit,long int thorn);



#endif	/* PWM_INIT_H_ */
