/*************
 �౾����
QEI�������ļ�

 2018.2.10
**************/

#include "QEI_Init.h"

int32_t i32Vel=0;                       //�ٶ�,unit:������/s,�����ž�������
int32_t i32Dir=1;                       //1Ϊ����,-1Ϊ����
int Velocity=0;                          //���ս��
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

        .DIR = 1,         //����
        .VELOCITY = 0,    //����
        .INIT_POS = 0,    //��ʼλ��
        .NOW_POS = 0,     //λ��
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

        .DIR = 1,         //����
        .VELOCITY = 0,    //����
        .INIT_POS = 0,    //��ʼλ��
        .NOW_POS = 0,     //λ��
    },
};



/*
*************************************************************
*   ��  ��  ��: QEI_VEL_IntHandler
*   ����˵��: QEI�����жϷ����ӳ���
*   ��ڲ���: none  (�ڲ��������û��Լ���д)
*   ��  ��  ֵ: none
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
    //��ȡλ�ú��ٶ���Ϣ
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
    //��ʼλ��
    if(Init_flag)
    {
    	qei_array[0].INIT_POS = MAP_QEIPositionGet(qei_array[0].QEI_BASE);
        Init_flag = false;
    }
    //��ȡλ�ú��ٶ���Ϣ
    qei_array[0].NOW_POS = MAP_QEIPositionGet(qei_array[0].QEI_BASE);
    Vel_DataDeal(i32Vel,&Velocity);
    bVelflag=true;
}
/*
*************************************************************
*   ��  ��  ��: ConfigQEI
*   ����˵��: QEI��ʼ������(ע��ʹ��QEI0ʱҪ����PD7)
*   ��ڲ���: qei_data -- �ṹ��ָ��ָ��ṹ���Ա
*   ��  ��  ֵ: none
*************************************************************
*/
void ConfigureQEI(int mode,void(*QEI_VEL_IntHandler)(void))
{
	//ʹ�ܶ�Ӧ��ϵͳQEI��GPIOʱ��
    MAP_SysCtlPeripheralEnable(qei_array[mode].SYSCTL_PERIPH_QEI);
    MAP_SysCtlPeripheralEnable(qei_array[mode].SYSCTL_PERIPH_GPIO_QEI);

	// Unlock PD7
	HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE+GPIO_O_CR)=GPIO_PIN_7;

	//GPIO�ĸ������� �͸���QEI������
	MAP_GPIOPinConfigure(qei_array[mode].GPIO_CFG_A);
	MAP_GPIOPinConfigure(qei_array[mode].GPIO_CFG_B);
	MAP_GPIOPinTypeQEI(qei_array[mode].GPIO_PORT_QEI_BASE,
	               qei_array[mode].GPIO_PIN_QEI);

	//QEI����λ������
	//��������ַ��ģʽ������λ��ֵ
	MAP_QEIConfigure(qei_array[mode].QEI_BASE,qei_array[mode].QEI_CONFIG_MODE,
	             qei_array[mode].QEI_MAX_POSITION);

	//QEI��ʹ�ܴ�
	MAP_QEIEnable(qei_array[mode].QEI_BASE);

	/* signal before it is counted;(�����ⲿ�źŲ�����ʱ�ӷ�Ƶ,��ʱ�����ⲿ�źŵ�4��Ƶ�������½�)
	 * param ui32Period:��ʱ��װ��ֵ.ÿ��һ��ϵͳʱ�����ڣ�װ��ֵ--������0����װ��
	 * �����ʱ����accumulator�ۻ��ⲿ�����ź���Ŀ.
	 * ��ʱ������һ�ν�accumulator�ۼ�������Ĵ�������ȡ(�ж�),accumulator����.
	*/
	// �˴���4��Ƶ��߾���;0.1s��һ���жϳ�һ������,����CPU����,ͬʱ����㹻�������߾���
	// period����ͬTimer����
	MAP_QEIVelocityConfigure(qei_array[mode].QEI_BASE,qei_array[mode].QEI_VEL_CLK_DIV,
	                         MAP_SysCtlClockGet() /(qei_array[mode].QEI_VEL_INT_FRE ));

	//�����ٶȲ���ʹ�ܴ�
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
*   ��  ��  ��: Vel_DataDeal
*   ����˵��: �ٶ����ݴ�������,���ٶ�ת��Ϊ:rpm r--1040���� 1m -- 60s
*   ��ڲ���: rawdata -- ԭʼ����(������/s),pdealeddata -- ����ַ���洦���������
*   ��  ��  ֵ: none
*************************************************************
*/
void Vel_DataDeal(int32_t rawdata,int *pdealeddata)
{
    if(rawdata > 0)
    {
        *pdealeddata=(int)(rawdata*0.0385+0.5);     //��������ȡ��
    }
    else
    {
        *pdealeddata=(int)(rawdata*0.0385-0.5);     //��������ȡ��
    }
}

