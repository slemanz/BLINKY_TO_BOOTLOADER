#ifndef INC_BOOT_INFO_H_
#define INC_BOOT_INFO_H_

#include <stdint.h>

#define INFO_BOOT_OK            0x02
#define INFO_BOOT_UPDATE        0x01

#define INFO_SECTION            0x07
#define INFO_ADDRESS            0x08060000UL


uint8_t info_verify_boot(void);
void info_set_boot_ok(void);
uint8_t info_get(void);


#endif /* INC_BOOT_INFO_H_ */