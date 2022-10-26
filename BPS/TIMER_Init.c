/*************
 �౾����
TIMER�������ļ�

 2018.2.10
**************/
#include "TIMER_Init.h"

volatile bool bwtimerflag=0;
volatile bool btimerflag=0;
uint32_t fre=0;
uint32_t duty=0;
uint32_t bDistance=0;
uint32_t timer_count=0;

#if TIMER_INIT==1
//timer_array1[] �Ƕ���Timer1�����ö�Ӧ��CCP1
//T0CCP1:PF1    T1CCP1:PF3
//T2CCP1:PB1    T3CCP1:PB3
//T4CCP1:PC1    T5CCP1:PC3
const timer_data_t timer_array[6]=
{
 {
      .SYSCTL_PERIPH_TIMER=SYSCTL_PERIPH_TIMER0,
      .SYSCTL_PERIPH_GPIO_TIMER=SYSCTL_PERIPH_GPIOF,

      .TIMER_BASE=TIMER0_BASE,
      .TIMER_PORT=TIMER_B,
      .TIMER_DIV=8,
      .TIMER_MODE=TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC,
      .TIMER_INT_EVENT=TIMER_TIMB_TIMEOUT,
       //TIMER_CAPA/B_EVENT��      ����A/B�¼��жϣ�                               TIMER_CAPA/B_MATCH��       ����A/Bƥ���жϣ�
       //TIMER_TIMA/B_TIMEOUT�� ��ʱ�� A/B��ʱ�жϣ�                            TIMER_RTC_MATCH��RTC   �ж����Σ�
      .INT_TIMER=INT_TIMER0B,
 },
 {
        .SYSCTL_PERIPH_TIMER=SYSCTL_PERIPH_TIMER1,
        .SYSCTL_PERIPH_GPIO_TIMER=SYSCTL_PERIPH_GPIOF,

        .TIMER_BASE=TIMER1_BASE,
        .TIMER_PORT=TIMER_B,
        .TIMER_DIV=8,
        .TIMER_MODE=TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC,
        .TIMER_INT_EVENT=TIMER_TIMB_TIMEOUT,
         //TIMER_CAPA/B_EVENT��      ����A/B�¼��жϣ�                               TIMER_CAPA/B_MATCH��       ����A/Bƥ���жϣ�
         //TIMER_TIMA/B_TIMEOUT�� ��ʱ�� A/B��ʱ�жϣ�                            TIMER_RTC_MATCH��RTC   �ж����Σ�
        .INT_TIMER=INT_TIMER1B,
 },
 {
        .SYSCTL_PERIPH_TIMER=SYSCTL_PERIPH_TIMER2,
        .SYSCTL_PERIPH_GPIO_TIMER=SYSCTL_PERIPH_GPIOB,

        .TIMER_BASE=TIMER2_BASE,
        .TIMER_PORT=TIMER_B,
        .TIMER_DIV=8,
        .TIMER_MODE=TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC,
        .TIMER_INT_EVENT=TIMER_TIMB_TIMEOUT,
         //TIMER_CAPA/B_EVENT��      ����A/B�¼��жϣ�                               TIMER_CAPA/B_MATCH��       ����A/Bƥ���жϣ�
         //TIMER_TIMA/B_TIMEOUT�� ��ʱ�� A/B��ʱ�жϣ�                            TIMER_RTC_MATCH��RTC   �ж����Σ�
        .INT_TIMER=INT_TIMER2B,
 },
 {
        .SYSCTL_PERIPH_TIMER=SYSCTL_PERIPH_TIMER3,
        .SYSCTL_PERIPH_GPIO_TIMER=SYSCTL_PERIPH_GPIOB,

        .TIMER_BASE=TIMER3_BASE,
        .TIMER_PORT=TIMER_B,
        .TIMER_DIV=8,
        .TIMER_MODE=TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC,
        .TIMER_INT_EVENT=TIMER_TIMB_TIMEOUT,
         //TIMER_CAPA/B_EVENT��      ����A/B�¼��жϣ�                               TIMER_CAPA/B_MATCH��       ����A/Bƥ���жϣ�
         //TIMER_TIMA/B_TIMEOUT�� ��ʱ�� A/B��ʱ�жϣ�                            TIMER_RTC_MATCH��RTC   �ж����Σ�
        .INT_TIMER=INT_TIMER3B,
 },
 {
        .SYSCTL_PERIPH_TIMER=SYSCTL_PERIPH_TIMER4,
        .SYSCTL_PERIPH_GPIO_TIMER=SYSCTL_PERIPH_GPIOC,

        .TIMER_BASE=TIMER4_BASE,
        .TIMER_PORT=TIMER_B,
        .TIMER_DIV=4,
        .TIMER_MODE=TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC,
        .TIMER_INT_EVENT=TIMER_TIMB_TIMEOUT,
         //TIMER_CAPA/B_EVENT��      ����A/B�¼��жϣ�                               TIMER_CAPA/B_MATCH��       ����A/Bƥ���жϣ�
         //TIMER_TIMA/B_TIMEOUT�� ��ʱ�� A/B��ʱ�жϣ�                            TIMER_RTC_MATCH��RTC   �ж����Σ�
        .INT_TIMER=INT_TIMER4B,
 },
 {
        .SYSCTL_PERIPH_TIMER=SYSCTL_PERIPH_TIMER5,
        .SYSCTL_PERIPH_GPIO_TIMER=SYSCTL_PERIPH_GPIOC,

        .TIMER_BASE=TIMER5_BASE,
        .TIMER_PORT=TIMER_B,
        .TIMER_DIV=8,
        .TIMER_MODE=TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC,
        .TIMER_INT_EVENT=TIMER_TIMB_TIMEOUT,
         //TIMER_CAPA/B_EVENT��      ����A/B�¼��жϣ�                               TIMER_CAPA/B_MATCH��       ����A/Bƥ���жϣ�
         //TIMER_TIMA/B_TIMEOUT�� ��ʱ�� A/B��ʱ�жϣ�                            TIMER_RTC_MATCH��RTC   �ж����Σ�
        .INT_TIMER=INT_TIMER5B,
 },
};
#endif


