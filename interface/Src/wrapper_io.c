#include "interface_io.h"
#include "interface_instances.h"
#include "driver_gpio.h"

/************************************************************
*                     PIN_DEFAULT                           *
*************************************************************/



/************************************************************
*                         IO0                               *
*************************************************************/

static void io0_write(uint8_t value)
{
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_13, value);
}

static uint8_t io0_read(void)
{
    return GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13);
}

static void io0_toggle(void)
{
    GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
}

/************************************************************
*                    INSTANCES
*************************************************************/

const IO_Interface_t io0 = {
    .read = io0_read,
    .write = io0_write,
    .toggle = io0_toggle
};
