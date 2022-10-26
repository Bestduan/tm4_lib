/*************
 �౾����
PWM�������ļ�
 
 2018.2.10
**************/

#include "PWM_Init.h"


//�ṹ������  �г����й���PWM������

//pwm_array0[]  �ǹ���PWMģ��0������    ��Ӧ��M1PWMx  xΪout��
//M0PWM0:PB6  M0PWM1:PB7
//M0PWM2:PB4  M0PWM3:PB5
//M0PWM4:PE4  M0PWM5:PE5
//M0PWM6:PC4  M0PWM7:PC5
pwm_data_t pwm_array0[8] =
{
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOB,

          .GPIO_PORT_PWM_BASE=GPIO_PORTB_BASE,
          .GPIO_M_PWM=GPIO_PB6_M0PWM0,
          .GPIO_PIN_PWM=GPIO_PIN_6,

		  .DIV=8,
          .PWM_DIV=SYSCTL_PWMDIV_8,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_0,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_0_BIT,
          .PWM_OUT=PWM_OUT_0,
    },

    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOB,

          .GPIO_PORT_PWM_BASE=GPIO_PORTB_BASE,
          .GPIO_M_PWM=GPIO_PB7_M0PWM1,
          .GPIO_PIN_PWM=GPIO_PIN_7,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_0,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_1_BIT,
          .PWM_OUT=PWM_OUT_1,
    },
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOB,

          .GPIO_PORT_PWM_BASE=GPIO_PORTB_BASE,
          .GPIO_M_PWM=GPIO_PB4_M0PWM2,
          .GPIO_PIN_PWM=GPIO_PIN_4,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_1,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_2_BIT,
          .PWM_OUT=PWM_OUT_2,
    },
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOB,

          .GPIO_PORT_PWM_BASE=GPIO_PORTB_BASE,
          .GPIO_M_PWM=GPIO_PB5_M0PWM3,
          .GPIO_PIN_PWM=GPIO_PIN_5,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_1,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_3_BIT,
          .PWM_OUT=PWM_OUT_3,
    },
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOE,

          .GPIO_PORT_PWM_BASE=GPIO_PORTE_BASE,
          .GPIO_M_PWM=GPIO_PE4_M0PWM4,
          .GPIO_PIN_PWM=GPIO_PIN_4,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_2,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_4_BIT,
          .PWM_OUT=PWM_OUT_4,
    },
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOE,

          .GPIO_PORT_PWM_BASE=GPIO_PORTE_BASE,
          .GPIO_M_PWM=GPIO_PE5_M0PWM5,
          .GPIO_PIN_PWM=GPIO_PIN_5,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_2,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_5_BIT,
          .PWM_OUT=PWM_OUT_5,
    },
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOC,

          .GPIO_PORT_PWM_BASE=GPIO_PORTC_BASE,
          .GPIO_M_PWM=GPIO_PC4_M0PWM6,
          .GPIO_PIN_PWM=GPIO_PIN_4,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_3,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_6_BIT,
          .PWM_OUT=PWM_OUT_6,
    },
    {
          .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM0,
          .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOC,

          .GPIO_PORT_PWM_BASE=GPIO_PORTC_BASE,
          .GPIO_M_PWM=GPIO_PC5_M0PWM7,
          .GPIO_PIN_PWM=GPIO_PIN_5,

		  .DIV=1,
          .PWM_DIV=SYSCTL_PWMDIV_1,
          .PWM_BASE=PWM0_BASE,
          .PWM_GEN=PWM_GEN_3,
          .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

          .PWM_OUT_BIT=PWM_OUT_7_BIT,
          .PWM_OUT=PWM_OUT_7,
    },
};



