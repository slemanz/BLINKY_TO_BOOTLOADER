#include "driver_flash.h"

void flash_set_program_size(uint32_t psize)
{
    FLASH->CR &= ~(FLASH_CR_PSIZE_MSK);
    FLASH->CR |=  (psize << FLASH_CR_PSIZE_POS);
}

void flash_wait_for_last_operation(void)
{
    while((FLASH->SR & FLASH_SR_BSY_MSK));
}

void flash_unlock_cr(void)
{
    FLASH->KEYR = FLASH_KEY1_CR;
    FLASH->KEYR = FLASH_KEY2_CR;
}

void flash_unlock_write(void)
{
    FLASH->OPTKEYR - FLASH_OPTKEY1;
    FLASH->OPTKEYR - FLASH_OPTKEY2;
}

void flash_lock_cr(void)
{
    FLASH->CR |= (1U << 31U);
}

void flash_lock_write(void)
{
    FLASH->OPTCR |= (1U << 0);
}

void flash_erase_sector(uint8_t sector)
{
    flash_wait_for_last_operation();
    flash_set_program_size(FLASH_PSIZE_X8);

    if(sector > 7)
    {
        return;
    }

    FLASH->CR &= ~(0xF << 3);
    FLASH->CR &= ~(sector << 3);
    FLASH->CR |= (1U << 1);
    FLASH->CR |= (1U << 16);

    flash_wait_for_last_operation();

}

void flash_erase_sectors(uint32_t sector, uint32_t Len)
{
    uint32_t length = Len;
    uint32_t sector_erase = sector;

    do
    {
        length--;
        flash_erase_sector(sector_erase);
        sector_erase++;
    } while(length);
}