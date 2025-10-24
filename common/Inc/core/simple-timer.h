#ifndef INC_SIMPLE_TIMER_H_
#define INC_SIMPLE_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
#include "interface_timebase.h"

typedef struct
{
    uint64_t wait_time;
    uint64_t target_time;
    bool auto_reset;
    bool has_elapsed;
}simple_timer_t;

void simple_timer_init(Timebase_Interface_t *interface_timer);
void simple_timer_setup(simple_timer_t *timer, uint64_t wait_time, bool auto_reset);
bool simple_timer_has_elapsed(simple_timer_t *timer);
bool simple_timer_reset(simple_timer_t *timer);

#endif /* INC_SIMPLE_TIMER_H_ */