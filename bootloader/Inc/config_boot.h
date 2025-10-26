#ifndef INC_CONFIG_BOOT_H_
#define INC_CONFIG_BOOT_H_

#include <stdint.h>
#include <stddef.h>
#include "core/firmware-info.h"


void config_drivers(void);
void config_interface(void);

void deinit_boot(void);
void jump_to_main(void);


#endif /* INC_CONFIG_BOOT_H_ */