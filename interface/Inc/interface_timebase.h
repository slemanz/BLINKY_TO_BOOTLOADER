#ifndef INC_INTERFACE_TIMEBASE_H_
#define INC_INTERFACE_TIMEBASE_H_

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    uint64_t (*get)(void);
    void     (*delay)(uint64_t ticks);
}Timebase_Interface_t;

Timebase_Interface_t *timebase_get(void);

#endif /* INC_INTERFACE_TIMEBASE_H_ */