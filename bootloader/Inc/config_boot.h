#ifndef INC_CONFIG_BOOT_H_
#define INC_CONFIG_BOOT_H_

#include <stdint.h>
#include <stddef.h>

void config_drivers(void);
void config_interface(void);

void deinit_boot(void);

#endif /* INC_CONFIG_BOOT_H_ */