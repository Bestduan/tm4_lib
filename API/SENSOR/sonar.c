/*************
 �౾����
sonar�������ļ�

 2018.2.10
**************/
#include "sonar.h"

double Distance = 0;


//Ĭ��PB4�ڴ������������ģ��
void SonarTrig()
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
    SysCtlDelay(SysCtlClockGet()*30/(3000000));
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
    WTimerTrig(2);
}


//���������ľ����ȡ����
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



