/*
 * fdc2214.c
 *
 *  Created on: 2018楠烇拷7閺堬拷20閺冿拷
 *      Author: 83456
 */

#include "fdc2214.h"

float capacitance_0 = 0.0f , capacitance_1 = 0.0f;
float capacitance_2 = 0.0f , capacitance_3 = 0.0f;

uint32_t ui32rawdata_0 = 0 , ui32rawdata_1 = 0 , ui32rawdata_2 = 0 , ui32rawdata_3 = 0;
float fsensor_0 = 0.0f , fsensor_1 = 0.0f , fsensor_2 = 0.0f , fsensor_3 = 0.0f;


/*!
 *  @brief      IIC閸愭DC2214
 *  @param      Slve_Addr     閸ｃ劋娆㈤崷鏉挎絻
 *  @param      reg           鐎靛嫬鐡ㄩ崳锟�
 *  @param      data          閺佺増宓�
 *  @since      v1.0
 *  Sample usage:       FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, 0xFFFF);
 */

void FDC2214_Write16(uint8_t Slve_Addr, uint8_t reg, uint16_t data)
{
    IIC_Start();
    IIC_Send_Byte(Slve_Addr << 1);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Send_Byte(data >> 8);
    IIC_Wait_Ack();
    IIC_Send_Byte(data & 0xFF);
    IIC_Wait_Ack();
    IIC_Stop();
}


/*!
 *  @brief      IIC鐠囩眽DC2214
 *  @param      Slve_Addr     閸ｃ劋娆㈤崷鏉挎絻
 *  @param      reg           鐎靛嫬鐡ㄩ崳锟�
 *  @return     鐎靛嫬鐡ㄩ崳銊ワ拷锟�
 *  @since      v1.0
 *  Sample usage:       FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
 */
uint16_t FDC2214_Read16(uint8_t Slve_Addr, uint8_t reg)
{
    uint16_t temp;

    IIC_Start();
    IIC_Send_Byte(Slve_Addr << 1);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte((Slve_Addr << 1) | 0x01);
    IIC_Wait_Ack();
    temp = (uint16_t)(IIC_Read_Byte(1) << 8);
    temp |= IIC_Read_Byte(0);
    IIC_Stop();

    return temp;
}

/*!
 *  @brief      鐠囪褰嘑DC2214娑擄拷娑擃亪锟芥岸浜鹃惃鍕祮閹广垹锟斤拷
 *  @param      channel     闁岸浜�
 *  @param      *data       鐠囪褰囬惃鍕殶閹癸拷
 *  @return     0閿涙艾銇戠拹銉幢1閿涙碍鍨氶崝锟�
 *  @since      v1.0
 *  Sample usage:       FDC2214_GetChannelData(FDC2214_Channel_0, &CH0_DATA);
 */
uint8_t FDC2214_GetChannelData(FDC2214_channel_t channel, uint32_t *data)
{
    int16_t timeout = 100;
    uint8_t dateReg_H;
    uint8_t dateReg_L;
    uint8_t bitUnreadConv;
    uint16_t status;
    uint32_t dataRead;

    status = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_STATUS);//鐠囪褰囬悩鑸碉拷浣哥槑鐎涙ê娅掗惃鍕拷锟�

    switch(channel)
    {
        case FDC2214_Channel_0:
            dateReg_H = FDC2214_DATA_CH0;
            dateReg_L = FDC2214_DATA_LSB_CH0;
            bitUnreadConv = 0x0008;
        break;

        case FDC2214_Channel_1:
            dateReg_H = FDC2214_DATA_CH1;
            dateReg_L = FDC2214_DATA_LSB_CH1;
            bitUnreadConv = 0x0004;
        break;

        case FDC2214_Channel_2:
            dateReg_H = FDC2214_DATA_CH2;
            dateReg_L = FDC2214_DATA_LSB_CH2;
            bitUnreadConv = 0x0002;
        break;

        case FDC2214_Channel_3:
            dateReg_H = FDC2214_DATA_CH3;
            dateReg_L = FDC2214_DATA_LSB_CH3;
            bitUnreadConv = 0x0001;
        break;
    }

    while(timeout && !(status & bitUnreadConv))//濡拷閺屻儲妲搁崥锔芥箒閺堫亣顕伴弫鐗堝祦
    {
        status = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_STATUS);
        timeout--;
    }
    if(timeout)
    {
        dataRead = (uint32_t)((FDC2214_Read16(FDC2214_ADDR_L, dateReg_H) & 0x0FFF )<< 16);
        dataRead |= FDC2214_Read16(FDC2214_ADDR_L, dateReg_L);
        *data = dataRead;

        return 1;
    }
    else
    {
        //鐡掑懏妞�
        return 0;
    }
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214娑擄拷娑擃亪锟芥岸浜鹃惃鍕祮閹广垺妞傞梻杈剧礉鏉烆剚宕查弮鍫曟？(tCx)=(CHx_RCOUNT鑰�16) / fREFx閵嗭拷
 *  @param      channel     闁岸浜�
 *  @param      rcount      CHx_RCOUNT
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetRcount(FDC2214_Channel_0, 0x0FFF);
 */
