/*************
 坂本制作
sonar的配置文件

 2018.2.10
**************/
#include "BSP/SENSOR/sonar.h"

double Distance = 0;


//默认PB4口触发超声波测距模块
void SonarTrig()
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
    SysCtlDelay(SysCtlClockGet()*30/(3000000));
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
    WTimerTrig(2);
}


//超声波测距的距离获取函数
void GetAverageDistance()
{
    int i = 0;
    double dis[5] = {0, 0, 0, 0, 0 };
    for( i=0 ; i<=4 ; i++)
    {
        SonarTrig();
        dis[i] = bDistance;
     }
    ShellSort(dis, 5);
    Distance = (dis[1]+dis[2]+dis[3]) /3.0;
}



