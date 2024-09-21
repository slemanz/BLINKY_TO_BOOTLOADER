#include "stm32f401xx.h"
#include "core/system.h"


// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}


TIM_Handle_t PWM;

void timer_setup(void)
{
    PWM.pTIMx = TIM2;
    PWM.TIM_Config.channel = TIM_CHANNEL1;
    PWM.TIM_Config.initialDuty = 100.0f;

    // setup frequency and resolution
    PWM.TIM_Config.prescaler = PRESCALER; // divided by 10
    PWM.TIM_Config.auto_reload = ARR_VALUE; // divided by 26667 -> close to 60Hz

    timer_pwm_init(&PWM);
}

int main(void)
 {
    system_setup();
    gpio_setup();
    uart_pin_setup();
    uart_setup();
    timer_setup();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();
    float duty_cycle = 0.0f;
    uint32_t delayMs = 1000;

    uint8_t string_send[] = "Hello world SLEMAN!!!\n";

    while (1)
    {
        if((system_get_ticks() - start_time) >= delayMs)
        {
            timer_pwm_set_duty_cycle(&PWM, duty_cycle);
            duty_cycle += 10.0f;
            if(duty_cycle >= 100.0f)
            {
                duty_cycle = 0.0f;
            }
            
            start_time = system_get_ticks();
        }

        if((system_get_ticks() - start_time2) >= 10000)
        {
            uart_write(string_send, (sizeof(string_send) - 1));
            start_time2 = system_get_ticks();
        }

        // Do other stuff
    }
}