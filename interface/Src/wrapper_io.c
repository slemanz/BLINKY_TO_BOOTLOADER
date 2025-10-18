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
*                         IO1                               *
*************************************************************/

static void io1_write(uint8_t value)
{
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, value);
}

static uint8_t io1_read(void)
{
    return GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_5);
}

static void io1_toggle(void)
{
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}

/************************************************************
*                         IO2                               *
*************************************************************/

static void io2_write(uint8_t value)
{
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, value);
}

static uint8_t io2_read(void)
{
    return GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6);
}

static void io2_toggle(void)
{
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_6);
}

/************************************************************
*                    INSTANCES
*************************************************************/

const IO_Interface_t io0 = {
    .read = io0_read,
    .write = io0_write,
    .toggle = io0_toggle
};

const IO_Interface_t io1 = {
    .read = io1_read,
    .write = io1_write,
    .toggle = io1_toggle
};

const IO_Interface_t io2 = {
    .read = io2_read,
    .write = io2_write,
    .toggle = io2_toggle
};
