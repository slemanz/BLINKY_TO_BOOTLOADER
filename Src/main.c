#include "stm32f401xx.h"

#define CPU_FREQ        (16000000)
#define SYSTICK_FREQ    (1000) // a

// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

// Define led
#define LED_PORT        GPIOA
#define LED_PIN         GPIO_PIN_NO_3


void gpio_setup(void)
{
    // Set GPIOA pin 3 as output
    GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = LED_PORT;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = LED_PIN;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}


int main(void)
 {
    gpio_setup();
    systick_1hz_interrupt();

    while (1)
    {

    }
}

static void systick_callback(void)
{
    GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
}


void SysTick_Handler(void)
{
    // do something
    systick_callback();
}