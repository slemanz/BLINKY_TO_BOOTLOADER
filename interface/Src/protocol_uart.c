#include "interface_comm.h"
#include"interface_instances.h"

#include "shared/ring-buffer.h"

#include "driver_uart.h"
#include "driver_interrupt.h"

// Ring buffer
#define SERIAL_BUFFER_SIZE     128

/************************************************************
*                       UART2                               *
*************************************************************/

static ring_buffer_t rb = {0U};
static uint8_t data_buffer[SERIAL_BUFFER_SIZE] = {0U};

void uart2_protocol_init(void)
{
    ring_buffer_setup(&rb, data_buffer, SERIAL_BUFFER_SIZE);
    
    UART_InterruptConfig(UART2, UART_INTERRUPT_RXNEIE, ENABLE);
    interrupt_Config(IRQ_NO_UART2, ENABLE);

    UART_PeripheralControl(UART2, ENABLE);
}

void uart2_protocol_send(uint8_t *data, uint32_t Len)
{
    UART_write(UART2, data, Len);
}

uint8_t uart2_protocol_receive(uint8_t *buffer, uint32_t Len)
{
    if(Len == 0)
    {
        return 0;
    }

    for(uint8_t bytes_read = 0; bytes_read < Len; bytes_read++)
    {
        if(!ring_buffer_read(&rb, &buffer[bytes_read])) return bytes_read;
    }

    return Len;
}

uint8_t uart2_protocol_data_available(void)
{
    return !ring_buffer_empty(&rb);
}

void USART2_IRQHandler(void)
{
	//const bool overrun_occurred = UART_GetFlagStatus(UART2, UART_FLAG_ORE);
	//const bool received_data = UART_GetFlagStatus(UART2, UART_FLAG_RXNE);

	//if(received_data || overrun_occurred)
    uint8_t data = UART2->DR;
    ring_buffer_write(&rb, data);
}


/************************************************************
*                     WRAPPER                               *
*************************************************************/

const Comm_Interface_t uart2_protocol = {
    .init = uart2_protocol_init,
    .send = uart2_protocol_send,
    .receive = uart2_protocol_receive,
    .data_available = uart2_protocol_data_available,
    .deinit = NULL
};