void FDC2214_SetRcount(FDC2214_channel_t channel, uint16_t rcount)
{
    if(rcount <= 0x00FF) return;

    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_RCOUNT_CH0, rcount);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_RCOUNT_CH1, rcount);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_RCOUNT_CH2, rcount);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_RCOUNT_CH3, rcount);
        break;
    }
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214娑擄拷娑擃亪锟芥岸浜鹃惃鍕紦缁斿妞傞梻杈剧礉娴ｇ竾C娴肩姵鍔呴崳銊ュ讲娴犮儱婀柅姘朵壕x瀵拷婵娴嗛幑顫閸撳秶菙鐎规矮绗呴弶銉礉瀵よ櫣鐝涢弮鍫曟？(tSx) = (CHx_SETTLECOUNT鑰�16) 姊� fREFx閵嗭拷
                CHx_SETTLECOUNT = 0x00, 0x01閺冿拷(tSx) = 32 姊� fREFx閵嗭拷
 *  @param      channel     闁岸浜�
 *  @param      count       CHx_SETTLECOUNT
 *  @since      v1.0
 *  @note       CHx_SETTLECOUNT > Vpk 鑴� fREFx 鑴� C 鑴� 锜篰2 / (32 鑴� IDRIVEX)
 *  Sample usage:       FDC2214_SetSettleCount(FDC2214_Channel_0, 0x00FF);
 */
void FDC2214_SetSettleCount(FDC2214_channel_t channel, uint16_t count)
{
    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_SETTLECOUNT_CH0, count);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_SETTLECOUNT_CH1, count);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_SETTLECOUNT_CH2, count);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_SETTLECOUNT_CH3, count);
        break;
    }
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214娑擄拷娑擃亪锟芥岸浜鹃惃鍕畱閺冨爼鎸撴０鎴犲芳,
                瀹割喖鍨庢导鐘冲妳閸ｃ劑鍘ょ純顕嗙窗
                0x01 -- 娴肩姵鍔呴崳銊╊暥閻滐拷0.01MHz閸滐拷8.75MHz
                0x02 -- 娴肩姵鍔呴崳銊╊暥閻滐拷5MHz閸滐拷10MHz
                閸楁洜顏导鐘冲妳閸ｃ劑鍘ょ純顕嗙窗
                0x01 -- 娴肩姵鍔呴崳銊╊暥閻滐拷0.01MHz閸滐拷10MHz
 *  @param      channel               闁岸浜�
 *  @param      frequency_select      閺冨爼鎸撻柅澶嬪
 *  @param      divider               閸掑棝顣堕崳顭掔礉fREFx = fCLK / CHx_FREF_DIVIDER閿涳拷
 *  @note       fREFx is > 4 鑴� fSENSOR(婢舵牠鍎碙C閹割垵宕遍崳銊╊暥閻滐拷)
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetChannelClock(FDC2214_Channel_0, 0x01, 0xFF);
 */
void FDC2214_SetChannelClock(FDC2214_channel_t channel, uint16_t set)
{
    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CLOCK_DIVIDERS_CH0, set);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CLOCK_DIVIDERS_CH1, set);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CLOCK_DIVIDERS_CH2, set);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CLOCK_DIVIDERS_CH3, set);
        break;
    }
}

/*!
 *  @brief      闁板秶鐤咺NTB瀵洝鍓兼稉顓熸焽閸旂喕鍏�
 *  @param      mode      1閿涙艾绱戞稉顓熸焽閿涳拷0閿涙艾鍙ф稉顓熸焽
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetDriveCurrent(FDC2214_Channel_0, FDC2214_Drive_Current_0_025);
 */ //???
