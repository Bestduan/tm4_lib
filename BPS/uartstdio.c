/*************
坂本制作
UART的配置文件

 2018.2.10
**************/
#include "uartstdio.h"

uart_data_t uart_array[8]={
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART0,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOA,

          .GPIO_PORT_UART_BASE=GPIO_PORTA_BASE,
          .GPIO_UART_TX=GPIO_PA1_U0TX,
          .GPIO_UART_RX=GPIO_PA0_U0RX,
          .GPIO_PIN_UART=(GPIO_PIN_0 | GPIO_PIN_1),

          .UART_BASE=UART0_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART1,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOB,

          .GPIO_PORT_UART_BASE=GPIO_PORTB_BASE,
          .GPIO_UART_TX=GPIO_PB1_U1TX,
          .GPIO_UART_RX=GPIO_PB0_U1RX,
          .GPIO_PIN_UART=(GPIO_PIN_0 | GPIO_PIN_1),

          .UART_BASE=UART1_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART2,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOD,

          .GPIO_PORT_UART_BASE=GPIO_PORTD_BASE,
          .GPIO_UART_TX=GPIO_PD7_U2TX,
          .GPIO_UART_RX=GPIO_PD6_U2RX,
          .GPIO_PIN_UART=(GPIO_PIN_6 | GPIO_PIN_7),

          .UART_BASE=UART2_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART3,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOC,

          .GPIO_PORT_UART_BASE=GPIO_PORTC_BASE,
          .GPIO_UART_TX=GPIO_PC7_U3TX,
          .GPIO_UART_RX=GPIO_PC6_U3RX,
          .GPIO_PIN_UART=(GPIO_PIN_6 | GPIO_PIN_7),

          .UART_BASE=UART3_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART4,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOC,

          .GPIO_PORT_UART_BASE=GPIO_PORTC_BASE,
          .GPIO_UART_TX=GPIO_PC5_U4TX,
          .GPIO_UART_RX=GPIO_PC4_U4RX,
          .GPIO_PIN_UART=(GPIO_PIN_4 | GPIO_PIN_5),

          .UART_BASE=UART4_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART5,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOE,

          .GPIO_PORT_UART_BASE=GPIO_PORTE_BASE,
          .GPIO_UART_TX=GPIO_PE5_U5TX,
          .GPIO_UART_RX=GPIO_PE4_U5RX,
          .GPIO_PIN_UART=(GPIO_PIN_4 | GPIO_PIN_5),

          .UART_BASE=UART5_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART6,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOD,

          .GPIO_PORT_UART_BASE=GPIO_PORTD_BASE,
          .GPIO_UART_TX=GPIO_PD5_U6TX,
          .GPIO_UART_RX=GPIO_PD4_U6RX,
          .GPIO_PIN_UART=(GPIO_PIN_4 | GPIO_PIN_5),

          .UART_BASE=UART6_BASE,
    },
    {
          .SYSCTL_PERIPH_UART=SYSCTL_PERIPH_UART7,
          .SYSCTL_PERIPH_GPIO_UART=SYSCTL_PERIPH_GPIOE,

          .GPIO_PORT_UART_BASE=GPIO_PORTE_BASE,
          .GPIO_UART_TX=GPIO_PE1_U7TX,
          .GPIO_UART_RX=GPIO_PE0_U7RX,
          .GPIO_PIN_UART=(GPIO_PIN_0 | GPIO_PIN_1),

          .UART_BASE=UART7_BASE,
    },
};

#if UART_DMA==1
#if defined(ewarm)
#pragma data_alignment=1024
uint8_t ui8ControlTable[1024];
#elif defined(ccs)
#pragma DATA_ALIGN(ui8ControlTable, 1024)
uint8_t ui8ControlTable[1024];
#else
uint8_t ui8ControlTable[1024] __attribute__ ((aligned(1024)));
#endif
#endif

int8_t  UART_rec[UART_LEN];
static const char * const g_pcHex = "0123456789abcdef";

#if UART_INT==1
volatile bool bUARTflag=false;
static const uint32_t g_ui32UARTInt[8] =
{
    INT_UART0, INT_UART1, INT_UART2,INT_UART3,
    INT_UART4, INT_UART5, INT_UART6,INT_UART7
};
#endif

