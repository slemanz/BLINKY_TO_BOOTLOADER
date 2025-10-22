#ifndef INC_DRIVER_FLASH_H_
#define INC_DRIVER_FLASH_H_

#include "stm32f411xx.h"

/*******************************Register and Mask Definitions********************************/
#define FLASH_KEY1_CR           0x45670123UL 
#define FLASH_KEY2_CR           0xCDEF89ABUL

#define FLASH_OPTKEY1           0x08192A3BUL
#define FLASH_OPTKEY2           0x4C5D6E7FUL


#define FLASH_PSIZE_X8                 (0U)                                    
#define FLASH_PSIZE_X16                (1U)                                    
#define FLASH_PSIZE_X32                (2U)                                    
#define FLASH_PSIZE_X64                (3U)                                    



#define FLASH_CR_PSIZE_POS             (8U)                                    
#define FLASH_SR_BSY_POS               (16U)                                   

#define FLASH_CR_PSIZE_MSK             (0x3UL << FLASH_CR_PSIZE_POS)
#define FLASH_SR_BSY_MSK               (0x1UL << FLASH_SR_BSY_POS)


/********************************************************************************************
 *                              APIs supported by this driver                               *
 *                  for more information check the function definitions                     *
 ********************************************************************************************/

void flash_set_program_size(uint32_t psize);
void flash_wait_for_last_operation(void);

void flash_unlock_cr(void);
void flash_unlock_write(void);
void flash_lock_cr(void);
void flash_lock_write(void);

void flash_enable_write(void);
void flash_disable_write(void);


void flash_program_double_word(uint32_t address, uint64_t data);
void flash_program_word(uint32_t address, uint32_t data);
void flash_program_half_word(uint32_t address, uint16_t data);
void flash_program_byte(uint32_t address, uint8_t data);
void flash_program(uint32_t address, const uint8_t *data, uint32_t len);


void flash_erase_sector(uint8_t sector);
void flash_erase_sectors(uint32_t sector, uint32_t Len);

#endif /* INC_DRIVER_FLASH_H_ */