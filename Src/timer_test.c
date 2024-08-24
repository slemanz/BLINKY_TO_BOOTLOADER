#include "stm32f401xx.h"
#include "core/system.h"

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
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
}




int main(void)
 {
    gpio_setup();
    tim2_1hz_init();

    while (1)
    {
        // wait for UIF
        while (!(TIM2->SR & SR_UIF));

        // clear UIF
        TIM2->SR &= ~(SR_UIF);
        
        GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
    }
}