/*************
 坂本制作
QEI的配置文件

 2018.2.10
**************/

#include "APIS/QEI_Init.h"

int32_t i32Vel=0;                       //速度,unit:脉冲数/s,正负号决定方向
int32_t i32Dir=1;                       //1为正向,-1为反向
int Velocity=0;                          //最终结果
volatile bool bVelflag=false;
volatile bool Init_flag=true;
//QEI0: D6,D7
//QEI1: C5,C6
qei_data_t qei_array[2] =
{
    {
        .SYSCTL_PERIPH_QEI = SYSCTL_PERIPH_QEI0,
        .SYSCTL_PERIPH_GPIO_QEI = SYSCTL_PERIPH_GPIOD,
        .QEI_BASE = QEI0_BASE,
        .QEI_CONFIG_MODE = (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET
        | QEI_CONFIG_QUADRATURE | QEI_CONFIG_SWAP),
        .QEI_MAX_POSITION = 0x618,		// 13*30*4 = 1560
        .QEI_VEL_CLK_DIV = QEI_VELDIV_1,
        .QEI_VEL_INT_FRE = 10,
        .QEI_INT = INT_QEI0,
        .QEI_INT_FLAG = (QEI_INTDIR | QEI_INTTIMER),

        .GPIO_PORT_QEI_BASE = GPIO_PORTD_BASE,
        .GPIO_PIN_QEI = (GPIO_PIN_6 | GPIO_PIN_7),
        .GPIO_CFG_A = GPIO_PD6_PHA0,
        .GPIO_CFG_B = GPIO_PD7_PHB0,

        .DIR = 1,         //方向
        .VELOCITY = 0,    //速率
        .INIT_POS = 0,    //初始位置
        .NOW_POS = 0,     //位置
    },

    {
        .SYSCTL_PERIPH_QEI = SYSCTL_PERIPH_QEI1,
        .SYSCTL_PERIPH_GPIO_QEI = SYSCTL_PERIPH_GPIOC,
        .QEI_BASE = QEI1_BASE,
        .QEI_CONFIG_MODE = (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET
        | QEI_CONFIG_QUADRATURE | QEI_CONFIG_SWAP),
        .QEI_MAX_POSITION = 0x618,		// 13*30*4 = 1560
        .QEI_VEL_CLK_DIV = QEI_VELDIV_1,
        .QEI_VEL_INT_FRE = 10,
        .QEI_INT = INT_QEI1,
        .QEI_INT_FLAG = (QEI_INTDIR | QEI_INTTIMER),

        .GPIO_PORT_QEI_BASE = GPIO_PORTC_BASE,
        .GPIO_PIN_QEI = (GPIO_PIN_5 | GPIO_PIN_6),
        .GPIO_CFG_A = GPIO_PC5_PHA1,
        .GPIO_CFG_B = GPIO_PC6_PHB1,

        .DIR = 1,         //方向
        .VELOCITY = 0,    //速率
        .INIT_POS = 0,    //初始位置
        .NOW_POS = 0,     //位置
    },
};



