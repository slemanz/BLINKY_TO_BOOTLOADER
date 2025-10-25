#include "config_boot.h"
#include "bl_info.h"
#include <stdio.h>

// interface
#include "interface_timebase.h"
#include "interface_comm.h"
#include "interface_io.h"

// comms
#include "comms/comms.h"

// core
#include "core/simple-timer.h"

// drivers
#include "driver_flash.h"

int main(void)
 {
    config_drivers();
    config_interface();

    Timebase_Interface_t *ticks = timebase_get();
    IO_Interface_t *led = IO_Interface_get(IO0);
    ticks->delay(100);

    simple_timer_t timer;
    simple_timer_setup(&timer, 5000, false);

    //Comm_Interface_t *serial = Comm_ProtocolGet(PROTOCOL_UART2);

    comms_setup(Comm_ProtocolGet(PROTOCOL_UART2));

    while(1)
    {
        if(simple_timer_has_elapsed(&timer))
        {
            if(info_verify_boot() == INFO_BOOT_OK)
            {
                deinit_boot();
                jump_to_main();
            }

            simple_timer_setup(&timer, 1000, true);

            while(1)
            {
                if(simple_timer_has_elapsed(&timer))
                {
                    led->toggle();
                }
            }
        }

        comms_update();

    }
}