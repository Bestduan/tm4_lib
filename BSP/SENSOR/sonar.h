/*************
 坂本制作
sonar的配置文件

 2018.2.10
**************/
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/debug.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_timer.h"

#include "APIS/TIMER_Init.h"
#include "APIS/My_String.h"


extern double Distance;

extern void GetAverageDistance();
extern void ShellSort(double A[], int n);
