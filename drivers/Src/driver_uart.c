#include "driver_uart.h"


static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}



void UART_PeriClockControl(UART_RegDef_t *pUARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pUARTx == UART1)
        {
            UART1_PCLK_EN();
        }else if(pUARTx == UART2)
        {
            UART2_PCLK_EN();
        }else if(pUARTx == UART6)
        {
            UART6_PCLK_EN();
        }
    }else
    {
        if(pUARTx == UART1)
        {
            UART1_PCLK_DI();
        }else if(pUARTx == UART2)
        {
            UART2_PCLK_DI();
        }else if(pUARTx == UART6)
        {
            UART6_PCLK_DI();
        }
    }
}