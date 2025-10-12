#include "interface_timebase.h"
#include "driver_systick.h"

const Timebase_Interface_t timer = {
    .get = ticks_get,
    .delay = ticks_delay
};

Timebase_Interface_t *timebase_get(void)
{
    return (Timebase_Interface_t*)&timer;
}