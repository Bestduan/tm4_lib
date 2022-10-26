/*************
 �౾����
I2C�������ļ�

 2018.2.10
**************/
#include "I2C_Init.h"

//��I2C�Ķ˿�����
//I2C0:     SCL:PB2      SDA:PB3
//I2C1:     SCL:PA6      SDA:PA7
//I2C2:     SCL:PE4      SDA:PE5
//I2C3:     SCL:PD0      SDA:PD1
const i2c_data_t i2c_array[4]=
{
  {
    .SYSCTL_PERIPH_I2C=SYSCTL_PERIPH_I2C0,
    .SYSCTL_PERIPH_GPIO_I2C=SYSCTL_PERIPH_GPIOB,

    .GPIO_PORT_I2C_BASE=GPIO_PORTB_BASE,
    .GPIO_I2C_SCL=GPIO_PB2_I2C0SCL,
    .GPIO_I2C_SDA=GPIO_PB3_I2C0SDA,
    .GPIO_PIN_I2C_SCL=GPIO_PIN_2,
    .GPIO_PIN_I2C_SDA=GPIO_PIN_3,

    .I2C_BASE=I2C0_BASE
  },
  {
    .SYSCTL_PERIPH_I2C=SYSCTL_PERIPH_I2C1,
    .SYSCTL_PERIPH_GPIO_I2C=SYSCTL_PERIPH_GPIOA,

    .GPIO_PORT_I2C_BASE=GPIO_PORTA_BASE,
    .GPIO_I2C_SCL=GPIO_PA6_I2C1SCL,
    .GPIO_I2C_SDA=GPIO_PA7_I2C1SDA,
    .GPIO_PIN_I2C_SCL=GPIO_PIN_6,
    .GPIO_PIN_I2C_SDA=GPIO_PIN_7,

    .I2C_BASE=I2C1_BASE
  },
  {
    .SYSCTL_PERIPH_I2C=SYSCTL_PERIPH_I2C2,
    .SYSCTL_PERIPH_GPIO_I2C=SYSCTL_PERIPH_GPIOE,

    .GPIO_PORT_I2C_BASE=GPIO_PORTE_BASE,
    .GPIO_I2C_SCL=GPIO_PE4_I2C2SCL,
    .GPIO_I2C_SDA=GPIO_PE5_I2C2SDA,
    .GPIO_PIN_I2C_SCL=GPIO_PIN_4,
    .GPIO_PIN_I2C_SDA=GPIO_PIN_5,

    .I2C_BASE=I2C2_BASE
   },
   {
     .SYSCTL_PERIPH_I2C=SYSCTL_PERIPH_I2C3,
     .SYSCTL_PERIPH_GPIO_I2C=SYSCTL_PERIPH_GPIOD,

     .GPIO_PORT_I2C_BASE=GPIO_PORTD_BASE,
     .GPIO_I2C_SCL=GPIO_PD0_I2C3SCL,
     .GPIO_I2C_SDA=GPIO_PD1_I2C3SDA,
     .GPIO_PIN_I2C_SCL=GPIO_PIN_0,
     .GPIO_PIN_I2C_SDA=GPIO_PIN_1,

     .I2C_BASE=I2C3_BASE
    },
};
void ConfigureI2C(int mode)
{
    MAP_SysCtlPeripheralEnable(i2c_array[mode].SYSCTL_PERIPH_I2C);
    MAP_SysCtlPeripheralEnable(i2c_array[mode].SYSCTL_PERIPH_GPIO_I2C);

    MAP_GPIOPinConfigure(i2c_array[mode].GPIO_I2C_SCL);
    MAP_GPIOPinConfigure(i2c_array[mode].GPIO_I2C_SDA);
    MAP_GPIOPinTypeI2CSCL(i2c_array[mode].GPIO_PORT_I2C_BASE,
                      i2c_array[mode].GPIO_PIN_I2C_SCL);
    MAP_GPIOPinTypeI2C(i2c_array[mode].GPIO_PORT_I2C_BASE,
                   i2c_array[mode].GPIO_PIN_I2C_SDA);

    MAP_I2CMasterInitExpClk(i2c_array[mode].I2C_BASE,SysCtlClockGet(),true);
    MAP_I2CMasterEnable(i2c_array[mode].I2C_BASE);
}

