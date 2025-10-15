#ifndef INC_CONFIG_APP_H_
#define INC_CONFIG_APP_H_

#include <stdint.h>

void config_drivers(void);
void config_interface(void);
void config_core(void);
void config_bsp(void);

void deinit_app(void);

#endif /* INC_CONFIG_APP_H_ */