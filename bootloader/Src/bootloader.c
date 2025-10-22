#include "config_boot.h"
#include <stdio.h>

// interface
#include "interface_timebase.h"
#include "interface_comm.h"

// comms
#include "comms/comms.h"

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
    ticks->delay(100);
    uint64_t start_time = ticks->get();
    uint64_t start_time2 = ticks->get();

    //printf("\nBootloader Init\n");
    const char *string_send = {"BOOT\n"};
    Comm_Interface_t *serial = Comm_ProtocolGet(PROTOCOL_UART2);
    serial->send((uint8_t*)string_send, 5);

    comms_setup(Comm_ProtocolGet(PROTOCOL_UART2));


    // unlock
    flash_unlock_cr();
    flash_unlock_write();

    uint8_t *mem = (uint8_t*)(0x08060000UL);
    printf("Teste Flash\n");
    flash_erase_sectors(7, 1);
    printf("ERASE: 0x%X\n", *mem);

    uint8_t mem_write[1] = {0x02};
    flash_program(0x08060000, mem_write, 1);
    printf("PROGRAM: 0x%X\n", *mem);



    while(1)
    {
        if((ticks->get() - start_time) >= 3000)
        {
            deinit_boot();
            //jump_to_main();
            while(1);
        }

        if((ticks->get() - start_time2) >= 100)
        {
            comms_update();


            start_time2 = ticks->get();
        }
    }
}