/*
*************************************************************
*   函  数  名: QEI_VEL_IntHandler
*   功能说明: QEI测速中断服务子程序
*   入口参数: none  (内部配置需用户自己编写)
*   返  回  值: none
*************************************************************
*/
void QEI1_IntHandler(void)
{
    uint32_t IntStatus;
    IntStatus=MAP_QEIIntStatus(QEI1_BASE,true);
    MAP_QEIIntClear(QEI1_BASE,IntStatus);

    if((IntStatus & QEI_INTDIR) == QEI_INTDIR)
    {
        i32Dir=-i32Dir;
    }
    if((IntStatus & QEI_INTTIMER) == QEI_INTTIMER)
    {
        i32Vel= MAP_QEIVelocityGet(QEI1_BASE)*10*MAP_QEIDirectionGet(QEI1_BASE);
    }
    if(Init_flag)
    {
        qei_array[0].INIT_POS = MAP_QEIPositionGet(qei_array[0].QEI_BASE);
        Init_flag = false;
    }
    //读取位置和速度信息
    qei_array[0].NOW_POS = MAP_QEIPositionGet(qei_array[0].QEI_BASE);
    Vel_DataDeal(i32Vel,&Velocity);
    bVelflag=true;
}
void QEI0_IntHandler(void)
{
    uint32_t IntStatus;
    IntStatus=MAP_QEIIntStatus(QEI0_BASE,true);
    MAP_QEIIntClear(QEI0_BASE,IntStatus);

    if((IntStatus & QEI_INTDIR) == QEI_INTDIR)
    {
        i32Dir=-i32Dir;
    }
    if((IntStatus & QEI_INTTIMER) == QEI_INTTIMER)
    {
        i32Vel= MAP_QEIVelocityGet(QEI0_BASE)*10*MAP_QEIDirectionGet(QEI0_BASE);
    }
    //初始位置
    if(Init_flag)
    {
    	qei_array[0].INIT_POS = MAP_QEIPositionGet(qei_array[0].QEI_BASE);
        Init_flag = false;
    }
    //读取位置和速度信息
    qei_array[0].NOW_POS = MAP_QEIPositionGet(qei_array[0].QEI_BASE);
    Vel_DataDeal(i32Vel,&Velocity);
    bVelflag=true;
}
/*
*************************************************************
*   函  数  名: ConfigQEI
*   功能说明: QEI初始化函数(注意使用QEI0时要解锁PD7)
*   入口参数: qei_data -- 结构体指针指向结构体成员
*   返  回  值: none
*************************************************************
*/
void ConfigureQEI(int mode,void(*QEI_VEL_IntHandler)(void))
{
	//使能对应的系统QEI和GPIO时钟
    MAP_SysCtlPeripheralEnable(qei_array[mode].SYSCTL_PERIPH_QEI);
    MAP_SysCtlPeripheralEnable(qei_array[mode].SYSCTL_PERIPH_GPIO_QEI);

	// Unlock PD7
	HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE+GPIO_O_CR)=GPIO_PIN_7;

	//GPIO的复用声明 和复用QEI的配置
	MAP_GPIOPinConfigure(qei_array[mode].GPIO_CFG_A);
	MAP_GPIOPinConfigure(qei_array[mode].GPIO_CFG_B);
	MAP_GPIOPinTypeQEI(qei_array[mode].GPIO_PORT_QEI_BASE,
	               qei_array[mode].GPIO_PIN_QEI);

	//QEI处理位置配置
	//参数：基址，模式，最大的位置值
	MAP_QEIConfigure(qei_array[mode].QEI_BASE,qei_array[mode].QEI_CONFIG_MODE,
	             qei_array[mode].QEI_MAX_POSITION);

	//QEI的使能打开
	MAP_QEIEnable(qei_array[mode].QEI_BASE);

	/* signal before it is counted;(对由外部信号产生的时钟分频,该时钟是外部信号的4倍频，上升下降)
	 * param ui32Period:定时器装载值.每过一个系统时钟周期，装载值--，减到0重新装载
	 * 在这段时间内accumulator累积外部边沿信号数目.
	 * 定时器记完一次将accumulator累计数放入寄存器待读取(中断),accumulator清零.
	*/
	// 此处测4倍频提高精度;0.1s进一次中断出一次数据,减少CPU负担,同时测得足够多边沿提高精度
	// period计算同Timer部分
	MAP_QEIVelocityConfigure(qei_array[mode].QEI_BASE,qei_array[mode].QEI_VEL_CLK_DIV,
	                         MAP_SysCtlClockGet() /(qei_array[mode].QEI_VEL_INT_FRE ));

	//处理速度捕获使能打开
	MAP_QEIVelocityEnable(qei_array[mode].QEI_BASE);


	QEIIntRegister(qei_array[mode].QEI_BASE,QEI_VEL_IntHandler);
	MAP_IntEnable(qei_array[mode].QEI_INT);
	MAP_QEIIntDisable(qei_array[mode].QEI_BASE,qei_array[mode].QEI_INT_FLAG);
	MAP_SysCtlDelay(MAP_SysCtlClockGet()*5/3000);
}
void QEI_Trig(int mode)
{
    int timerout=10;
    MAP_QEIIntEnable(qei_array[mode].QEI_BASE,qei_array[mode].QEI_INT_FLAG);
    while((true!=bVelflag)&&timerout)
    {
        timerout--;
        MAP_SysCtlDelay(MAP_SysCtlClockGet()/(3000));
    }
    MAP_QEIIntDisable(qei_array[mode].QEI_BASE,qei_array[mode].QEI_INT_FLAG);
    bVelflag=false;
}

/*
*************************************************************
*   函  数  名: Vel_DataDeal
*   功能说明: 速度数据处理函数,将速度转换为:rpm r--1040脉冲 1m -- 60s
*   入口参数: rawdata -- 原始数据(脉冲数/s),pdealeddata -- 传地址储存处理后的数据
*   返  回  值: none
*************************************************************
*/
void Vel_DataDeal(int32_t rawdata,int *pdealeddata)
{
    if(rawdata > 0)
    {
        *pdealeddata=(int)(rawdata*0.0385+0.5);     //正数向上取整
    }
    else
    {
        *pdealeddata=(int)(rawdata*0.0385-0.5);     //负数向下取整
    }
}

