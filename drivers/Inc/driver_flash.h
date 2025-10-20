#ifndef INC_DRIVER_FLASH_H_
#define INC_DRIVER_FLASH_H_

#include "stm32f411xx.h"

/*******************************Register and Mask Definitions********************************/
#define FLASH_KEY1_CR           0x45670123UL 
#define FLASH_KEY2_CR           0xCDEF89ABUL

#define FLASH_OPTKEY1           0x08192A3BUL
#define FLASH_OPTKEY2           0x4C5D6E7FUL


/********************************************************************************************
 *                              APIs supported by this driver                               *
 *                  for more information check the function definitions                     *
 ********************************************************************************************/

void flash_unlock_cr(void);
void flash_unlock_write(void);
void flash_lock_cr(void);
void flash_lock_write(void);

void flash_wait_busy(void);


void flash_enable_write(void);
void flash_disable_write(void);


void flash_write_double_word(uint32_t address, uint64_t data);
void flash_write(uint32_t address, uint8_t *data, uint32_t Len);


void flash_erase_page(uint32_t page);
void flash_erase_pages(uint32_t page, uint32_t Len);
void flash_erase(uint32_t address);

#endif /* INC_DRIVER_FLASH_H_ */