/*************
 坂本制作
TIMER的配置文件

 2018.2.10
**************/
#ifndef TIMER_Init_H_
#define TIMER_Init_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/watchdog.h"
#include "driverlib/uart.h"
#include "driverlib/rom_map.h"

#define TIMER_INIT     1
#define WTIMER_INIT    1
#define WWDG_INIT      1
#define WWDG_INT       1

#if TIMER_INIT==1
typedef struct
{
    uint32_t    SYSCTL_PERIPH_TIMER;
    uint32_t    SYSCTL_PERIPH_GPIO_TIMER;

    uint32_t    TIMER_BASE;
    uint32_t    TIMER_PORT;
    uint32_t    TIMER_DIV;
    uint32_t    TIMER_MODE;
    uint32_t    INT_TIMER;

    //TIMER_CAPA/B_EVENT：      捕获A/B事件中断；
    //TIMER_CAPA/B_MATCH：       捕获A/B匹配中断；
    //TIMER_TIMA/B_TIMEOUT： 定时器 A/B超时中断；
    //TIMER_RTC_MATCH：RTC   中断屏蔽；
    uint32_t    TIMER_INT_EVENT;
}timer_data_t;

extern const timer_data_t  timer_array [6];
extern volatile bool btimerflag;
extern uint32_t timer_count;
extern void ConfigureTimer(int TimerStyle,int timeset,void (*timer_pfnHandler)(void));
extern void Timercount();
extern void Timer_MSP_Handler(int mode);
#endif
#if WWDG_INIT==1
extern void ConfigureWWDG(int mode,int settime);
extern void FeedWWDG(int mode,int settime);
#endif
#if WTIMER_INIT==1
extern void ConfigureWTimer(int wtimerstyle,void (*Wtimer_pfnHandler)(void));
extern long int Wtimer_MSP_Handler(int mode);
extern void WTimerTrig(int wtimerstyle);
extern void WtimerIntHandler();
extern void DistanceGet();
typedef struct
{
    uint32_t SYSCTL_PERIPH_WTIMER;                //系统对应的WTIMER模块使能
    uint32_t SYSCTL_PERIPH_GPIO_WTIMER;           //系统对应的GPIO端口使能
    uint32_t GPIO_WT0CCP;                         //GPIO复用管脚WT_CCP声明
    uint32_t GPIO_PORT_WTIMER_BASE;               //GPIO复用端口
    uint32_t GPIO_PIN_WTIMER;                     //GPIO复用管脚
    uint32_t WTIMER_BASE;                         //WTIMER的基址
    uint32_t WTIMER_MODE;                         //WTIMER的工作模式

    uint32_t WTIMER_PORT;                         //WTIMER的指定的定时器
    uint32_t WTIMER_EVENT;                        //捕获触发事件
                                                  //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
    uint32_t WTIMER_INT_EVENT;                    //中断触发事件
    uint32_t INT_WTIMER;                          //中断使能
}wtimer_data_t;

extern const wtimer_data_t wtimer_array[6];
extern uint32_t fre;
extern uint32_t duty;
extern uint32_t bDistance;
extern volatile bool bwtimerflag;
#endif


#endif 
