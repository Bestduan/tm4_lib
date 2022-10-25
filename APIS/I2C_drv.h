/*************
 坂本制作
I2C的仿51驱动配置文件

 2018.2.10
**************/

#ifndef HARDWARE_I2C_I2C_H_
#define HARDWARE_I2C_I2C_H_

/*=====标准库头文件 =============*/
#include <stdint.h>
#include <stdbool.h>

/*===== TivaWare 驱动库头文件====*/
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "inc/hw_memmap.h"



/*===设置输入输出===*/
#define SCL_OUT()	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_3)
#define SDA_OUT()	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_2)

#define SDA_IN()	MAP_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_2)

/*===设置高低电平====*/

#define IIC_SCL_H()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8)
#define IIC_SCL_L()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0)

#define IIC_SDA_H()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,4)
#define IIC_SDA_L()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0)

#define READ_SDA	MAP_GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_2)




//IIC所有操作函数
extern void IIC_Init(void);                     //初始化IIC的IO口
extern void IIC_Start(void);                    //发送IIC开始信号
extern void IIC_Stop(void);                     //发送IIC停止信号
extern void IIC_Send_Byte(uint8_t txd);         //IIC发送一个字节
extern uint8_t IIC_Read_Byte(uint8_t ack);//IIC读取一个字节
extern uint8_t IIC_Wait_Ack(void);              //IIC等待ACK信号
extern void IIC_Ack(void);                      //IIC发送ACK信号
extern void IIC_NAck(void);                     //IIC不发送ACK信号


#endif /* HARDWARE_I2C_I2C_H_ */
