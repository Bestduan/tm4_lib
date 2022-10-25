/*************
 坂本制作
I2C的仿51驱动配置文件

 2018.2.10
**************/
#include "APIS/I2C_drv.h"

void I2C_Delay(unsigned long y)
{
    SysCtlDelay(y*(SysCtlClockGet()/3000000));
}

//初始化IIC
void IIC_Init(void){

    //使能各端口
    // * GPIO_PA2__ -> SDA
    // * GPIO_PA3__ -> SCL
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SCL_OUT();
    SDA_OUT();

    IIC_SCL_H();
    IIC_SDA_H();
}


//产生IIC起始信号
void IIC_Start(void){

    SDA_OUT();     //sda线输出
    IIC_SDA_H();
    IIC_SCL_H();
    I2C_Delay(15);
    IIC_SDA_L();
    I2C_Delay(15);    //START:when CLK is high,DATA change form high to low
    IIC_SCL_L();    //钳住I2C总线，准备发送或接收数据
}


//产生IIC停止信号
void IIC_Stop(void){

    SDA_OUT();//sda线输出
    IIC_SCL_L();
    I2C_Delay(15);
    IIC_SDA_L();//STOP:when CLK is high DATA change form low to high
    I2C_Delay(15);
    IIC_SCL_H();
    I2C_Delay(15);
    IIC_SDA_H();
    I2C_Delay(15);//发送I2C总线结束信号
}


/* 等待应答信号到来
 * 返回值：1，接收应答失败
 *        0，接收应答成功
*/
uint8_t IIC_Wait_Ack(void){
    uint8_t ucErrTime=0;

    SDA_IN();      //SDA设置为输入
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

    IIC_SCL_L();//时钟输出0
    I2C_Delay(15);
    return 0;
} //end func


//产生ACK应答
void IIC_Ack(void){

    IIC_SCL_L();
    SDA_OUT();
    IIC_SDA_L();
    I2C_Delay(4);
    IIC_SCL_H();
    I2C_Delay(4);
    IIC_SCL_L();

    /*===新增===*/
    SDA_IN();   //释放SDA总线
}


//不产生ACK应答
void IIC_NAck(void)
{
    IIC_SCL_L();
    SDA_OUT();
    IIC_SDA_H();
    I2C_Delay(4);
    IIC_SCL_H();
    I2C_Delay(4);
    IIC_SCL_L();

    /*===新增===*/
    SDA_IN();   //释放SDA总线
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_L();//拉低时钟开始数据传输
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

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t IIC_Read_Byte(uint8_t ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}
















