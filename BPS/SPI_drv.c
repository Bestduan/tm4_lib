/*
 * SPI_dev.c
 *
 *  Created on: 2018��9��19��
 *      Author: duan
 */
#include "SPI_drv.h"


void SPI_Delayus(unsigned long y)
{
    SysCtlDelay(y*(SysCtlClockGet()/3000000));
}


void SPI_Init(void)
{
  //ʹ��GPIO�˿�
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

  //SCLK CS DOUT ���
  GPIOPinTypeGPIOOutput(SPI_SCLK_GPIO_PORT,SPI_SCLK_GPIO_PIN);
  GPIOPinTypeGPIOOutput(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN);
  GPIOPinTypeGPIOOutput(SPI_DOUT_GPIO_PORT,SPI_DOUT_GPIO_PIN);
  //SYNC RESET ���
  GPIOPinTypeGPIOOutput(SYNC_GPIO_PORT,SYNC_GPIO_PIN);
  GPIOPinTypeGPIOOutput(RESET_GPIO_PORT,RESET_GPIO_PIN);
  //��ʼ����λ
  SPI_SCLK_L();
  SPI_CS_H();   //Ƭѡ����
  SPI_DOUT_H();
  SPI_SYNC_H();
  SPI_RESET_H();

  //DIN ����
  GPIOPinTypeGPIOInput(SPI_DIN_GPIO_PORT,SPI_DIN_GPIO_PIN);
  //DRDY ����
  GPIOPinTypeGPIOInput(DRDY_GPIO_PORT,DRDY_GPIO_PIN);
  //��λ

}


/*
*************************************************************
*   ��  ��  ��: SPI_Write_Byte
*   ����˵��: SPI����һ���ֽ� MICROWIRE��ʽ
*   ��ڲ���: TxByte: ���͵������ֽ�
*   ��  ��  ֵ: none
*************************************************************
*/

void SPI_Write_Byte(uint8_t TxByte)
{
  uint8_t i = 0;

  for(i=0; i<8; i++)      //һ���ֽ�8bit��Ҫѭ��8��
  {
    SPI_SCLK_H();       //ʱ��������

        /** ���� */
        if(TxByte & 0x80)
        {
          SPI_DOUT_H();         //�������Ҫ���͵�λΪ 1 ���ø�IO����
        }
        else
        {
          SPI_DOUT_L();         //�������Ҫ���͵�λΪ 0 ���õ�IO����
        }

        TxByte = TxByte << 1;   //��������һλ���ȷ��͵������λ

        SPI_Delayus(1);       //valid data setup time: >50ns && SCLK period > 0.53us
        SPI_SCLK_L();       //ʱ�����õ�
        SPI_Delayus(1);       //valid data hold time: >50ns && SCLK period > 0.53us
  }

}

/*
*************************************************************
*   ��  ��  ��: SPI_Read_Byte
*   ����˵��: SPI����һ���ֽ� MICROWIRE��ʽ  ʱ����ֻ�豣֤t6��SCLK���ڼ���
*   ��ڲ���: none
*   ��  ��  ֵ: ���յ����ֽ�
*************************************************************
*/

uint8_t SPI_Read_Byte(void)
{
  uint8_t i;
  uint8_t data = 0;

  for(i=0; i<8; i++)
  {
    SPI_SCLK_H();         //ʱ��������
    data = data << 1;       //���ݴ�MSB��LSB
    SPI_Delayus(1);         //SCLK period > 0.53us
    SPI_SCLK_L();         //ʱ�����õ�
    if(SPI_READ_DIN())        //����Ϊ1
    {
      data = data | 0x01;
    }
    else              //����Ϊ0
    {
      data = data & 0xFE;
    }
//    data = data | SPI_READ_DIN(); //������
    SPI_Delayus(1);         //SCLK period > 0.53us
  }

  return data;
}




