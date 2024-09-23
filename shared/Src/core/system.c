#include "core/system.h"

static volatile uint64_t ticks = 0;

void SysTick_Handler(void)
{
    ticks++;
}

uint64_t system_get_ticks(void)
{
    return ticks;
}

static void vector_setup(void)
{
    VTOR_OFFSET = BOOTLOADER_SIZE;
}

void systick_setup(void)
{
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}

void system_setup(void)
{
    vector_setup();
    systick_setup();
}

void gpio_setup(void)
{
    // set pin for pwm
    GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = LED_PORT;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = LED_PIN;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    GpioLed.GPIO_PinConfig.GPIO_PinAltFunMode = PA5_ALTFN_TIM2_CH1;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);
}

void uart_pin_setup(void)
{
    // init tx pin
    GPIO_Handle_t UartTx;
    UartTx.pGPIOx = PORT_UART;
    UartTx.GPIO_PinConfig.GPIO_PinNumber = PIN_TX;
    UartTx.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    UartTx.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartTx.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartTx.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartTx.GPIO_PinConfig.GPIO_PinAltFunMode = PA2_ALTFN_UART2_TX;

    GPIO_Init(&UartTx);


    // init rx pin
    GPIO_Handle_t UartRx;
    UartRx.pGPIOx = PORT_UART;
    UartRx.GPIO_PinConfig.GPIO_PinNumber = PIN_RX;
    UartRx.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    UartRx.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartRx.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartRx.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartRx.GPIO_PinConfig.GPIO_PinAltFunMode = PA3_ALTFN_UART2_RX;

    GPIO_Init(&UartRx);
}