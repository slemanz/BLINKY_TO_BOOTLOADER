#include "config_app.h"

// drivers
#include "driver_gpio.h"

static void config_gpio(void)
{
    // set pin for led
    GPIO_PinConfig_t GpioLed;
	GpioLed.pGPIOx = GPIOC;
	GpioLed.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinAltFunMode = GPIO_PIN_ALTFN_0;
	GpioLed.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GpioLed);

    // init tx pin
    GPIO_PinConfig_t UartTx;
    UartTx.pGPIOx = GPIOA;
    UartTx.GPIO_PinNumber = GPIO_PIN_NO_3;
    UartTx.GPIO_PinSpeed = GPIO_SPEED_LOW;
    UartTx.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartTx.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartTx.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartTx.GPIO_PinAltFunMode = PA2_ALTFN_UART2_TX;
    GPIO_Init(&UartTx);

    // init rx pin
    GPIO_PinConfig_t UartRx;
    UartRx.pGPIOx = GPIOA;
    UartRx.GPIO_PinNumber = GPIO_PIN_NO_2;
    UartRx.GPIO_PinSpeed = GPIO_SPEED_LOW;
    UartRx.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartRx.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartRx.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartRx.GPIO_PinAltFunMode = PA3_ALTFN_UART2_RX;

    GPIO_Init(&UartRx);

}

void config_drivers(void)
{
    config_gpio();
}