#if WTIMER_INIT==1
//wtimer_array1[] �Ƕ���WTimer1�����ö�Ӧ��CCP1
//Ĭ�ϲ�Ƶ������              :     PC5
//Ĭ�ϲ�ռ�ձ�����           :     PC7
//Ĭ�ϲ��������              :     PD3
//WT0CCP1:PC5    WT1CCP1:PC7
//WT2CCP1:PD1    WT3CCP1:PD3
//WT4CCP1:PD5    WT5CCP1:PD7
const wtimer_data_t wtimer_array[6]=
{
 {
        .SYSCTL_PERIPH_WTIMER=SYSCTL_PERIPH_WTIMER0,          //ϵͳ��Ӧ��WTIMERģ��ʹ��
        .SYSCTL_PERIPH_GPIO_WTIMER=SYSCTL_PERIPH_GPIOC,       //ϵͳ��Ӧ��GPIO�˿�ʹ��
        .GPIO_WT0CCP=GPIO_PC5_WT0CCP1,                        //GPIO���ùܽ�WT_CCP����
        .GPIO_PORT_WTIMER_BASE=GPIO_PORTC_BASE,               //GPIO���ö˿�
        .GPIO_PIN_WTIMER= GPIO_PIN_5,                         //GPIO���ùܽ�
        .WTIMER_BASE=  WTIMER0_BASE,                          //WTIMER�Ļ�ַ
        .WTIMER_MODE=  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP,
                                                              //WTIMER�Ĺ���ģʽ
        .WTIMER_PORT=  TIMER_B,                               //WTIMER��ָ���Ķ�ʱ��
        .WTIMER_EVENT= TIMER_EVENT_POS_EDGE,                 //���񴥷��¼�
                                                              //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
        .WTIMER_INT_EVENT= TIMER_CAPB_EVENT,                  //�жϴ����¼�
        .INT_WTIMER= INT_WTIMER0B,                            //�ж�ʹ��
 },
 {
        .SYSCTL_PERIPH_WTIMER=SYSCTL_PERIPH_WTIMER1,          //ϵͳ��Ӧ��WTIMERģ��ʹ��
        .SYSCTL_PERIPH_GPIO_WTIMER=SYSCTL_PERIPH_GPIOC,       //ϵͳ��Ӧ��GPIO�˿�ʹ��
        .GPIO_WT0CCP=GPIO_PC7_WT1CCP1,                        //GPIO���ùܽ�WT_CCP����
        .GPIO_PORT_WTIMER_BASE=GPIO_PORTC_BASE,               //GPIO���ö˿�
        .GPIO_PIN_WTIMER= GPIO_PIN_7,                         //GPIO���ùܽ�
        .WTIMER_BASE=  WTIMER1_BASE,                          //WTIMER�Ļ�ַ
        .WTIMER_MODE=  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP,
                                                              //WTIMER�Ĺ���ģʽ
        .WTIMER_PORT=  TIMER_B,                               //WTIMER��ָ���Ķ�ʱ��
        .WTIMER_EVENT = TIMER_EVENT_POS_EDGE,                 //���񴥷��¼�
                                                              //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
        .WTIMER_INT_EVENT= TIMER_CAPB_EVENT,                  //�жϴ����¼�
        .INT_WTIMER= INT_WTIMER1B,                            //�ж�ʹ��
 },
 {
        .SYSCTL_PERIPH_WTIMER=SYSCTL_PERIPH_WTIMER2,          //ϵͳ��Ӧ��WTIMERģ��ʹ��
        .SYSCTL_PERIPH_GPIO_WTIMER=SYSCTL_PERIPH_GPIOD,       //ϵͳ��Ӧ��GPIO�˿�ʹ��
        .GPIO_WT0CCP=GPIO_PD1_WT2CCP1,                        //GPIO���ùܽ�WT_CCP����
        .GPIO_PORT_WTIMER_BASE=GPIO_PORTD_BASE,               //GPIO���ö˿�
        .GPIO_PIN_WTIMER= GPIO_PIN_1,                         //GPIO���ùܽ�
        .WTIMER_BASE=  WTIMER2_BASE,                          //WTIMER�Ļ�ַ
        .WTIMER_MODE=  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP,
                                                              //WTIMER�Ĺ���ģʽ
        .WTIMER_PORT=  TIMER_B,                               //WTIMER��ָ���Ķ�ʱ��
        .WTIMER_EVENT = TIMER_EVENT_POS_EDGE,                 //���񴥷��¼�
                                                              //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
        .WTIMER_INT_EVENT= TIMER_CAPB_EVENT,                  //�жϴ����¼�
        .INT_WTIMER= INT_WTIMER2B,                            //�ж�ʹ��
 },
 {
        .SYSCTL_PERIPH_WTIMER=SYSCTL_PERIPH_WTIMER3,          //ϵͳ��Ӧ��WTIMERģ��ʹ��
        .SYSCTL_PERIPH_GPIO_WTIMER=SYSCTL_PERIPH_GPIOD,       //ϵͳ��Ӧ��GPIO�˿�ʹ��
        .GPIO_WT0CCP=GPIO_PD3_WT3CCP1,                        //GPIO���ùܽ�WT_CCP����
        .GPIO_PORT_WTIMER_BASE=GPIO_PORTD_BASE,               //GPIO���ö˿�
        .GPIO_PIN_WTIMER= GPIO_PIN_3,                         //GPIO���ùܽ�
        .WTIMER_BASE=  WTIMER3_BASE,                          //WTIMER�Ļ�ַ
        .WTIMER_MODE=  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP,
                                                              //WTIMER�Ĺ���ģʽ
        .WTIMER_PORT=  TIMER_B,                               //WTIMER��ָ���Ķ�ʱ��
        .WTIMER_EVENT = TIMER_EVENT_BOTH_EDGES,               //���񴥷��¼�
                                                              //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
        .WTIMER_INT_EVENT= TIMER_CAPB_EVENT,                  //�жϴ����¼�
        .INT_WTIMER= INT_WTIMER3B,                            //�ж�ʹ��
 },
 {
        .SYSCTL_PERIPH_WTIMER=SYSCTL_PERIPH_WTIMER4,          //ϵͳ��Ӧ��WTIMERģ��ʹ��
        .SYSCTL_PERIPH_GPIO_WTIMER=SYSCTL_PERIPH_GPIOD,       //ϵͳ��Ӧ��GPIO�˿�ʹ��
        .GPIO_WT0CCP=GPIO_PD5_WT4CCP1,                        //GPIO���ùܽ�WT_CCP����
        .GPIO_PORT_WTIMER_BASE=GPIO_PORTD_BASE,               //GPIO���ö˿�
        .GPIO_PIN_WTIMER= GPIO_PIN_5,                         //GPIO���ùܽ�
        .WTIMER_BASE=  WTIMER4_BASE,                          //WTIMER�Ļ�ַ
        .WTIMER_MODE=  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP,
                                                              //WTIMER�Ĺ���ģʽ
        .WTIMER_PORT=  TIMER_B,                               //WTIMER��ָ���Ķ�ʱ��
        .WTIMER_EVENT = TIMER_EVENT_POS_EDGE,                 //���񴥷��¼�
                                                              //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
        .WTIMER_INT_EVENT= TIMER_CAPB_EVENT,                  //�жϴ����¼�
        .INT_WTIMER= INT_WTIMER4B,                            //�ж�ʹ��
 },
 {
        .SYSCTL_PERIPH_WTIMER=SYSCTL_PERIPH_WTIMER5,          //ϵͳ��Ӧ��WTIMERģ��ʹ��
        .SYSCTL_PERIPH_GPIO_WTIMER=SYSCTL_PERIPH_GPIOD,       //ϵͳ��Ӧ��GPIO�˿�ʹ��
        .GPIO_WT0CCP=GPIO_PD7_WT5CCP1,                        //GPIO���ùܽ�WT_CCP����
        .GPIO_PORT_WTIMER_BASE=GPIO_PORTD_BASE,               //GPIO���ö˿�
        .GPIO_PIN_WTIMER= GPIO_PIN_7,                         //GPIO���ùܽ�
        .WTIMER_BASE=  WTIMER5_BASE,                          //WTIMER�Ļ�ַ
        .WTIMER_MODE=  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP,
                                                              //WTIMER�Ĺ���ģʽ
        .WTIMER_PORT=  TIMER_B,                               //WTIMER��ָ���Ķ�ʱ��
        .WTIMER_EVENT = TIMER_EVENT_POS_EDGE,                 //���񴥷��¼�
                                                              //TIMER_EVENT_POS/NEG/BOTH_EDGE(S)
        .WTIMER_INT_EVENT= TIMER_CAPB_EVENT,                  //�жϴ����¼�
        .INT_WTIMER= INT_WTIMER5B,                            //�ж�ʹ��
 },
};
#endif