void FDC2214_SetINTB(uint8_t mode)
{
    uint16_t temp = 0;

    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_CONFIG);
    temp &= 0xFF7F;
    if(mode)
        temp |= 0x0080;
    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, temp);

    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_ERROR_CONFIG);
    temp &= 0xFFFE;
    if(mode)
        temp |= 0x0001;
    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_ERROR_CONFIG, temp);
}

/*!
 *  @brief      濠碉拷濞茬眽DC2214閻ㄥ嫪绔存稉顏堬拷姘朵壕閿涘苯宕熼柅姘朵壕濡�崇础
 *  @param      channel     闁岸浜�
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetActiveChannel(FDC2214_Channel_0);
 */
void FDC2214_SetActiveChannel(FDC2214_channel_t channel)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_CONFIG);
    temp &= 0x3FFF;
    temp |= (uint16_t)(channel << 14);

    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214閻ㄥ嫬浼愭担婊勀佸蹇ョ窗濮濓絽鐖堕妴浣烘蒋閻姰锟斤拷
 *  @param      mode     0閿涙碍顒滅敮绋夸紣娴ｆ粣绱�1閿涙氨娼┑锟藉ú缁樐佸蹇涳拷澶嬪閵嗗倻婀�
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetSleepMode(0);
 */
void FDC2214_SetSleepMode(uint8_t mode)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_CONFIG);
    temp &= 0xDFFF;
    if(mode)
        temp |= 0x2000;

    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      FDC2214濠碉拷濞茬粯膩瀵繘锟藉瀚ㄩ妴锟�
 *  @param      mode     0閿涙艾鍙忛悽鍨ウ濠碉拷濞茬粯膩瀵骏绱�1閿涙矮缍嗛崝鐔哄芳濠碉拷濞茬粯膩瀵拷
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetCurrentMode(1);
 */
void FDC2214_SetCurrentMode(uint8_t mode)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_CONFIG);
    temp &= 0xF7FF;
    if(mode)
        temp |= 0x800;

    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214閺冨爼鎸撳┃锟�
 *  @param      src     0閿涙艾鍞撮柈銊︽闁界喐绨敍锟�1閿涙艾顦婚柈銊︽闁界喐绨�
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetClockSource(1);
 */
void FDC2214_SetClockSource(uint8_t src)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_CONFIG);
    temp &= 0xFDFF;
    if(src)
        temp |= 0x200;

    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      妤傛鏁稿ù浣风炊閹扮喎娅掓す鍗炲З閿涘苯褰ч柅鍌滄暏娴滃骸宕熼柅姘朵壕濡�崇础閵嗭拷
 *  @param      mode     0閿涙碍顒滅敮闈╃礄閺堬拷婢讹拷1.5mA閿涘绱�1閿涙岸鐝悽鍨ウ娴肩姵鍔呴崳銊┾攳閸旑煉绱�>1.5mA閿涳拷
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetHighCurrentMode(0);
 */
void FDC2214_SetHighCurrentMode(uint8_t mode)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_ADDR_L, FDC2214_CONFIG);
    temp &= 0xFFBF;
    if(mode)
        temp |= 0x40;

    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214閻ㄥ嚜UX CONFIG鐎靛嫬鐡ㄩ崳锟�
 *  @param      autoscan      閼奉亜濮╅幍顐ｅ伎濡�崇础 0閿涙艾鍙ч梻顓ㄧ礉1閿涙碍澧﹀锟�
 *  @param      channels      閼奉亜濮╅幍顐ｅ伎闁岸浜�
 *  @param      bandwidth     閺佹澘鐡у銈嗗皾閸ｃ劌鐢�规枻绱濇径褌绨径鏍劥LC閹割垵宕遍崳銊╊暥閻滐拷
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetMUX_CONFIG(1, FDC2214_Channel_Sequence_0_1_2, FDC2214_Bandwidth_10M);
 */
void FDC2214_SetMUX_CONFIG(uint16_t mux_config)
{
    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_MUX_CONFIG, mux_config);
}

void FDC2214_Set_CONFIG(uint16_t config)
{
    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_CONFIG, config);
}