/*
*************************************************************
*   ��  ��  ��: I2CWriteOneByte
*   ����˵��: I2Cд�Ĵ�������, Single Byte Write *�Ĵ�����ַ��ֵ��Ϊ8bit
*   ��ڲ���: ui32I2CBase -- I2C��ַ, ui8SlaveAddr -- �ӻ���ַ,
*   ui8RegAddr -- �Ĵ�����ַ, ui8RegData -- Ҫд��ֵ
*   ��  ��  ֵ: ui32ErrFlag -- �����־λ,0 -- success ,else fail
*              ____________________________________________
*  MASTER:  **| S | AD+W |     | RA |     | DATA |��       | P |**
*  SLAVE :  **|   |      | ACK |    | ACK |      | ACK |   |**
*************************************************************
*/
uint32_t I2CWriteOneByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t ui8RegData)
{
    uint8_t  ui8WriteBuffer = 0;   /* д������ */
    uint32_t ui32ErrFlag = 0;      /* �����־λ */

    while(I2CMasterBusy(ui32I2CBase));
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, false);

    //frame 2: �����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegAddr;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 3: �����/״̬�Ĵ���I2CMCS д "---0-011" ����start
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));
        return ui32ErrFlag;
    }
    //frame 4:�����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegData;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 5:�����/״̬�Ĵ���I2CMCS д "---0-101" ����stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_FINISH);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        return ui32ErrFlag;
    }
    return I2C_MASTER_ERR_NONE;
}

/*
*************************************************************
*   ��  ��  ��: I2CWriteTwoByte
*   ����˵��: I2Cд�Ĵ�������, ��8bit�Ĵ���д�����ֽ�����
*   ��ڲ���: ui32I2CBase -- I2C��ַ, ui8SlaveAddr -- �ӻ���ַ,
*            ui8RegAddr -- �Ĵ�����ַ, ui16RegData -- Ҫд��Ĵ�����16bit����
*                                                    ��λ��ǰ��λ�ں�-bit:15-0
*   ��  ��  ֵ: ui32ErrFlag -- �����־λ,0 -- success ,else fail
*              _________________________________________________________
*  MASTER:  **| S | AD+W |     | RA |     | DATA |��       | DATA |     | P |**
*  SLAVE :  **|   |      | ACK |    | ACK |      | ACK |      | ACK |   |**
*************************************************************
*/
uint32_t I2CWriteTwoByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint16_t ui16RegData)
{
    uint8_t  ui8WriteBuffer = 0;   /* д������ */
    uint32_t ui32ErrFlag = 0;      /* �����־λ */

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    //frame 1: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    ui8WriteBuffer = ui8SlaAddr;
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8WriteBuffer, false);

    //frame 2: �����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegAddr;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 3: �����/״̬�Ĵ���I2CMCS д "---0-011" ����start
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    //frame 4:�����ݼĴ���I2CMDRд���� -- �߰�λ
    ui8WriteBuffer = (uint8_t)( ui16RegData >> 8 );
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 5:�����/״̬�Ĵ���I2CMCS д "---0-001"
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_CONT);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    //frame 6:�����ݼĴ���I2CMDRд���� -- �Ͱ�λ
    ui8WriteBuffer = (uint8_t)( ui16RegData );
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame n:�����/״̬�Ĵ���I2CMCS д "---0-101" ����stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_FINISH);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }
    return I2C_MASTER_ERR_NONE;
}

/*
*************************************************************
*   ��  ��  ��: I2CWriteMultiByte
*   ����˵��: I2Cд�Ĵ�������, ��8bit�Ĵ���д����ֽ�����
*   ��ڲ���: ui32I2CBase -- I2C��ַ, ui8SlaveAddr -- �ӻ���ַ,
*            ui8RegAddr -- �Ĵ�����ַ, pui8RegData -- ָ��ָ��Ҫд��ֵ,
*            ui32WriteCount -- д������>=2
*   ��  ��  ֵ: ui32ErrFlag -- �����־λ,0 -- success ,else fail
*              _____________________________________________________________________
*  MASTER:  **| S | AD+W |     | RA |     | DATA |     | ... |��       | DATA |     | P |**
*  SLAVE :  **|   |      | ACK |    | ACK |      | ACK |     |...  |      | ACK |   |**
*************************************************************
*/
uint32_t I2CWriteMultiByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t *pui8RegData, uint32_t ui32WriteCount)
{
    uint8_t  ui8WriteBuffer = 0;     /* д������ */
    uint32_t ui32Counter = 0;        /* ������ */
    uint32_t ui32ErrFlag = 0;        /* �����־λ */

    // д�����������ٴ���
    while(ui32WriteCount < 2);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    //frame 1: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    ui8WriteBuffer = ui8SlaAddr;
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8WriteBuffer, false);

    //frame 2: �����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegAddr;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 3: �����/״̬�Ĵ���I2CMCS д "---0-011" ����start
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    //frame 4:�����ݼĴ���I2CMDRд����
    ui8WriteBuffer = pui8RegData[0];
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    for( ui32Counter = 0; ui32Counter < ui32WriteCount - 1; ui32Counter ++ )
    {
        // frame n-1:�����/״̬�Ĵ���I2CMCS д "---0-001"
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_CONT);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        // ��ѯERRORλ
        ui32ErrFlag = I2CMasterErr(ui32I2CBase);
        if(ui32ErrFlag != I2C_MASTER_ERR_NONE) {
            // ���ʹ���ֹͣ
            I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

            // ��ѯBUSYλ
            while(I2CMasterBusy(ui32I2CBase));

            return ui32ErrFlag;
        }

        //frame n-1:�����ݼĴ���I2CMDRд����
        ui8WriteBuffer = pui8RegData[ ui32Counter + 1 ];
        I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);
    }

    // frame n:�����/״̬�Ĵ���I2CMCS д "---0-101" ����stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_FINISH);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }
    return I2C_MASTER_ERR_NONE;
}

