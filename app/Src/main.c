#include <stdio.h>

#include "config_app.h"

// core
#include "core/cli.h"
#include "core/simple-timer.h"

// bsp
#include "bsp/led.h"
#include "bsp/button.h"

int main(void)
 {
    config_drivers();
    config_interface();
    config_core();
    config_bsp();

    simple_timer_t timer_blink;
    simple_timer_setup(&timer_blink, 300, true);

    simple_timer_t timer_cli;
    simple_timer_setup(&timer_cli, 100, true);

    printf("\n");
    printf("Init app\n");

    while (1)
    {
        if(simple_timer_has_elapsed(&timer_blink))
        {
            led_get(LED_NUM_1)->toggle();
        }

        if(button_get(BUTTON_NUM_1)->read() == BUTTON_LOW)
        {
            led_get(LED_NUM_2)->set(LED_ON);
        }else
        {
            led_get(LED_NUM_2)->set(LED_OFF);
        }

        if(simple_timer_has_elapsed(&timer_cli))
        {
            cli_update();
        }

        // Do other stuff
    }
}