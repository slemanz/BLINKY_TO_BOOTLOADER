#include "stm32f401xx.h"
#include "core/system.h"

#include "config_app.h"


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
    uart_setup(); // 9600
    //timer_setup();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();
    uint32_t delayMs = 1000;

    uint8_t string_send[] = "hello world!!!\r\n";

    //float duty_cycle = 0.0f;
    //timer_pwm_set_duty_cycle(&PWM, duty_cycle);

    while (1)
    {
        if((system_get_ticks() - start_time) >= delayMs)
        {
            start_time = system_get_ticks();
        }

        if((system_get_ticks() - start_time2) >= 10000)
        {
            uart_write(string_send, (sizeof(string_send) - 1));
            start_time2 = system_get_ticks();
        }

        while(uart_data_available())
        {
            uint8_t data = uart_read_byte();
            uart_write_byte(data);
        }

        // Do other stuff
    }
}