#if WWDG_INIT==1
#if WWDG_INT==1
void Watchdog0IntHandler(void)
{
    MAP_WatchdogIntClear(WATCHDOG0_BASE);
}
void Watchdog1IntHandler(void)
{
    MAP_WatchdogIntClear(WATCHDOG1_BASE);
}
#endif
void ConfigureWWDG(int mode,int settime)
{
    uint32_t   WWDG_BASE;
    if(mode==0)
    {
        WWDG_BASE=WATCHDOG0_BASE;
#if WWDG_INT==1
        WatchdogIntRegister(WWDG_BASE,Watchdog0IntHandler);
#endif
    }else{WWDG_BASE=WATCHDOG1_BASE;
#if WWDG_INT==1
    WatchdogIntRegister(WWDG_BASE,Watchdog1IntHandler);
#endif
    }
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0+mode);
    if(MAP_WatchdogLockState(WWDG_BASE)==true)
    {MAP_WatchdogUnlock(WWDG_BASE);}
    MAP_WatchdogReloadSet(WWDG_BASE,settime);
    MAP_WatchdogResetEnable(WWDG_BASE);
    MAP_WatchdogEnable(WWDG_BASE);
#if WWDG_INT==1
    MAP_IntEnable(INT_WATCHDOG);
#endif
}
void FeedWWDG(int mode,int settime)
{
    MAP_WatchdogReloadSet(WATCHDOG0_BASE,settime);
}
#endif

