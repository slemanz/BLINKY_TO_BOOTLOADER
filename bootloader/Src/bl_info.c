#include "bl_info.h"
#include "driver_flash.h"

static void info_set(uint8_t id)
{
    flash_unlock_cr();

    flash_erase_sectors(7, 1);
    flash_program(INFO_ADDRESS, &id, 1);

    flash_lock_cr();
}

uint8_t info_verify_boot(void)
{
    uint32_t *app_address = (uint32_t*)0x08008000UL;

    if(info_get() == INFO_BOOT_OK && *app_address == 0x20020000)
    {
        return INFO_BOOT_OK;
    }

    if(info_get() != INFO_BOOT_UPDATE)
    {
        info_set_boot_update();
    }

    return INFO_BOOT_UPDATE;
}

void info_set_boot_ok(void)
{
    info_set(INFO_BOOT_OK);
}

void info_set_boot_update(void)
{
    info_set(INFO_BOOT_UPDATE);
}

uint8_t info_get(void)
{
    uint8_t *mem_read = (uint8_t*)INFO_ADDRESS;
    return *mem_read;
}