void UARTStdioConfig(int mode, uint32_t ui32Baud, uint32_t ui32SrcClock)
{
    MAP_UARTConfigSetExpClk(uart_array[mode].UART_BASE, ui32SrcClock, ui32Baud,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));
    MAP_UARTFIFODisable(uart_array[mode].UART_BASE);
    MAP_UARTEnable(uart_array[mode].UART_BASE);
}


#if UART_DMA==1
void ConfigureUART_DMA(int mode,int8_t *RXstr,int8_t *TXstr)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    MAP_UARTDMAEnable(uart_array[mode].UART_BASE, UART_DMA_RX | UART_DMA_TX);
    HWREG(uart_array[mode].UART_BASE + UART_O_CTL) |= UART_CTL_LBE;
    MAP_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART0RX+mode*14,
                                    UDMA_ATTR_ALTSELECT     |
                                    UDMA_ATTR_USEBURST      |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);
    MAP_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART0TX+mode*14,
                                    UDMA_ATTR_ALTSELECT     |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);

    MAP_uDMAChannelControlSet(UDMA_CHANNEL_UART0RX+mode*14 | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8    |
                              UDMA_ARB_4);
    MAP_uDMAChannelControlSet(UDMA_CHANNEL_UART0TX+mode*14 | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_8    | UDMA_DST_INC_NONE |
                              UDMA_ARB_4);


    MAP_uDMAChannelTransferSet(UDMA_CHANNEL_UART0RX+mode*14 | UDMA_PRI_SELECT,
                               UDMA_MODE_AUTO,
                               (void *)(uart_array[mode].UART_BASE + UART_O_DR),
                               RXstr, sizeof(RXstr));
    MAP_uDMAChannelTransferSet(UDMA_CHANNEL_UART0TX+mode*14 | UDMA_PRI_SELECT,
                               UDMA_MODE_AUTO, TXstr,
                               (void *)(uart_array[mode].UART_BASE + UART_O_DR),
                               sizeof(TXstr));

    MAP_uDMAChannelAttributeEnable(UDMA_CHANNEL_UART0RX+mode*14, UDMA_ATTR_USEBURST);
    MAP_uDMAChannelAttributeEnable(UDMA_CHANNEL_UART0TX+mode*14, UDMA_ATTR_USEBURST);

    MAP_uDMAChannelEnable(UDMA_CHANNEL_UART0RX+mode*14);
    MAP_uDMAChannelEnable(UDMA_CHANNEL_UART0TX+mode*14);

    MAP_uDMAEnable();
    MAP_uDMAControlBaseSet(ui8ControlTable);
}
#endif


#if UART_INT==1
//UART0 RX:PA0 TX:PA1   //UART1 RX:PB0 TX:PB1
//UART2 RX:PD6 TX:PD7   //UART3 RX:PC6 TX:PC7
//UART4 RX:PC4 TX:PC5   //UART5 RX:PE4 TX:PE5
//UART6 RX:PD4 TX:PD5   //UART7 RX:PE0 TX:PE1
void ConfigureINTUART(int mode, int band, void (*uart_pfnHandler)(void))
{
    MAP_SysCtlPeripheralEnable(uart_array[mode].SYSCTL_PERIPH_UART);
    MAP_SysCtlPeripheralEnable(uart_array[mode].SYSCTL_PERIPH_GPIO_UART);

    if(mode==2)
    {
        HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
        HWREG(GPIO_PORTD_BASE+GPIO_O_CR)=GPIO_PIN_7;
    }

    MAP_GPIOPinConfigure(uart_array[mode].GPIO_UART_RX);
    MAP_GPIOPinConfigure(uart_array[mode].GPIO_UART_TX);
    MAP_GPIOPinTypeUART(uart_array[mode].GPIO_PORT_UART_BASE,
                    uart_array[mode].GPIO_PIN_UART);

    MAP_UARTClockSourceSet(uart_array[mode].UART_BASE,UART_CLOCK_PIOSC);
    UARTStdioConfig(mode,band,16000000);
    MAP_UARTIntDisable(uart_array[mode].UART_BASE, 0xFFFFFFFF);
    MAP_UARTIntEnable(uart_array[mode].UART_BASE, UART_INT_RX | UART_INT_RT);
    MAP_IntEnable(g_ui32UARTInt[mode]);
    UARTIntRegister(uart_array[mode].UART_BASE,uart_pfnHandler);
}