#if TIMER_INIT==1
int timerlimit=1;
void Timer_MSP_Handler(int mode)
{
    uint32_t ui32status;
    ui32status=MAP_TimerIntStatus(timer_array[mode].TIMER_BASE,true);
    MAP_TimerIntClear(timer_array[mode].TIMER_BASE,ui32status);
}

void Timercount()
{
    static uint32_t ui32counter=0;
    Timer_MSP_Handler(0);
    if(ui32counter>=timerlimit)
    {
        ui32counter=0;
        timer_count++;
    }
    ui32counter++;
}


//T0CCP1:PF1    T1CCP1:PF3
//T2CCP1:PB1    T3CCP1:PB3
//T4CCP1:PC1    T5CCP1:PC3
void ConfigureTimer(int TimerStyle,int timeset,void (*timer_pfnHandler)(void))
{
//    if(timeset<=3000)
//    {(timer_array+TimerStyle)->TIMER_DIV=8;}
//    else if(timeset<=200)
//    {(timer_array+TimerStyle)->TIMER_DIV=16;}
//    else if(timeset<=50)
//    {(timer_array+TimerStyle)->TIMER_DIV=32;}

    //ϵͳ���� ���ö�ʱ�жϿ�
    MAP_SysCtlPeripheralEnable((timer_array+TimerStyle)->SYSCTL_PERIPH_TIMER);
    MAP_SysCtlPeripheralEnable((timer_array+TimerStyle)->SYSCTL_PERIPH_GPIO_TIMER);

    //�Զ�ʱ����ʱ��Դ��������    �ô���ѡ�õ�ϵͳʱ��      (��ַ��ָ����ʱ��)
    MAP_TimerClockSourceSet((timer_array+TimerStyle)->TIMER_BASE,TIMER_CLOCK_SYSTEM);
    //�Զ�ʱ����ʱ��Դ���з�Ƶ����   �ó��ǽ��е�8��Ƶ     (��ַ��ָ����ʱ��)
    MAP_TimerPrescaleSet((timer_array+TimerStyle)->TIMER_BASE,(timer_array+TimerStyle)->TIMER_PORT,
                     ((timer_array+TimerStyle)->TIMER_DIV)-1);
    //�Զ�ʱ�����л�������   �ֱ��ǣ���ʱ�����õĻ�ַ���Լ�����ģʽ������
    MAP_TimerConfigure((timer_array+TimerStyle)->TIMER_BASE,
                   (timer_array+TimerStyle)->TIMER_MODE);
    //�Զ�ʱʱ��������ã�������������                             (��ַ��ָ����ʱ������ʱ��ʱ��)
    MAP_TimerLoadSet((timer_array+TimerStyle)->TIMER_BASE,
                 (timer_array+TimerStyle)->TIMER_PORT,
                 ((MAP_SysCtlClockGet()/(MAP_TimerPrescaleGet((timer_array+TimerStyle)->TIMER_BASE,
                 (timer_array+TimerStyle)->TIMER_PORT)+1))/timeset)-1);
    //���жϴ�����������ע��                                                   ( ��ַ��ָ����ʱ��  ���жϴ�������)

    TimerIntRegister((timer_array+TimerStyle)->TIMER_BASE,
                     (timer_array+TimerStyle)->TIMER_PORT,timer_pfnHandler);
    //�򿪶�ʱ�жϵ�ʹ�ܣ��Ͷ�ʱʹ��                                    ( ��ַ����ʹ�ܵ��ж�Դ��λ����)�磺
    MAP_TimerIntEnable((timer_array+TimerStyle)->TIMER_BASE,
                   (timer_array+TimerStyle)->TIMER_INT_EVENT);
    MAP_TimerEnable((timer_array+TimerStyle)->TIMER_BASE,
                (timer_array+TimerStyle)->TIMER_PORT);
    MAP_IntEnable((timer_array+TimerStyle)->INT_TIMER);
    MAP_TimerIntDisable((timer_array+TimerStyle)->TIMER_BASE,TIMER_B);
}
#endif

