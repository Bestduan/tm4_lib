/*************
 �౾����
I2C�ķ�51���������ļ�

 2018.2.10
**************/

#ifndef HARDWARE_I2C_I2C_H_
#define HARDWARE_I2C_I2C_H_

/*=====��׼��ͷ�ļ� =============*/
#include <stdint.h>
#include <stdbool.h>

/*===== TivaWare ������ͷ�ļ�====*/
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "inc/hw_memmap.h"



/*===�����������===*/
#define SCL_OUT()	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_3)
#define SDA_OUT()	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_2)

#define SDA_IN()	MAP_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_2)

/*===���øߵ͵�ƽ====*/

#define IIC_SCL_H()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8)
#define IIC_SCL_L()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0)

#define IIC_SDA_H()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,4)
#define IIC_SDA_L()	MAP_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0)

#define READ_SDA	MAP_GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_2)




//IIC���в�������
extern void IIC_Init(void);                     //��ʼ��IIC��IO��
extern void IIC_Start(void);                    //����IIC��ʼ�ź�
extern void IIC_Stop(void);                     //����IICֹͣ�ź�
extern void IIC_Send_Byte(uint8_t txd);         //IIC����һ���ֽ�
extern uint8_t IIC_Read_Byte(uint8_t ack);//IIC��ȡһ���ֽ�
extern uint8_t IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
extern void IIC_Ack(void);                      //IIC����ACK�ź�
extern void IIC_NAck(void);                     //IIC������ACK�ź�


#endif /* HARDWARE_I2C_I2C_H_ */
