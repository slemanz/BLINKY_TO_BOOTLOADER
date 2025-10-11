#include "stm32f411xx.h"
#include <stdio.h>

#include "config_app.h"

// interface
#include "interface_io.h"

#include "driver_systick.h"
#include "interface_comm.h"

// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

int main(void)
 {
    config_drivers();
    config_interface();

    uint64_t start_time = ticks_get();
    uint64_t start_time2 = ticks_get();

    printf("\n");
    printf("Init board\n");

    Comm_Interface_t *serial = Comm_ProtocolGet(PROTOCOL_UART2);
    uint8_t data_rcv = 0;

    while (1)
    {
        if((ticks_get() - start_time) >= 1000)
        {
            IO_Interface_get(IO0)->toggle();
            start_time = ticks_get();
        }

        if((ticks_get() - start_time2) >= 10000)
        {
            printf("Hello\n");
            start_time2 = ticks_get();
        }

        while(serial->data_available())
        {
            serial->receive(&data_rcv, 1);
            serial->send(&data_rcv, 1); // echo
        }
        // Do other stuff
    }
}