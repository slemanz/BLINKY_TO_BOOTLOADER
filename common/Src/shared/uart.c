/**************************************************************************************************
 * @file    uart.c
 * @brief   UART Driver Implementation for STM32F401xx
 * @details This source file contains the implementations for initializing, configuring, and 
 *          handling UART communication in the STM32F401xx microcontroller. It includes:
 * 
 *          - Functions to setup UART peripheral.
 *          - Transmission and reception of UART data.
 *          - Handling UART interrupts.
 *          - Helper functions to check status flags.
 * 
 *          The baud rate is configured to 115200. UART interrupts are enabled for data reception.
 * 
 * Author:  William Sleman (www.slemanz.com)
 **************************************************************************************************/

#include "shared/uart.h"
#include "shared/ring-buffer.h"

#define BAUDRATE			(9600U)
#define RING_BUFFER_SIZE		(128)

static ring_buffer_t rb = {0U};

static uint8_t data_buffer[RING_BUFFER_SIZE] = {0U};


void USART2_IRQHandler(void)
{
	//const bool overrun_occurred = UART_GetFlagStatus(UART2, UART_FLAG_ORE);
	//const bool received_data = UART_GetFlagStatus(UART2, UART_FLAG_RXNE);

	//if(received_data || overrun_occurred)
	//{
		if(ring_buffer_write(&rb, (uint8_t)uart_recv(UART2)))
		{
			// handle some error/failure?
		}
	//}
}



void uart_setup(void)
{
	ring_buffer_setup(&rb, data_buffer, RING_BUFFER_SIZE);

    UART2->CR1 |= UART_CR1_RXNEIE_SHIFT; // enable interrupt to rx
    UART_IRQITConfig(38, ENABLE);

    UART2->CR1 |= UART_CR1_UE_SHIFT;// enable uart periph
}

void uart_write(uint8_t* data, const uint32_t lenght)
{
	for(uint32_t i = 0; i < lenght; i++)
	{
		uart_write_byte(data[i]);
	}

}
uint8_t uart_recv(UART_RegDef_t *pUARTx)
{
	return (uint8_t)(pUARTx->DR);
}

void uart_write_byte(uint8_t data)
{
	while(!(UART2->SR & UART_SR_TXE_SHIFT));
    UART2->DR = data;
}

uint32_t uart_read(uint8_t *data, const uint32_t length)
{
	if(length == 0)
	{
		return 0;
	}
	
	for(uint32_t bytes_read = 0; bytes_read < length; bytes_read++)
	{
		if(!ring_buffer_read(&rb, &data[bytes_read]))
		{
			return bytes_read;
		}
	}

	return length;
}

uint8_t uart_read_byte(void)
{
	uint8_t byte = 'z';
	
	(void)uart_read(&byte, 1);

	return byte;
}

bool uart_data_available(void)
{
	return !ring_buffer_empty(&rb);
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
