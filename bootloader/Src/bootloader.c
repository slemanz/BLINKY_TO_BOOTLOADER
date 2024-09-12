#include "common-defines.h"

// bootloader size -> 32kB
#define BOOTLOADER_SIZE             (0x8000UL)
#define FLASH_BASE                  (0x08000000UL)
#define MAIN_APP_START_ADDRESS      (FLASH_BASE + BOOTLOADER_SIZE)

void jump_to_main(void)
{
    uint32_t* reset_vector = (uint32_t*)MAIN_APP_START_ADDRESS;
}


int main(void)
 {
    jump_to_main();

    // never return
    return 0;
}