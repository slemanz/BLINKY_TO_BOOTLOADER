#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>
#include "interface_io.h"

typedef enum
{
    LED_NUM_1 = 0,
    LED_NUM_2,
    LED_NUM_3,
    LED_MAX
}led_num_e;

typedef struct
{
    void (*set)(uint8_t value);
    void (*toggle)(void);
}led_t;

#define LED_ON          IO_SET
#define LED_OFF         IO_RESET

void led_setup(led_num_e led_num, IO_Interface_t *io);
led_t *led_get(led_num_e led_num);

#endif /* INC_LED_H_ */