void UART_MSP_Handler(int mode)
{
    uint32_t IntStatus;
    IntStatus=UARTIntStatus(uart_array[mode].UART_BASE,true);
    UARTIntClear(uart_array[mode].UART_BASE,IntStatus);
    bUARTflag=true;
}

#endif

//UART0 RX:PA0 TX:PA1   //UART1 RX:PB0 TX:PB1
//UART2 RX:PD6 TX:PD7   //UART3 RX:PC6 TX:PC7
//UART4 RX:PC4 TX:PC5   //UART5 RX:PE4 TX:PE5
//UART6 RX:PD4 TX:PD5   //UART7 RX:PE0 TX:PE1
void ConfigureUART(int mode, int band)
{
    MAP_SysCtlPeripheralEnable(uart_array[mode].SYSCTL_PERIPH_UART);
    MAP_SysCtlPeripheralEnable(uart_array[mode].SYSCTL_PERIPH_GPIO_UART);

    if(mode==2)
    {
        HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
        HWREG(GPIO_PORTD_BASE+GPIO_O_CR)=GPIO_PIN_7;
    }

    MAP_GPIOPinConfigure(uart_array[mode].GPIO_UART_RX);
    MAP_GPIOPinConfigure(uart_array[mode].GPIO_UART_TX);
    MAP_GPIOPinTypeUART(uart_array[mode].GPIO_PORT_UART_BASE,
                    uart_array[mode].GPIO_PIN_UART);

    MAP_UARTClockSourceSet(uart_array[mode].UART_BASE,UART_CLOCK_PIOSC);
    UARTStdioConfig(mode,band,16000000);
}

int UARTRead(int mode,int8_t *pui8Buffer)
{
    int m,i=0;
    for(m=0;m<UART_LEN;m++)
    {
        *(pui8Buffer+m)='\0';
    }
    while( ( *pui8Buffer=(int8_t)
        UARTCharGetNonBlocking(uart_array[mode].UART_BASE) ) != -1)
    {
        pui8Buffer++;
        i++;
    }
    *pui8Buffer='\0';
    if(i==0)
    {
        return 1;
    }
    i=0;
    return 0;
}

int UARTwrite(int mode,int8_t *pcBuf, uint32_t ui32Len)
{
    unsigned int uIdx;
    ASSERT(uart_array[mode].UART_BASE != 0);
    ASSERT(pcBuf != 0);
    for(uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        if(pcBuf[uIdx] == '\n')
        {
            MAP_UARTCharPut(uart_array[mode].UART_BASE, '\r');
        }
        MAP_UARTCharPut(uart_array[mode].UART_BASE, pcBuf[uIdx]);
    }
    return(uIdx);
}

