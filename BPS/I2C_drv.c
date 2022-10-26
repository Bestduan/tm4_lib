/*************
 �౾����
I2C�ķ�51���������ļ�

 2018.2.10
**************/
#include "I2C_drv.h"

void I2C_Delay(unsigned long y)
{
    SysCtlDelay(y*(SysCtlClockGet()/3000000));
}

//��ʼ��IIC
void IIC_Init(void){

    //ʹ�ܸ��˿�
    // * GPIO_PA2__ -> SDA
    // * GPIO_PA3__ -> SCL
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SCL_OUT();
    SDA_OUT();

    IIC_SCL_H();
    IIC_SDA_H();
}


//����IIC��ʼ�ź�
void IIC_Start(void){

    SDA_OUT();     //sda�����
    IIC_SDA_H();
    IIC_SCL_H();
    I2C_Delay(15);
    IIC_SDA_L();
    I2C_Delay(15);    //START:when CLK is high,DATA change form high to low
    IIC_SCL_L();    //ǯסI2C���ߣ�׼�����ͻ��������
}


//����IICֹͣ�ź�
void IIC_Stop(void){

    SDA_OUT();//sda�����
    IIC_SCL_L();
    I2C_Delay(15);
    IIC_SDA_L();//STOP:when CLK is high DATA change form low to high
    I2C_Delay(15);
    IIC_SCL_H();
    I2C_Delay(15);
    IIC_SDA_H();
    I2C_Delay(15);//����I2C���߽����ź�
}


/* �ȴ�Ӧ���źŵ���
 * ����ֵ��1������Ӧ��ʧ��
 *        0������Ӧ��ɹ�
*/
uint8_t IIC_Wait_Ack(void){
    uint8_t ucErrTime=0;

    SDA_IN();      //SDA����Ϊ����
    IIC_SDA_H();
    I2C_Delay(1);
    IIC_SCL_H();
    I2C_Delay(1);

    while(READ_SDA){

        ucErrTime++;
        if(ucErrTime>250){

            IIC_Stop();
            return 1;
        }//end if
    }//end while

    IIC_SCL_L();//ʱ�����0
    I2C_Delay(15);
    return 0;
} //end func


//����ACKӦ��
void IIC_Ack(void){

    IIC_SCL_L();
    SDA_OUT();
    IIC_SDA_L();
    I2C_Delay(4);
    IIC_SCL_H();
    I2C_Delay(4);
    IIC_SCL_L();

    /*===����===*/
    SDA_IN();   //�ͷ�SDA����
}


//������ACKӦ��
void IIC_NAck(void)
{
    IIC_SCL_L();
    SDA_OUT();
    IIC_SDA_H();
    I2C_Delay(4);
    IIC_SCL_H();
    I2C_Delay(4);
    IIC_SCL_L();

    /*===����===*/
    SDA_IN();   //�ͷ�SDA����
}

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_L();//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
        if(txd&0x80)
            IIC_SDA_H();
        else
            IIC_SDA_L();
        txd<<=1;
        I2C_Delay(2);
        IIC_SCL_H();
        I2C_Delay(2);
        IIC_SCL_L();
        I2C_Delay(2);
    }
}

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC_Read_Byte(uint8_t ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        IIC_SCL_L();
        I2C_Delay(2);
        IIC_SCL_H();
        receive<<=1;
        if(READ_SDA)receive++;
        I2C_Delay(1);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}
















