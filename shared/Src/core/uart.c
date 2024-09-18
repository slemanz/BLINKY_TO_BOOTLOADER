#include "stm32f401xx.h"


void uart_setup(void)
{
    UART2_PCLK_EN();
}

void uart_write(uint8_t* data, const uint32_t lenght)
{

}

void uart_write_byte(uint8_t data)
{

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