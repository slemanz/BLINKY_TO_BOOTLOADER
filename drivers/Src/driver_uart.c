#include "driver_uart.h"
#include "driver_clock.h"


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

void UART_Init(UART_Config_t *pUARTConfig)
{
    // temporary variable
	uint32_t tempreg = 0;

	// *** Configuration of CR1 **************************************
	UART_PeriClockControl(pUARTConfig->pUARTx, ENABLE);

	if(pUARTConfig->UART_Mode == UART_MODE_ONLY_RX)
	{
		tempreg |= (1 << UART_CR1_RE);
	}else if(pUARTConfig->UART_Mode == UART_MODE_ONLY_TX)
	{
		tempreg |= (1 << UART_CR1_TE);
	}else if(pUARTConfig->UART_Mode == UART_MODE_TXRX)
	{
		tempreg |= ((1 << UART_CR1_RE) | (1 << UART_CR1_TE));
	}

	tempreg |= (pUARTConfig->UART_WordLength << UART_CR1_M);

	if(pUARTConfig->UART_ParityControl == UART_PARITY_EN_EVEN)
	{
		tempreg |= (1 << UART_CR1_PCE);
	}else if(pUARTConfig->UART_ParityControl == UART_PARITY_EN_ODD)
	{
		tempreg |= (1 << UART_CR1_PCE);
		tempreg |= (1 << UART_CR1_PS);
	}
	pUARTConfig->pUARTx->CR1 = tempreg;

	// *** Configuration of CR2 **************************************
	tempreg = 0;
	tempreg |= (pUARTConfig->UART_NoOfStopBits << UART_CR2_STOP);
	pUARTConfig->pUARTx->CR2 = tempreg;

	// *** Configuration of CR3 **************************************
	tempreg=0;

    if ( pUARTConfig->UART_HWFlowControl == UART_HW_FLOW_CTRL_CTS)
    {
        tempreg |= ( 1 << UART_CR3_CTSE);
    }else if (pUARTConfig->UART_HWFlowControl == UART_HW_FLOW_CTRL_RTS)
    {
        tempreg |= ( 1 << UART_CR3_RTSE);
    }else if (pUARTConfig->UART_HWFlowControl == UART_HW_FLOW_CTRL_CTS_RTS)
    {
        tempreg |= ((1 << UART_CR3_CTSE) | ( 1 << UART_CR3_RTSE));
    }
    pUARTConfig->pUARTx->CR3 = tempreg;

    // *** Configuration of BRR (Baudrate) ***********************
    pUARTConfig->pUARTx->BRR = compute_uart_div(clock_get(), pUARTConfig->UART_Baud);
}

void UART_Init_table(const UART_Config_t *pUARTConfig, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        UART_Init((UART_Config_t*)&pUARTConfig[i]);
    }
}

void UART_DeInit(UART_RegDef_t *pUARTx)
{
    if      (pUARTx == UART1) UART1_REG_RESET();
    else if	(pUARTx == UART2) UART2_REG_RESET();
    else if	(pUARTx == UART6) UART6_REG_RESET();
}

void UART_write_byte(UART_RegDef_t *pUARTx, uint8_t data)
{
    pUARTx->DR = data;
}

void UART_write(UART_RegDef_t *pUARTx, uint8_t *pTxBuffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        while(!UART_GetFlagStatus(pUARTx, UART_FLAG_TXE));
        UART_write_byte(pUARTx, pTxBuffer[i]);
    }
    while(!UART_GetFlagStatus(pUARTx, UART_FLAG_TC));
}

uint8_t UART_read_byte(UART_RegDef_t *pUARTx)
{
    uint8_t data = pUARTx->DR;
    return data;
}

uint8_t UART_GetFlagStatus(UART_RegDef_t *pUARTx , uint8_t FlagName)
{
	if(pUARTx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}