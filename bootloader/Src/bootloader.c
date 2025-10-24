#include "config_boot.h"
#include "boot_info.h"
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

// bootloader size -> 32kB
#define BOOTLOADER_SIZE             (0x8000UL)
#define FLASH_BASE                  (0x08000000UL)
#define MAIN_APP_START_ADDRESS      (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void)
{
    typedef void (*void_fn)(void);
    uint32_t* reset_vector_entry = (uint32_t*)(MAIN_APP_START_ADDRESS + 4U);
    uint32_t* reset_vector = (uint32_t*)(*reset_vector_entry);

    void_fn jump_fn = (void_fn)reset_vector;
    jump_fn();
}


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