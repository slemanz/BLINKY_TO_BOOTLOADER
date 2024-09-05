#include "stm32f401xx.h"
#include "core/system.h"

// Define led
#define LED_PORT        GPIOA
#define LED_PIN         GPIO_PIN_NO_5

// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

void gpio_setup(void)
{
    // Set GPIOA pin 3 as output
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

TIM_Handle_t PWM;

void timer_setup(void)
{
    PWM.pTIMx = TIM2;
    PWM.TIM_Config.channel = TIM_CHANNEL1;
    PWM.TIM_Config.initialDuty = 10.0f;

    // setup frequency and resolution
    PWM.TIM_Config.prescaler = PRESCALER; // divided by 10
    PWM.TIM_Config.auto_reload = ARR_VALUE; // divided by 26667 -> close to 60Hz

    timer_pwm_init(&PWM);
}



int main(void)
 {
    gpio_setup();
    system_setup();
    timer_setup();


    uint64_t start_time = system_get_ticks();
    float duty_cycle = 0.0f;

    while (1)
    {
        if((system_get_ticks() - start_time) >= 50)
        {
            duty_cycle += 0.5f;            


            timer_pwm_set_duty_cycle(&PWM, duty_cycle);
            start_time = system_get_ticks();
            if(duty_cycle >= 50.0f)
            {
                duty_cycle = 0.0f;
            }
        }

        // Do useful work
    }
}