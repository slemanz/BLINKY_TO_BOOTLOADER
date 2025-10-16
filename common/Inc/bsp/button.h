#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>
#include "interface_io.h"

typedef enum
{
    BUTTON_NUM_1 = 0,
    BUTTON_NUM_2,
    BUTTON_NUM_3,
    BUTTON_NUM_MAX
}button_num_e;

typedef struct
{
    uint8_t (*read)(void);
}button_t;

#define BUTTON_HIGH         IO_SET
#define BUTTON_LOW          IO_RESET

void button_setup(button_num_e button_num, IO_Interface_t *io);
button_t *button_get(button_num_e button_num);

#endif /* INC_BUTTON_H_ */