void UARTvprintf(int mode, int8_t *pcString, va_list vaArgP)
{
    uint32_t ui32Idx, ui32Value, ui32Pos, ui32Count, ui32Base, ui32Neg;
    double value_f=0.0f;
    uint32_t dec_num,int_num;
    int8_t *pcStr, pcBuf[16] ,cFill,numstr[16];
    ASSERT(pcString != 0);
    while(*pcString)
    {
        for(ui32Idx = 0;
            (pcString[ui32Idx] != '%') && (pcString[ui32Idx] != '\0');
            ui32Idx++)
        {
        }
        UARTwrite(mode, pcString, ui32Idx);
        pcString += ui32Idx;
        if(*pcString == '%')
        {
            pcString++;
            ui32Count = 0;
            cFill = ' ';
again:
            switch(*pcString++)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    if((pcString[-1] == '0') && (ui32Count == 0))
                    {
                        cFill = '0';
                    }
                    ui32Count *= 10;
                    ui32Count += pcString[-1] - '0';
                    goto again;
                }
                case 'c':
                {
                    ui32Value = va_arg(vaArgP, uint32_t);
                    UARTwrite(mode, (int8_t *)&ui32Value, 1);
                    break;
                }
                case 'd':
                case 'i':
                {
                    ui32Value = va_arg(vaArgP, uint32_t);
                    ui32Pos = 0;
                    if((int32_t)ui32Value < 0)
                    {
                        ui32Value = -(int32_t)ui32Value;
                        ui32Neg = 1;
                    }
                    else
                    {
                        ui32Neg = 0;
                    }
                    ui32Base = 10;
                    goto convert;
                }
                case 'f':
                {
                    value_f = va_arg(vaArgP,double);
                    ui32Pos=0;
                    ui32Count=0;
                    ui32Idx=0;
                    if((int32_t)value_f<0)
                    {
                        UARTwrite(mode, "-", 1);
                        value_f=-value_f;
                    }
                    int_num = (uint32_t)(value_f);
                    dec_num = (uint32_t)((value_f-int_num)*10000);
                    while(int_num)
                    {
                        pcBuf[ui32Count] = ((uint32_t)int_num%10)+'0';
                        ui32Count++;
                        int_num= int_num/10;
                    }
                    ui32Pos+=ui32Count;
                    while (ui32Count!=0)
                    {
                        ui32Count--;
                        numstr[ui32Idx] = pcBuf[ui32Count];
                        ui32Idx++;
                    }
                    numstr[ui32Idx]='.';
                    ui32Pos++;
                    while(ui32Count!=4)
                    {
                        pcBuf[ui32Count] = ((uint32_t)dec_num%10)+'0';
                        ui32Count++;
                        dec_num= dec_num/10;
                    }
                    ui32Pos+=ui32Count;
                    while (ui32Count)
                    {
                        ui32Count--;
                        ui32Idx++;
                        numstr[ui32Idx] = pcBuf[ui32Count];
                    }
                    UARTwrite(mode, numstr, ui32Pos);
                    ui32Pos=0;
                    ui32Count=0;
                    ui32Idx=0;
                    break;
                }
                case 's':
                {
                    pcStr = va_arg(vaArgP, int8_t *);
                    for(ui32Idx = 0; pcStr[ui32Idx] != '\0'; ui32Idx++)
                    {
                    }
                    UARTwrite(mode, pcStr, ui32Idx);
                    if(ui32Count > ui32Idx)
                    {
                        ui32Count -= ui32Idx;
                        while(ui32Count--)
                        {
                            UARTwrite(mode," ", 1);
                        }
                    }
                    break;
                }
                case 'u':
                {
                    ui32Value = va_arg(vaArgP, uint32_t);
                    ui32Pos = 0;
                    ui32Base = 10;
                    ui32Neg = 0;
                    goto convert;
                }
                case 'x':
                case 'X':
                case 'p':
                {
                    ui32Value = va_arg(vaArgP, uint32_t);
                    ui32Pos = 0;
                    ui32Base = 16;
                    ui32Neg = 0;
convert:
                    for(ui32Idx = 1;
                        (((ui32Idx * ui32Base) <= ui32Value) &&
                         (((ui32Idx * ui32Base) / ui32Base) == ui32Idx));
                        ui32Idx *= ui32Base, ui32Count--)
                    {
                    }
                    if(ui32Neg)
                    {
                        ui32Count--;
                    }
                    if(ui32Neg && (cFill == '0'))
                    {
                        pcBuf[ui32Pos++] = '-';
                        ui32Neg = 0;
                    }
                    if((ui32Count > 1) && (ui32Count < 16))
                    {
                        for(ui32Count--; ui32Count; ui32Count--)
                        {
                            pcBuf[ui32Pos++] = cFill;
                        }
                    }
                    if(ui32Neg)
                    {
                        pcBuf[ui32Pos++] = '-';
                    }
                    for(; ui32Idx; ui32Idx /= ui32Base)
                    {
                        pcBuf[ui32Pos++] =
                            g_pcHex[(ui32Value / ui32Idx) % ui32Base];
                    }
                    UARTwrite(mode, pcBuf, ui32Pos);
                    break;
                }
                case '%':
                {
                    UARTwrite(mode, pcString - 1, 1);
                    break;
                }
                default:
                {
                    UARTwrite(mode,"ERROR", 5);
                    break;
                }
            }
        }
    }
}

void UARTprintf(int style, int8_t *pcString, ...)
{
    va_list vaArgP;
    va_start(vaArgP, pcString);
    UARTvprintf(style, pcString, vaArgP);
    va_end(vaArgP);
}

