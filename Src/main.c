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
    uint8_t flag_up = 1;
    float duty_step = 1.0f;
    uint32_t delayMs = 15;

    while (1)
    {
        if((system_get_ticks() - start_time) >= delayMs)
        {

            duty_cycle = (flag_up) ? duty_cycle + duty_step : duty_cycle - duty_step;

            if(duty_cycle >= 100.0f)
            {
                flag_up = 0;
                duty_cycle = 100.0f;
            }
            else if(duty_cycle <= 0)
            {
                flag_up = 1;
                duty_step = 1.0f;
                duty_cycle = 0.0f;
            }
            
            timer_pwm_set_duty_cycle(&PWM, duty_cycle);
            start_time = system_get_ticks();
        }

        // Do other stuff
    }
}