/*!
 *  @brief      娴肩姵鍔呴崳銊ヮ槻娴ｏ拷
 *  @since      v1.0
 *  Sample usage:       FDC2214_Reset();
 */
void FDC2214_Reset(void)
{
    FDC2214_Write16(FDC2214_ADDR_L, FDC2214_RESET_DEV, 0x8000);
}

/*!
 *  @brief      鐠佸墽鐤咶DC2214閻ㄥ嫪绔存稉顏堬拷姘朵壕娴肩姵鍔呴崳銊┾攳閸斻劎鏁稿ù渚婄礉绾喕绻氶幐顖濆幢楠炲懎瀹抽崷锟�1.2V閸滐拷1.8V娑斿妫块妴锟�
 *  @param      channel      闁岸浜�
 *  @param      current      閻㈠灚绁︽径褍鐨�
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetDriveCurrent(FDC2214_Channel_0, FDC2214_Drive_Current_0_025);
 */
void FDC2214_SetDriveCurrent(FDC2214_channel_t channel, uint16_t current)
{

    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_DRIVE_CURRENT_CH0, current);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_DRIVE_CURRENT_CH1, current);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_DRIVE_CURRENT_CH2, current);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_ADDR_L, FDC2214_DRIVE_CURRENT_CH3, current);
        break;
    }
}

/*!
 *  @brief      FDC2214閸掓繂顫愰崠鏍у毐閺侊拷
 *  @return     1閿涙碍鍨氶崝鐕傜幢0閿涙艾銇戠拹锟�
 *  @since      v1.0
 *  Sample usage:       FDC2214_Init();
 */
void FDC2214_Init(void)
{
    FDC2214_Reset();
    FDC2214_SetRcount(FDC2214_Channel_0, RCOUNT_CHx_CONFIG_4);//2000us 鏉烆剚宕查崨銊︽埂
    FDC2214_SetRcount(FDC2214_Channel_1, RCOUNT_CHx_CONFIG_4);//2000us 鏉烆剚宕查崨銊︽埂
    FDC2214_SetRcount(FDC2214_Channel_2, RCOUNT_CHx_CONFIG_4);//2000us 鏉烆剚宕查崨銊︽埂
    FDC2214_SetRcount(FDC2214_Channel_3, RCOUNT_CHx_CONFIG_4);//2000us 鏉烆剚宕查崨銊︽埂
    FDC2214_SetSettleCount(FDC2214_Channel_0, SETTLECOUNT_CHx_CONFIG_4);//200 cycles 缁涘绶熼弮鍫曟？
    FDC2214_SetSettleCount(FDC2214_Channel_1, SETTLECOUNT_CHx_CONFIG_4);//200 cycles 缁涘绶熼弮鍫曟？
    FDC2214_SetSettleCount(FDC2214_Channel_2, SETTLECOUNT_CHx_CONFIG_4);//200 cycles 缁涘绶熼弮鍫曟？
    FDC2214_SetSettleCount(FDC2214_Channel_3, SETTLECOUNT_CHx_CONFIG_4);//200 cycles 缁涘绶熼弮鍫曟？
    FDC2214_SetChannelClock(FDC2214_Channel_0, CLOCK_DIVIDERS_CHx_CONFIG_4);//鐠佸墽鐤嗛弮鍫曟寭閸掑棝顣堕敍锟�1閸掑棝顣堕敍锟�40MHz
    FDC2214_SetChannelClock(FDC2214_Channel_1, CLOCK_DIVIDERS_CHx_CONFIG_4);//鐠佸墽鐤嗛弮鍫曟寭閸掑棝顣堕敍锟�1閸掑棝顣堕敍锟�40MHz
    FDC2214_SetChannelClock(FDC2214_Channel_2, CLOCK_DIVIDERS_CHx_CONFIG_4);//鐠佸墽鐤嗛弮鍫曟寭閸掑棝顣堕敍锟�1閸掑棝顣堕敍锟�40MHz
    FDC2214_SetChannelClock(FDC2214_Channel_3, CLOCK_DIVIDERS_CHx_CONFIG_4);//鐠佸墽鐤嗛弮鍫曟寭閸掑棝顣堕敍锟�1閸掑棝顣堕敍锟�40MHz
    FDC2214_SetINTB(0);//閸忔娊妫碔NTB娑擃厽鏌�
//    FDC2214_SetActiveChannel(FDC2214_Channel_0);//瀵拷閸氼垶锟芥岸浜�2
//    FDC2214_SetCurrentMode(0);//閸忋劎鏁稿ù浣圭负濞茬粯膩瀵拷
//    FDC2214_SetClockSource(1);//婢舵牠鍎撮弮鍫曟寭濠э拷
//    FDC2214_SetHighCurrentMode(0);//濮濓絽鐖堕悽鍨ウ娴肩姵鍔呴崳銊┾攳閸旓拷
    FDC2214_SetMUX_CONFIG(MUX_CONFIG_4);    //閸忔娊妫撮懛顏勫З閹殿偅寮块敍锟�10MHz鐢箑顔�
    FDC2214_SetDriveCurrent(FDC2214_Channel_0, DRIVE_CURRENT_CHx_CONFIG_4);//闁岸浜�0妞瑰崬濮╅悽鍨ウ0.081mA
    FDC2214_SetDriveCurrent(FDC2214_Channel_1, DRIVE_CURRENT_CHx_CONFIG_4);//闁岸浜�1妞瑰崬濮╅悽鍨ウ0.081mA
    FDC2214_SetDriveCurrent(FDC2214_Channel_2, DRIVE_CURRENT_CHx_CONFIG_4);//闁岸浜�2妞瑰崬濮╅悽鍨ウ0.081mA
    FDC2214_SetDriveCurrent(FDC2214_Channel_3, DRIVE_CURRENT_CHx_CONFIG_4);//闁岸浜�3妞瑰崬濮╅悽鍨ウ0.081mA
    FDC2214_SetSleepMode(0);//闁拷閸戣櫣娼惇鐘靛Ц閹緤绱濆锟芥慨瀣紣娴ｏ拷
    FDC2214_Set_CONFIG(CONFIG_4);
}

