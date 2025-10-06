#include "config_app.h"

// drivers
#include "driver_gpio.h"

// GPIO table - minimal one-liner style
static const GPIO_PinConfig_t GPIO_ConfigTable[] = {

    { GPIOC, GPIO_PIN_NO_13, GPIO_MODE_OUT,   GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  GPIO_PIN_ALTFN_0   },     // LED
    { GPIOA, GPIO_PIN_NO_3,  GPIO_MODE_ALTFN, GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  PA3_ALTFN_UART2_RX },    // UART2 TX
    { GPIOA, GPIO_PIN_NO_2,  GPIO_MODE_ALTFN, GPIO_SPEED_LOW, GPIO_OP_TYPE_PP, GPIO_NO_PUPD,  PA2_ALTFN_UART2_TX },    // UART2 RX
};

void config_drivers(void)
{
    GPIO_Init_table(GPIO_ConfigTable, (sizeof(GPIO_ConfigTable)/sizeof(GPIO_ConfigTable[0])));
}