#ifndef INC_FIRMWARE_INFO_H_
#define INC_FIRMWARE_INFO_H_

#include <stdint.h>

// bootloader size -> 32kB
#define BOOTLOADER_SIZE             (0x8000UL)
#define FLASH_BASE                  (0x08000000UL)
#define MAIN_APP_START_ADDRESS      (FLASH_BASE + BOOTLOADER_SIZE)
#define MAX_FW_LENGTH               ((1024U * 256U) - BOOTLOADER_SIZE)

#define DEVICE_ID                   (0x42)

#endif /* INC_FIRMWARE_INFO_H_ */