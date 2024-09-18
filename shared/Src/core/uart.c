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
    UART2->CR1 &= ~(1 << 12); // 8 databits
    UART2->BRR = compute_uart_div(16000000, 115200); // baurate
    UART2->CR1 &= ~(1 << 10); // parity disable
    UART2->CR2 &= ~(0x3 << 12); // 1 stop bits

    // tx en
    // rx en


    // do macros to bit shifts
    // enable interrupt to rx
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