#if WTIMER_INIT==1
long int Wtimer_MSP_Handler(int mode)
{
    long int value=0;
    MAP_TimerIntClear(wtimer_array[mode].WTIMER_BASE,
                         MAP_TimerIntStatus(wtimer_array[mode].WTIMER_BASE,true));
    value= MAP_TimerValueGet(wtimer_array[mode].WTIMER_BASE,TIMER_B);
    MAP_TimerControlEvent(wtimer_array[mode].WTIMER_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
    return value;
}

void WtimerIntHandler()
{
    int x=1;
    static uint16_t ui16EdgeCountrr = 0;
    static uint32_t ui32Timerr[2]={0};
    static uint16_t ui16EdgeCountr = 0;
    static uint32_t ui32Timer[2]={0};
    static double fPeriodrr = 0;
    static double fPeriodr = 0;
    MAP_TimerIntClear(wtimer_array[x].WTIMER_BASE,
                      MAP_TimerIntStatus(wtimer_array[x].WTIMER_BASE,true));
    ui32Timerr[ui16EdgeCountrr++] = MAP_TimerValueGet(wtimer_array[x].WTIMER_BASE,TIMER_B);
    MAP_TimerControlEvent(wtimer_array[x].WTIMER_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
    if(ui16EdgeCountrr > 1)
    {
        ui16EdgeCountrr = 0;
        fPeriodrr = ui32Timerr[1] > ui32Timerr[0] ? ui32Timerr[1] - ui32Timerr[0]
                    : ui32Timerr[1] - ui32Timerr[0] + 0xFFFFFFFF;
        fre=(uint32_t)80000000.0/fPeriodrr;

        ui32Timer[ui16EdgeCountr++]=ui32Timerr[0];
               if (ui16EdgeCountr > 1)
               {
                   ui16EdgeCountr=0;
                   fPeriodr= ui32Timer[1] > ui32Timer[0] ? ui32Timer[1] - ui32Timer[0] : ui32Timer[1] - ui32Timer[0] + 0xFFFFFFFF;
                   duty=(100.0*fPeriodrr)/fPeriodr;
                   bwtimerflag = true;
               }
               MAP_TimerControlEvent(wtimer_array[x].WTIMER_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
    }
}

void DistanceGet()
{
    int x=3;
    static uint32_t Timer[2]={0};
    static uint32_t count=0;
    double fperiod=0;
    MAP_TimerIntClear(wtimer_array[x].WTIMER_BASE,MAP_TimerIntStatus(wtimer_array[x].WTIMER_BASE,true));
    MAP_TimerControlEvent(wtimer_array[x].WTIMER_BASE,wtimer_array[x].WTIMER_PORT,TIMER_EVENT_BOTH_EDGES);
    Timer[count++]=MAP_TimerValueGet(wtimer_array[x].WTIMER_BASE,TIMER_B);

    if(count>1)
    {
        count=0;
        fperiod=Timer[1]>Timer[0]?Timer[1]-Timer[0]:Timer[1]-Timer[0]+0XFFFFFFFF;
        bDistance=(uint32_t)(fperiod*0.00000625);
        bwtimerflag=true;
    }
}
//WT0CCP1:PC5    WT1CCP1:PC7
//WT2CCP1:PD1    WT3CCP1:PD3
//WT4CCP1:PD5    WT5CCP1:PD7
void WTimerTrig(int wtimerstyle)
{
    int timerout=10;
    MAP_TimerIntEnable((wtimer_array+wtimerstyle)->WTIMER_BASE,
                   (wtimer_array+wtimerstyle)->WTIMER_INT_EVENT);
    MAP_TimerIntClear((wtimer_array+wtimerstyle)->WTIMER_BASE,
                      MAP_TimerIntStatus((wtimer_array+wtimerstyle)->WTIMER_BASE,false));
    while((true!=bwtimerflag)&&timerout)
    {
        timerout--;
        MAP_SysCtlDelay(MAP_SysCtlClockGet()/(3000));
    }
    MAP_TimerIntDisable((wtimer_array+wtimerstyle)->WTIMER_BASE,
                    (wtimer_array+wtimerstyle)->WTIMER_INT_EVENT);
    bwtimerflag=false;
}

void ConfigureWTimer(int wtimerstyle,void (*Wtimer_pfnHandler)(void))
{
    //ϵͳ���� ���ö�ʱ�жϿ�
    MAP_SysCtlPeripheralEnable((wtimer_array+wtimerstyle)->SYSCTL_PERIPH_WTIMER);
    MAP_SysCtlPeripheralEnable((wtimer_array+wtimerstyle)->SYSCTL_PERIPH_GPIO_WTIMER);
    //�Բ���ڵĸ�������
    MAP_GPIOPinConfigure((wtimer_array+wtimerstyle)->GPIO_WT0CCP);
    MAP_GPIOPinTypeTimer((wtimer_array+wtimerstyle)->GPIO_PORT_WTIMER_BASE,
                     (wtimer_array+wtimerstyle)->GPIO_PIN_WTIMER);

    MAP_TimerConfigure((wtimer_array+wtimerstyle)->WTIMER_BASE,
                   (wtimer_array+wtimerstyle)->WTIMER_MODE);
    //���ò���ģʽ�д�����ʱ�����ź��ؼ��жϴ����¼�
    MAP_TimerControlEvent((wtimer_array+wtimerstyle)->WTIMER_BASE,
                      (wtimer_array+wtimerstyle)->WTIMER_PORT,
                      (wtimer_array+wtimerstyle)->WTIMER_EVENT);

    //���жϴ�����������ע��                                                   ( ��ַ��ָ����ʱ��  ���жϴ�������)
    TimerIntRegister((wtimer_array+wtimerstyle)->WTIMER_BASE,
                     (wtimer_array+wtimerstyle)->WTIMER_PORT,Wtimer_pfnHandler);

    //�򿪶�ʱ�жϵ�ʹ�ܣ��Ͷ�ʱʹ��                                    ( ��ַ����ʹ�ܵ��ж�Դ��λ����)
    MAP_TimerIntEnable((wtimer_array+wtimerstyle)->WTIMER_BASE,
                   (wtimer_array+wtimerstyle)->WTIMER_INT_EVENT);
    MAP_TimerEnable((wtimer_array+wtimerstyle)->WTIMER_BASE,
                (wtimer_array+wtimerstyle)->WTIMER_PORT);

    MAP_IntEnable((wtimer_array+wtimerstyle)->INT_WTIMER);
    MAP_TimerIntDisable((wtimer_array+wtimerstyle)->WTIMER_BASE,
                    (wtimer_array+wtimerstyle)->WTIMER_INT_EVENT);
}
#endif

