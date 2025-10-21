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