//pwm_array1[]  �ǹ���PWMģ��1������       ��Ӧ��M1PWMx  xΪout��
//M1PWM0:PD0  M1PWM1:PD1
//M1PWM2:PA6  M1PWM3:PA7
//M1PWM4:PF0  M1PWM5:PF1
//M1PWM6:PF2  M1PWM7:PF3
pwm_data_t pwm_array1[8] =
{
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOD,

           .GPIO_PORT_PWM_BASE=GPIO_PORTD_BASE,
           .GPIO_M_PWM=GPIO_PD0_M1PWM0,
           .GPIO_PIN_PWM=GPIO_PIN_0,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_0,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_0_BIT,
           .PWM_OUT=PWM_OUT_0,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOD,

           .GPIO_PORT_PWM_BASE=GPIO_PORTD_BASE,
           .GPIO_M_PWM=GPIO_PD1_M1PWM1,
           .GPIO_PIN_PWM=GPIO_PIN_1,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_0,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_1_BIT,
           .PWM_OUT=PWM_OUT_1,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOA,

           .GPIO_PORT_PWM_BASE=GPIO_PORTA_BASE,
           .GPIO_M_PWM=GPIO_PA6_M1PWM2,
           .GPIO_PIN_PWM=GPIO_PIN_6,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_1,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_2_BIT,
           .PWM_OUT=PWM_OUT_2,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOA,

           .GPIO_PORT_PWM_BASE=GPIO_PORTA_BASE,
           .GPIO_M_PWM=GPIO_PA7_M1PWM3,
           .GPIO_PIN_PWM=GPIO_PIN_5,

           .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_1,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_3_BIT,
           .PWM_OUT=PWM_OUT_3,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOF,

           .GPIO_PORT_PWM_BASE=GPIO_PORTF_BASE,
           .GPIO_M_PWM=GPIO_PF0_M1PWM4,
           .GPIO_PIN_PWM=GPIO_PIN_0,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_2,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_4_BIT,
           .PWM_OUT=PWM_OUT_4,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOF,

           .GPIO_PORT_PWM_BASE=GPIO_PORTF_BASE,
           .GPIO_M_PWM=GPIO_PF1_M1PWM5,
           .GPIO_PIN_PWM=GPIO_PIN_1,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_2,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_5_BIT,
           .PWM_OUT=PWM_OUT_5,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOF,

           .GPIO_PORT_PWM_BASE=GPIO_PORTF_BASE,
           .GPIO_M_PWM=GPIO_PF2_M1PWM6,
           .GPIO_PIN_PWM=GPIO_PIN_2,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_3,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_6_BIT,
           .PWM_OUT=PWM_OUT_6,
     },
     {
           .SYSCTL_PERIPH_PWM=SYSCTL_PERIPH_PWM1,
           .SYSCTL_PERIPH_GPIO_PWM=SYSCTL_PERIPH_GPIOF,

           .GPIO_PORT_PWM_BASE=GPIO_PORTF_BASE,
           .GPIO_M_PWM=GPIO_PF3_M1PWM7,
           .GPIO_PIN_PWM=GPIO_PIN_3,

		   .DIV=1,
           .PWM_DIV=SYSCTL_PWMDIV_1,
           .PWM_BASE=PWM1_BASE,
           .PWM_GEN=PWM_GEN_3,
           .PWM_MODE=PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC,

           .PWM_OUT_BIT=PWM_OUT_7_BIT,
           .PWM_OUT=PWM_OUT_7,
     },
};

/*
*************************************************************
*   ��  ��  ��: ConfigurePWM
*   ����˵��: PWM������
*   ��ڲ���: �ṹ������
*   ��  ��  ֵ: none
*************************************************************
*/

//M0PWM0:PB6  M0PWM1:PB7
//M0PWM2:PB4  M0PWM3:PB5
//M0PWM4:PE4  M0PWM5:PE5
//M0PWM6:PC4  M0PWM7:PC5

//M1PWM0:PD0  M1PWM1:PD1
//M1PWM2:PA6  M1PWM3:PA7
//M1PWM4:PF0  M1PWM5:PF1
//M1PWM6:PF2  M1PWM7:PF3
void ConfigurePWM(int mode,int pwmstyle)
{
    pwm_data_t *pwm_data;
    if(mode==0) {
        pwm_data=pwm_array0;
    }else if (mode==1){
        pwm_data=pwm_array1;
    }
    //��PWMʹ�õ�ʱ�ӷ�Ƶ��������  �˴�Ϊ8��Ƶ   1/4/8/16/32
    MAP_SysCtlPWMClockSet((pwm_data+pwmstyle)->PWM_DIV);
	//��ϵͳʹ������  ���ö�Ӧ��PWMģ�� 0/1
    MAP_SysCtlPeripheralEnable((pwm_data+pwmstyle)->SYSCTL_PERIPH_PWM);
    MAP_SysCtlPeripheralEnable((pwm_data+pwmstyle)->SYSCTL_PERIPH_GPIO_PWM);

    //GPIO�ĸ�������  �͸�������
    MAP_GPIOPinConfigure((pwm_data+pwmstyle)->GPIO_M_PWM);
    MAP_GPIOPinTypePWM((pwm_data+pwmstyle)->GPIO_PORT_PWM_BASE,
                   (pwm_data+pwmstyle)->GPIO_PIN_PWM);

    //PWM����������
    MAP_PWMGenConfigure((pwm_data+pwmstyle)->PWM_BASE,
                    (pwm_data+pwmstyle)->PWM_GEN,(pwm_data+pwmstyle)->PWM_MODE);
}


