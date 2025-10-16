#include "config_app.h"

#define BOOTLOADER_SIZE (0x8000U)

/************************************************************
*                       DRIVERS                             *
*************************************************************/
#include "driver_systick.h"
#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_systick.h"

static const GPIO_PinConfig_t GPIO_ConfigTable[] = {

    { GPIOC, GPIO_PIN_NO_13, GPIO_MODE_OUT,   GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  GPIO_PIN_ALTFN_0   },    // IO0 - (LED)
    { GPIOA, GPIO_PIN_NO_3,  GPIO_MODE_ALTFN, GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  PA3_ALTFN_UART2_RX },    // UART2 TX
    { GPIOA, GPIO_PIN_NO_2,  GPIO_MODE_ALTFN, GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  PA2_ALTFN_UART2_TX },    // UART2 RX
    { GPIOA, GPIO_PIN_NO_5,  GPIO_MODE_OUT,   GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  GPIO_PIN_ALTFN_0   },    // IO1 - (LED)
    { GPIOA, GPIO_PIN_NO_0,  GPIO_MODE_IN,    GPIO_SPEED_FAST, GPIO_OP_TYPE_PP, GPIO_PIN_PU,   GPIO_PIN_ALTFN_0   },   // IO2 - (BUTTON)
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


/************************************************************
*                      INTERFACE                            *
*************************************************************/

#include "interface_comm.h"

void config_interface(void)
{
    Comm_ProtocolGet(PROTOCOL_UART2)->init();
}

/************************************************************
*                         CORE                              *
*************************************************************/
#include "core/cli.h"

const command_t commands_table[] = {
    {"boot", jump_bootloader, "Jump to bootloader"},
    {"help", cli_help, "List all commands."},
};

void config_core(void)
{
    cli_setup(Comm_ProtocolGet(PROTOCOL_UART2), (command_t*)commands_table, 2);

}

/************************************************************
*                         BSP                               *
*************************************************************/
#include "bsp/led.h"
#include "bsp/button.h"

void config_bsp(void)
{
    led_setup(LED_NUM_1, IO_Interface_get(IO0));
    led_setup(LED_NUM_2, IO_Interface_get(IO1));

    button_setup(BUTTON_NUM_1, IO_Interface_get(IO2));
}


/************************************************************
*                       DEINIT APP                          *
*************************************************************/

void deinit_app(void)
{
    // interface 
    Comm_ProtocolGet(PROTOCOL_UART2)->deinit();

    // drivers
    systick_deinit();
    UART_DeInit(UART2);
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOC);
}

void jump_bootloader(void)
{
    deinit_app();
    
    VTOR_OFFSET = 0x08000000;
    
    void (*sys_mem_bootloader)(void);
    uint32_t reset_handler_address = *(volatile uint32_t *)0x08000004U; // read the reset handler address (inside this)
    sys_mem_bootloader = (void (*)(void))reset_handler_address;
    sys_mem_bootloader();

    //typedef void (*void_fn)(void);
    //uint32_t* reset_vector_entry = (uint32_t*)(0x08000000 + 4U);
    //uint32_t* reset_vector = (uint32_t*)(*reset_vector_entry);
    //void_fn jump_fn = (void_fn)reset_vector;
    //jump_fn();
}

// printf retarget
extern int __io_putchar(int ch)
{
    Comm_ProtocolGet(PROTOCOL_UART2)->send((uint8_t*)&ch, 1);
    return ch;
}
