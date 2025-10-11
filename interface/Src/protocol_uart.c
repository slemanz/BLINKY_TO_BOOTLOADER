#include "interface_comm.h"
#include"interface_instances.h"

#include "shared/ring-buffer.h"

#include "driver_uart.h"

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
    UART_PeripheralControl(UART2, ENABLE);
}

void uart2_protocol_send(uint8_t *data, uint32_t Len)
{
    UART_write(UART2, data, Len);
}


/************************************************************
*                     WRAPPER                               *
*************************************************************/

const Comm_Interface_t uart2_protocol = {
    .init = uart2_protocol_init,
    .send = uart2_protocol_send,
    .receive = NULL,
    .data_available = NULL,
    .deinit = NULL
};