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