/*
*************************************************************
*   ��  ��  ��: I2CReadOneByte
*   ����˵��: I2C���Ĵ�������,  ��һ��8bit�Ĵ�����һ�ֽ�����
*   ��ڲ���: ui32I2CBase -- I2C��ַ, ui8SlaveAddr -- �ӻ���ַ,
*            ui8RegAddr -- �Ĵ�����ַ, pui8RegData -- ָ�����ݴ�ű���
*   ��  ��  ֵ: ui32ErrFlag -- �����־λ,0 -- success ,else fail
*              ______________________________________________________________
*  MASTER:  **| S | AD+W |     | RA |     | S | AD+R |��       |      | NACK | P |**
*  SLAVE :  **|   |      | ACK |    | ACK |   |      | ACK | DATA |      |   |**
*************************************************************
*/
uint32_t I2CReadOneByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t *pui8RegData)
{
    uint8_t  ui8WriteBuffer = 0;       /* д������ */
    uint8_t  ui8ReadBuffer = 0;        /* �������� */
    uint32_t ui32ErrFlag = 0;          /* �����־λ */

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // frame 1: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    ui8WriteBuffer = ui8SlaAddr;
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8WriteBuffer, false);

    // frame 2: �����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegAddr;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 3: �����/״̬�Ĵ���I2CMCS д "---0-011" ����start ������stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE) {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    /******************��������ظ���ʼ���н��еĽ���***************/

    // frame 4: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, true);

    // frame 5: �����/״̬�Ĵ���I2CMCS д "---01011" �����ظ���ʼ,������Ӧ��Ľ���
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_SINGLE_RECEIVE);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    // frame 6: ���������ݼĴ���I2CMDR����һ������
    ui8ReadBuffer =I2CMasterDataGet(ui32I2CBase);

    // ��ֵ
    *pui8RegData = ui8ReadBuffer;

    //  return 0 to indicates transmit success
    return I2C_MASTER_ERR_NONE;
}

/*
*************************************************************
*   ��  ��  ��: I2CReadTwoByte
*   ����˵��: I2C���Ĵ�������,  ��һ��8bit�Ĵ����������ֽ�����
*   ��ڲ���: ui32I2CBase -- i2c��ַ, ui8SlaveAddr -- �ӻ���ַ,
*            ui8RegAddr -- �Ĵ�����ַ, pui16RegData -- ָ�����ݴ�ű���
*   ��  ��  ֵ: ui32ErrFlag -- �����־λ,0 -- success ,else fail
*              ____________________________________________________________________________
*  MASTER:  **| S | AD+W |     | RA |     | S | AD+R |��       |      | ACK  |      | NACK | P |**
*  SLAVE :  **|   |      | ACK |    | ACK |   |      | ACK | DATA |      | DATA |      |   |**
*************************************************************
*/
uint32_t I2CReadTwoByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint16_t *pui16RegData)
{
    uint8_t  ui8WriteBuffer = 0;          /* д������ */
    uint32_t ui32ReadBuffer[2] = {0};   /* �������� */
    uint16_t ui16RegData = 0;             /* �����ݴ� */
    uint32_t ui32ErrFlag = 0;             /* �����־λ */

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // frame 1: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    ui8WriteBuffer = ui8SlaAddr;
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8WriteBuffer, false);

    // frame 2: �����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegAddr;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 3: �����/״̬�Ĵ���I2CMCS д "---0-011" ����start ������stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    /******************��������ظ���ʼ���н��еĽ���***************/

    // frame 4: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, true);

    // frame 5: �����/״̬�Ĵ���I2CMCS д "---01011" �����ظ���ʼ
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    // frame 6: ���������ݼĴ���I2CMDR����һ������, Ĭ�ϸ�8bit(MSB)
    ui32ReadBuffer[0] = I2CMasterDataGet(ui32I2CBase);

    // frame 7: �����/״̬�Ĵ���I2CMCS д "---00101" ����stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    // frame 8: ���������ݼĴ���I2CMDR���ڶ�������, Ĭ�ϵ�8bit(LSB)
    ui32ReadBuffer[1] = I2CMasterDataGet(ui32I2CBase);

    // ���ݰ�Ĭ�ϸߵ�λ���
    ui16RegData = (uint16_t)((ui32ReadBuffer[0] << 8) | ui32ReadBuffer[1]);

    // ��ֵ
    *pui16RegData = ui16RegData;
    return I2C_MASTER_ERR_NONE;
}

