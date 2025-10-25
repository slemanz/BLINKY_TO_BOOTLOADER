#ifndef INC_BL_FLASH_H_
#define INC_BL_FLASH_H_

#include <stdint.h>

void bl_flash_erase_main_application(void);
void bl_flash_write(const uint32_t address, const uint8_t *data, const uint32_t length);

#endif /* INC_BL_FLASH_H_ */