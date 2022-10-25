/*
 * SPI_dev.c
 *
 *  Created on: 2018年9月19日
 *      Author: duan
 */
#include "APIS/SPI_drv.h"


void SPI_Delayus(unsigned long y)
{
    SysCtlDelay(y*(SysCtlClockGet()/3000000));
}


void SPI_Init(void)
{
  //使能GPIO端口
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

  //SCLK CS DOUT 输出
  GPIOPinTypeGPIOOutput(SPI_SCLK_GPIO_PORT,SPI_SCLK_GPIO_PIN);
  GPIOPinTypeGPIOOutput(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN);
  GPIOPinTypeGPIOOutput(SPI_DOUT_GPIO_PORT,SPI_DOUT_GPIO_PIN);
  //SYNC RESET 输出
  GPIOPinTypeGPIOOutput(SYNC_GPIO_PORT,SYNC_GPIO_PIN);
  GPIOPinTypeGPIOOutput(RESET_GPIO_PORT,RESET_GPIO_PIN);
  //初始化置位
  SPI_SCLK_L();
  SPI_CS_H();   //片选拉高
  SPI_DOUT_H();
  SPI_SYNC_H();
  SPI_RESET_H();

  //DIN 输入
  GPIOPinTypeGPIOInput(SPI_DIN_GPIO_PORT,SPI_DIN_GPIO_PIN);
  //DRDY 输入
  GPIOPinTypeGPIOInput(DRDY_GPIO_PORT,DRDY_GPIO_PIN);
  //置位

}


/*
*************************************************************
*   函  数  名: SPI_Write_Byte
*   功能说明: SPI发送一个字节 MICROWIRE格式
*   入口参数: TxByte: 发送的数据字节
*   返  回  值: none
*************************************************************
*/

void SPI_Write_Byte(uint8_t TxByte)
{
  uint8_t i = 0;

  for(i=0; i<8; i++)      //一个字节8bit需要循环8次
  {
    SPI_SCLK_H();       //时钟线拉高

        /** 发送 */
        if(TxByte & 0x80)
        {
          SPI_DOUT_H();         //如果即将要发送的位为 1 则置高IO引脚
        }
        else
        {
          SPI_DOUT_L();         //如果即将要发送的位为 0 则置低IO引脚
        }

        TxByte = TxByte << 1;   //数据左移一位，先发送的是最高位

        SPI_Delayus(1);       //valid data setup time: >50ns && SCLK period > 0.53us
        SPI_SCLK_L();       //时钟线置低
        SPI_Delayus(1);       //valid data hold time: >50ns && SCLK period > 0.53us
  }

}

/*
*************************************************************
*   函  数  名: SPI_Read_Byte
*   功能说明: SPI接收一个字节 MICROWIRE格式  时序上只需保证t6和SCLK周期即可
*   入口参数: none
*   返  回  值: 接收到的字节
*************************************************************
*/

uint8_t SPI_Read_Byte(void)
{
  uint8_t i;
  uint8_t data = 0;

  for(i=0; i<8; i++)
  {
    SPI_SCLK_H();         //时钟线拉高
    data = data << 1;       //数据从MSB到LSB
    SPI_Delayus(1);         //SCLK period > 0.53us
    SPI_SCLK_L();         //时钟线置低
    if(SPI_READ_DIN())        //数据为1
    {
      data = data | 0x01;
    }
    else              //数据为0
    {
      data = data & 0xFE;
    }
//    data = data | SPI_READ_DIN(); //读数据
    SPI_Delayus(1);         //SCLK period > 0.53us
  }

  return data;
}




