#include <stdio.h>

#include "config_app.h"

// interface
#include "interface_io.h"
#include "interface_comm.h"
#include "interface_timebase.h"

int main(void)
 {
    config_drivers();
    config_interface();

    Timebase_Interface_t *ticks = timebase_get();
    uint64_t start_time = ticks->get();

    printf("\n");
    printf("Init app\n");

    Comm_Interface_t *serial = Comm_ProtocolGet(PROTOCOL_UART2);
    uint8_t data_rcv = 0;

    while (1)
    {
        if((ticks->get() - start_time) >= 1000)
        {
            IO_Interface_get(IO0)->toggle();
            start_time = ticks->get();
        }

        while(serial->data_available())
        {
            serial->receive(&data_rcv, 1);
            serial->send(&data_rcv, 1); // echo
        }
        // Do other stuff
    }
}