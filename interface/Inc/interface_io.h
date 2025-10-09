#ifndef INC_INTERFACE_IO_H_
#define INC_INTERFACE_IO_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    IO0,
    // ...
}IO_Pin_e;

typedef struct
{
    void    (*write)(uint8_t value);
    uint8_t (*read)(void);
    void    (*toggle)(void);
}IO_Interface_t;  

#define IO_SET              1
#define IO_RESET            0

IO_Interface_t *IO_Interface_get(IO_Pin_e pin);

#endif /* INC_INTERFACE_IO_H_ */