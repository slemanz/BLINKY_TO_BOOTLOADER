#include "stm32f401xx.h"

#define CPU_FREQ        (16000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

volatile uint64_t ticks = 0;
void SysTick_Handler(void)
{
    ticks++;
}

static uint64_t get_ticks(void)
{
    return ticks;
}

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
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
}

void systick_setup(void)
{
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}


int main(void)
 {
    gpio_setup();
    systick_setup();

    uint64_t start_time = get_ticks();

    while (1)
    {
        if((get_ticks() - start_time) >= 1000)
        {
            GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
            start_time = get_ticks();
        }

        // Do useful work
    }
}