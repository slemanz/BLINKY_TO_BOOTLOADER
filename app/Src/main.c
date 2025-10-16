#include <stdio.h>

#include "config_app.h"

// interface
#include "interface_timebase.h"

// core
#include "core/cli.h"

// bsp
#include "bsp/led.h"
#include "bsp/button.h"

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
        if((ticks->get() - start_time) >= 500)
        {
            led_get(LED_NUM_1)->toggle();
            start_time = ticks->get();
        }

        if(button_get(BUTTON_NUM_1)->read() == BUTTON_LOW)
        {
            led_get(LED_NUM_2)->set(LED_ON);
        }else
        {
            led_get(LED_NUM_2)->set(LED_OFF);
        }

        if((ticks->get() - start_time2) >= 100)
        {
            cli_update();
            start_time2 = ticks->get();
        }
        // Do other stuff
    }
}