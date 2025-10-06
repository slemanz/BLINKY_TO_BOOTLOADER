#include "stm32f401xx.h"
#include "core/system.h"

#include "config_app.h"

#include "driver_gpio.h"


// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

int main(void)
 {
    system_setup();
    config_drivers();
    uart_setup(); // 9600
    //timer_setup();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();

    uint8_t string_send[] = "hello world!!!\r\n";

    while (1)
    {
        if((system_get_ticks() - start_time) >= 1000)
        {
            GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
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