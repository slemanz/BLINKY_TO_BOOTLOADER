#include "stm32f401xx.h"

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

void uart_setup(void)
{
    UART2_PCLK_EN();

    // no flow control (default reset)
    UART2->CR1 &= ~(1 << UART_CR1_M); // 8 databits
    UART2->BRR = compute_uart_div(16000000, 115200); // baurate
    UART2->CR1 &= ~(1 << UART_CR1_PCE); // parity disable
    UART2->CR2 &= ~(0x3 << UART_CR2_STOP); // 1 stop bits

    UART2->CR1 |= (1 << UART_CR1_TE); // tx en
    UART2->CR1 |= (1 << UART_CR1_RE); // rx en


    UART2->CR1 |= (1 << UART_CR1_RXNEIE); // enable interrupt to rx
    UART_IRQITConfig(38, ENABLE);

    UART2->CR1 |= (1 << UART_CR1_UE);// enable uart periph
}

void uart_write(uint8_t* data, const uint32_t lenght)
{

}

void uart_write_byte(uint8_t data)
{
	while(!(UART2->SR & (1 << UART_SR_TXE)));
    UART2->DR = data;
}

uint32_t uart_read(uint8_t *data, const uint32_t length)
{

}

uint8_t uart_read_byte(void)
{

}

bool uart_data_available(void)
{

}


void UART_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    // reference: CORTEX M4 user guide
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		}else if(IRQNumber > 31 && IRQNumber < 64) // 32 to 63
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));

		}else if(IRQNumber >= 64 && IRQNumber < 96) // 64 to 95
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));

		}
	}else
	{
		if(IRQNumber <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// program ICER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}