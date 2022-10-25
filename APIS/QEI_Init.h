/*************
 �౾����
QEI�������ļ�

 2018.2.10
**************/
#ifndef QEI_INIT_H_
#define QEI_INIT_H_

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_qei.h"

typedef struct
{
    uint32_t SYSCTL_PERIPH_QEI;
    uint32_t SYSCTL_PERIPH_GPIO_QEI;
    uint32_t QEI_BASE;
    uint32_t QEI_CONFIG_MODE;
    uint32_t QEI_MAX_POSITION;
    uint32_t QEI_VEL_CLK_DIV;
    uint32_t QEI_VEL_INT_FRE;
    uint32_t QEI_INT;
    uint32_t QEI_INT_FLAG;

    uint32_t GPIO_PORT_QEI_BASE;
    uint8_t  GPIO_PIN_QEI;
    uint32_t GPIO_CFG_A;
    uint32_t GPIO_CFG_B;

    int32_t  DIR;
    int32_t  VELOCITY;
    int32_t  INIT_POS;
    uint32_t NOW_POS;      //0~1560

}qei_data_t;

//*********************�ⲿ���ñ�������*********************
extern qei_data_t qei_array[2];

//*********************�ⲿ���ú�������*********************
extern void ConfigureQEI(int mode,void(*QEI_VEL_IntHandler)(void));
extern void QEI_Trig(int mode);
extern void Vel_DataDeal(int32_t rawdata,int *pdealeddata);
extern void QEI0_IntHandler(void);
extern void QEI1_IntHandler(void);
extern int32_t i32Vel;                       //�ٶ�,unit:������/s,�����ž�������
extern int32_t i32Dir;                       //1Ϊ����,-1Ϊ����
extern int Velocity;                           //���ս��
extern volatile bool bVelflag;

#endif /* QEI_INIT_H_ */
