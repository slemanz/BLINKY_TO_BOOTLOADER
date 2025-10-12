#include "config_app.h"

// drivers
#include "driver_systick.h"
#include "driver_gpio.h"
#include "driver_uart.h"

// interface
#include "interface_comm.h"

#define BOOTLOADER_SIZE (0x8000U)

// GPIO table - minimal one-liner style
static const GPIO_PinConfig_t GPIO_ConfigTable[] = {

    { GPIOC, GPIO_PIN_NO_13, GPIO_MODE_OUT,   GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  GPIO_PIN_ALTFN_0   },    // PIN0 - (LED)
    { GPIOA, GPIO_PIN_NO_3,  GPIO_MODE_ALTFN, GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  PA3_ALTFN_UART2_RX },    // UART2 TX
    { GPIOA, GPIO_PIN_NO_2,  GPIO_MODE_ALTFN, GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  PA2_ALTFN_UART2_TX },    // UART2 RX
};

static const UART_Config_t UART_ConfigTable[ ]= {

    {UART2, UART_MODE_TXRX, UART_STD_BAUD_115200, UART_STOPBITS_1, UART_WORDLEN_8BITS, UART_PARITY_DISABLE, UART_HW_FLOW_CTRL_NONE}
};

static void vector_setup(void)
{
    VTOR_OFFSET = BOOTLOADER_SIZE;
}

void config_drivers(void)
{
    vector_setup();
    GPIO_Init_table(GPIO_ConfigTable, (sizeof(GPIO_ConfigTable)/sizeof(GPIO_ConfigTable[0])));
    UART_Init_table(UART_ConfigTable, (sizeof(UART_ConfigTable)/sizeof(UART_ConfigTable[0])));
    systick_init(1000);
}

void config_interface(void)
{
    Comm_ProtocolGet(PROTOCOL_UART2)->init();
}


/************************************************************
*                       DEINIT APP                          *
*************************************************************/

void deinit_app(void)
{
    // interface 
    Comm_ProtocolGet(PROTOCOL_UART2)->deinit();

    // drivers
    UART_DeInit(UART2);
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOC);
}

// printf retarget
extern int __io_putchar(int ch)
{
    Comm_ProtocolGet(PROTOCOL_UART2)->send((uint8_t*)&ch, 1);
    return ch;
}
