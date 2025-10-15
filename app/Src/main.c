#include <stdio.h>

#include "config_app.h"

// interface
#include "interface_io.h"
#include "interface_comm.h"
#include "interface_timebase.h"

// core
#include "core/cli.h"

// bsp
#include "bsp/led.h"

int main(void)
 {
    config_drivers();
    config_interface();
    config_core();
    config_bsp();

    Timebase_Interface_t *ticks = timebase_get();
    uint64_t start_time = ticks->get();
    uint64_t start_time2 = ticks->get();

    printf("\n");
    printf("Init app\n");

    while (1)
    {
        if((ticks->get() - start_time) >= 200)
        {
            //IO_Interface_get(IO0)->toggle();
            led_get(LED_NUM_1)->toggle();
            start_time = ticks->get();
        }

        if((ticks->get() - start_time2) >= 100)
        {
            cli_update();
            start_time2 = ticks->get();
        }
        // Do other stuff
    }
}