float KalmanFilter_0(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{

    float R = MeasureNoise_R;
    float Q = ProcessNiose_Q;

    static float x_last;
    float x_mid = x_last;
    float x_now;

    static float p_last;
    float p_mid ;
    float p_now;

    float kg;

    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=閸ｎ亜锛�

    /*
     *  閸椻�崇毜閺囧吋鎶ゅ▔銏㈡畱娴滄柧閲滈柌宥堫洣閸忣剙绱�
     */
    kg=p_mid/(p_mid+R);                 //kg娑撶皝alman filter閿涘 娑撳搫娅旀竟锟�
    x_now=x_mid+kg*(ResrcData-x_mid);   //娴兼媽顓搁崙铏规畱閺堬拷娴兼ê锟斤拷
    p_now=(1-kg)*p_mid;                 //閺堬拷娴兼ê锟界厧顕惔鏃傛畱covariance
    p_last = p_now;                     //閺囧瓨鏌奵ovariance 閸婏拷
    x_last = x_now;                     //閺囧瓨鏌婄化鑽ょ埠閻樿埖锟戒礁锟斤拷

    return x_now;

}

float KalmanFilter_1(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{

    float R = MeasureNoise_R;
    float Q = ProcessNiose_Q;

    static float x_last;
    float x_mid = x_last;
    float x_now;

    static float p_last;
    float p_mid ;
    float p_now;

    float kg;

    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=閸ｎ亜锛�

    /*
     *  閸椻�崇毜閺囧吋鎶ゅ▔銏㈡畱娴滄柧閲滈柌宥堫洣閸忣剙绱�
     */
    kg=p_mid/(p_mid+R);                 //kg娑撶皝alman filter閿涘 娑撳搫娅旀竟锟�
    x_now=x_mid+kg*(ResrcData-x_mid);   //娴兼媽顓搁崙铏规畱閺堬拷娴兼ê锟斤拷
    p_now=(1-kg)*p_mid;                 //閺堬拷娴兼ê锟界厧顕惔鏃傛畱covariance
    p_last = p_now;                     //閺囧瓨鏌奵ovariance 閸婏拷
    x_last = x_now;                     //閺囧瓨鏌婄化鑽ょ埠閻樿埖锟戒礁锟斤拷

    return x_now;

}

float KalmanFilter_2(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{

    float R = MeasureNoise_R;
    float Q = ProcessNiose_Q;

    static float x_last;
    float x_mid = x_last;
    float x_now;

    static float p_last;
    float p_mid ;
    float p_now;

    float kg;

    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=閸ｎ亜锛�

    /*
     *  閸椻�崇毜閺囧吋鎶ゅ▔銏㈡畱娴滄柧閲滈柌宥堫洣閸忣剙绱�
     */
    kg=p_mid/(p_mid+R);                 //kg娑撶皝alman filter閿涘 娑撳搫娅旀竟锟�
    x_now=x_mid+kg*(ResrcData-x_mid);   //娴兼媽顓搁崙铏规畱閺堬拷娴兼ê锟斤拷
    p_now=(1-kg)*p_mid;                 //閺堬拷娴兼ê锟界厧顕惔鏃傛畱covariance
    p_last = p_now;                     //閺囧瓨鏌奵ovariance 閸婏拷
    x_last = x_now;                     //閺囧瓨鏌婄化鑽ょ埠閻樿埖锟戒礁锟斤拷

    return x_now;

}

float KalmanFilter_3(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{

    float R = MeasureNoise_R;
    float Q = ProcessNiose_Q;

    static float x_last;
    float x_mid = x_last;
    float x_now;

    static float p_last;
    float p_mid ;
    float p_now;

    float kg;

    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=閸ｎ亜锛�

    /*
     *  閸椻�崇毜閺囧吋鎶ゅ▔銏㈡畱娴滄柧閲滈柌宥堫洣閸忣剙绱�
     */
    kg=p_mid/(p_mid+R);                 //kg娑撶皝alman filter閿涘 娑撳搫娅旀竟锟�
    x_now=x_mid+kg*(ResrcData-x_mid);   //娴兼媽顓搁崙铏规畱閺堬拷娴兼ê锟斤拷
    p_now=(1-kg)*p_mid;                 //閺堬拷娴兼ê锟界厧顕惔鏃傛畱covariance
    p_last = p_now;                     //閺囧瓨鏌奵ovariance 閸婏拷
    x_last = x_now;                     //閺囧瓨鏌婄化鑽ょ埠閻樿埖锟戒礁锟斤拷

    return x_now;

}


void FDC2214_Data_Analysis(void)
{
    if(0 == FDC2214_GetChannelData(FDC2214_Channel_0, &ui32rawdata_0))
        UARTprintf(0,"error\n");
    SysCtlDelay(10*(SysCtlClockGet()/3000));
    if(0 == FDC2214_GetChannelData(FDC2214_Channel_1, &ui32rawdata_1))
        UARTprintf(0,"error\n");
    SysCtlDelay(10*(SysCtlClockGet()/3000));
    if(0 == FDC2214_GetChannelData(FDC2214_Channel_2, &ui32rawdata_2))
        UARTprintf(0,"error\n");
    SysCtlDelay(10*(SysCtlClockGet()/3000));
    if(0 == FDC2214_GetChannelData(FDC2214_Channel_3, &ui32rawdata_3))
        UARTprintf(0,"error\n");

    // 0.298023 = 2 * 40,000,000 / 2^28
    fsensor_0 = (float)(ui32rawdata_0 * 0.298023);
    fsensor_1 = (float)(ui32rawdata_1 * 0.298023);
    fsensor_2 = (float)(ui32rawdata_2 * 0.298023);
    fsensor_3 = (float)(ui32rawdata_3 * 0.298023);

    // 1407.238661 = 1/ (2 * pi^2) * 18 * 10^(-6)
    capacitance_0 = 1407.238661 * 1.0e+12 / (fsensor_0*fsensor_0);
    capacitance_1 = 1407.238661 * 1.0e+12 / (fsensor_1*fsensor_1);
    capacitance_2 = 1407.238661 * 1.0e+12 / (fsensor_2*fsensor_2);
    capacitance_3 = 1407.238661 * 1.0e+12 / (fsensor_3*fsensor_3);

//        //閸椻�崇毜閺囧吋鎶ゅ▔銏犲箵閸ｏ拷
//        capacitance_0 = KalmanFilter_0(capacitance_0 , 0.05 , 5);
//        capacitance_1 = KalmanFilter_1(capacitance_1 , 0.05 , 5);
//        capacitance_2 = KalmanFilter_2(capacitance_2 , 0.05 , 5);
//        capacitance_3 = KalmanFilter_3(capacitance_3 , 0.05 , 5);

}