/*
*************************************************************
*   ��  ��  ��: PWMSet
*   ����˵��: PWM���ڵ�����
*   ��ڲ���: �ṹ������ ��Ƶ�ʣ�ռ�ձ�
*   ��  ��  ֵ: none
*************************************************************
*/
//M0PWM0:PB6  M0PWM1:PB7
//M0PWM2:PB4  M0PWM3:PB5
//M0PWM4:PE4  M0PWM5:PE5
//M0PWM6:PC4  M0PWM7:PC5

//M1PWM0:PD0  M1PWM1:PD1
//M1PWM2:PA6  M1PWM3:PA7
//M1PWM4:PF0  M1PWM5:PF1
//M1PWM6:PF2  M1PWM7:PF3
void PWMSet(int mode,int pwmstyle,uint32_t fre,uint8_t duty)
{
    pwm_data_t *pwm_data;
    if(mode==0) {
        pwm_data=pwm_array0;
    }else if (mode==1){
        pwm_data=pwm_array1;
    }

    if(fre<=50)
    {pwm_data->PWM_DIV=SYSCTL_PWMDIV_32;pwm_data->DIV=32;
    MAP_SysCtlPWMClockSet((pwm_data+pwmstyle)->PWM_DIV);}
    else if(fre<=200)
    {pwm_data->PWM_DIV=SYSCTL_PWMDIV_16;pwm_data->DIV=16;
    MAP_SysCtlPWMClockSet((pwm_data+pwmstyle)->PWM_DIV);}
    else if(fre<=3000)
    {pwm_data->PWM_DIV=SYSCTL_PWMDIV_8;pwm_data->DIV=8;
    MAP_SysCtlPWMClockSet((pwm_data+pwmstyle)->PWM_DIV);}


    MAP_PWMGenEnable((pwm_data+pwmstyle)->PWM_BASE,
                 (pwm_data+pwmstyle)->PWM_GEN);
    MAP_PWMOutputState((pwm_data+pwmstyle)->PWM_BASE,(pwm_data+pwmstyle)->PWM_OUT_BIT,true);
    MAP_PWMGenPeriodSet((pwm_data+pwmstyle)->PWM_BASE,(pwm_data+pwmstyle)->PWM_GEN,
				(MAP_SysCtlClockGet()/((pwm_data+pwmstyle)->DIV))/fre);
    MAP_PWMPulseWidthSet((pwm_data+pwmstyle)->PWM_BASE,(pwm_data+pwmstyle)->PWM_OUT,
				(MAP_PWMGenPeriodGet((pwm_data+pwmstyle)->PWM_BASE,
				                 (pwm_data+pwmstyle)->PWM_GEN)*duty)/100);
}

void __attribute__((weak)) Motor_z()
{
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5,~GPIO_PIN_4|GPIO_PIN_5);
}

void __attribute__((weak)) Motor_f()
{
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_4|~GPIO_PIN_5);
}

//M0PWM0:PB6  M0PWM1:PB7
//M0PWM2:PB4  M0PWM3:PB5
//M0PWM4:PE4  M0PWM5:PE5
//M0PWM6:PC4  M0PWM7:PC5

//M1PWM0:PD0  M1PWM1:PD1
//M1PWM2:PA6  M1PWM3:PA7
//M1PWM4:PF0  M1PWM5:PF1
//M1PWM6:PF2  M1PWM7:PF3
void  MotoSet(int mode,int pwmstyle,long int limit,long int thorn)
{
    pwm_data_t *pwm_data;
    if(mode==0) {
        pwm_data=pwm_array0;
    }else if (mode==1){
        pwm_data=pwm_array1;
    }

    if(thorn<-limit)
        thorn=-limit;
    else if(thorn>limit)
        thorn= limit;
    else
    {
        if(thorn<0)
        {Motor_f();}
        else
        {Motor_z();}
    }
    PWMPulseWidthSet((pwm_data+pwmstyle)->PWM_BASE,(pwm_data+pwmstyle)->PWM_OUT,thorn);
}
