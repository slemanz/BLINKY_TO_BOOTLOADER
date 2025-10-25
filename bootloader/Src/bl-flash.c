#include "bl-flash.h"
#include "bl-info.h"
#include "driver_flash.h"

#define MAIN_APP_SECTOR_START (2)
#define MAIN_APP_SECTOR_END   (6)

void bl_flash_erase_main_application(void)
{
    bl_info_set_boot_update();

    flash_unlock_cr();
    flash_erase_sectors(MAIN_APP_SECTOR_START, (MAIN_APP_SECTOR_END - MAIN_APP_SECTOR_START));
    flash_lock_cr();
}


void bl_flash_write(const uint32_t address, const uint8_t *data, const uint32_t length)
{
    flash_unlock_cr();
    flash_program(address, data, length);
    flash_lock_cr();
}