/*
*************************************************************
*   ��  ��  ��: I2CReadMultiByte
*   ����˵��: I2C���Ĵ�������,  ��һ��8bit�Ĵ���������ֽ�����
*   ��ڲ���: ui32I2CBase -- i2c��ַ, ui8SlaveAddr -- �ӻ���ַ,
*            ui8RegAddr -- �Ĵ�����ַ, pui8RegData -- ָ�������ݱ���
*            ui32ReadCount -- Ҫ�����ֽ���
*   ��  ��  ֵ: ui32ErrFlag -- �����־λ, 0 -- success, else fail
*              ________________________________________________________________________________
*  MASTER:  **| S | AD+W |     | RA |     | S | AD+R |��       |      | ACK |     | ... | NACK | P |**
*  SLAVE :  **|   |      | ACK |    | ACK |   |      | ACK | DATA |     | ... |     |      |   |**
*************************************************************
*/
uint32_t I2CReadMultiByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr,uint8_t *pui8RegData, uint32_t ui32ReadCount)
{
    uint8_t  ui8WriteBuffer = 0;       /* д������ */
    uint32_t ui32ReadBuffer = 0;       /* �������� */
    uint32_t ui32Counter    = 0;       /* ������ */
    uint32_t ui32ErrFlag    = 0;       /* �����־λ */

    // ����������С��2ʱ����
    while(ui32ReadCount < 2);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // frame 1: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    ui8WriteBuffer = ui8SlaAddr;
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8WriteBuffer, false);

    // frame 2: �����ݼĴ���I2CMDRд����
    ui8WriteBuffer = ui8RegAddr;
    I2CMasterDataPut(ui32I2CBase, ui8WriteBuffer);

    // frame 3: �����/״̬�Ĵ���I2CMCS д "---0-011" ����start ������stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    /******************��������ظ���ʼ���н��еĽ���***************/

    // frame 4: ��ӻ���ַI2CMSA�Ĵ���д�ӻ���ַ
    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, true);

    // frame 5: �����/״̬�Ĵ���I2CMCS д "---01011" �����ظ���ʼ
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_START);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    // frame 6: ���������ݼĴ���I2CMDR����һ������
    ui32ReadBuffer = I2CMasterDataGet(ui32I2CBase);
    pui8RegData[ 0 ] = (uint8_t)ui32ReadBuffer;

    for(ui32Counter = 0; ui32Counter < ui32ReadCount - 2; ui32Counter ++ ) {
        // frame n-1: �����/״̬�Ĵ���I2CMCS д "---01001" ����Ӧ��
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        // ��ѯERRORλ
        ui32ErrFlag = I2CMasterErr(ui32I2CBase);
        if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
        {
            // ���ʹ���ֹͣ
            I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);

            // ��ѯBUSYλ
            while(I2CMasterBusy(ui32I2CBase));

            return ui32ErrFlag;
        }

        // frame n-1: ���������ݼĴ���I2CMDR��һ������
        ui32ReadBuffer = I2CMasterDataGet(ui32I2CBase);
        pui8RegData[ ui32Counter + 1 ] = (uint8_t)ui32ReadBuffer;
    }

    // frame n: �����/״̬�Ĵ���I2CMCS д "---00101" ����stop
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    // ��ѯBUSYλ
    while(I2CMasterBusy(ui32I2CBase));

    // ��ѯERRORλ
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        // ���ʹ���ֹͣ
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);

        // ��ѯBUSYλ
        while(I2CMasterBusy(ui32I2CBase));

        return ui32ErrFlag;
    }

    // frame n: ���������ݼĴ���I2CMDR�����һ������
    ui32ReadBuffer = I2CMasterDataGet(ui32I2CBase);

    pui8RegData[ ui32ReadCount - 1 ] = (uint8_t)ui32ReadBuffer;
    return I2C_MASTER_ERR_NONE;
}
