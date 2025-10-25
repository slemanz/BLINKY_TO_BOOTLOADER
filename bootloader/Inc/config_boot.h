#ifndef INC_CONFIG_BOOT_H_
#define INC_CONFIG_BOOT_H_

#include <stdint.h>
#include <stddef.h>

// bootloader size -> 32kB
#define BOOTLOADER_SIZE             (0x8000UL)
#define FLASH_BASE                  (0x08000000UL)
#define MAIN_APP_START_ADDRESS      (FLASH_BASE + BOOTLOADER_SIZE)

void config_drivers(void);
void config_interface(void);

void deinit_boot(void);
void jump_to_main(void);


#endif /* INC_CONFIG_BOOT_H_ */