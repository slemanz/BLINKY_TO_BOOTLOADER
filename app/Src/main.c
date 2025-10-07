#include "stm32f411xx.h"
#include "core/system.h"

#include "config_app.h"

#include "driver_gpio.h"
#include "driver_systick.h"
#include "core/uart.h"


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

    uint64_t start_time = ticks_get();
    uint64_t start_time2 = ticks_get();

    uint8_t string_send[] = "hello world!!!\r\n";

    while (1)
    {
        if((ticks_get() - start_time) >= 1000)
        {
            GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
            start_time = ticks_get();
        }

        if((ticks_get() - start_time2) >= 10000)
        {
            uart_write(string_send, (sizeof(string_send) - 1));
            start_time2 = ticks_get();
        }

        while(uart_data_available())
        {
            uint8_t data = uart_read_byte();
            uart_write_byte(data);
        }

        // Do other stuff
    }
}