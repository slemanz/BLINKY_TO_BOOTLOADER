#include "interface_io.h"
#include "interface_instances.h"

IO_Interface_t *IO_Interface_get(IO_Pin_e pin)
{
    switch(pin)
    {
        case IO0: return (IO_Interface_t*)&io0;
        case IO1: return (IO_Interface_t*)&io1;
        case IO2: return (IO_Interface_t*)&io2;

        default: return NULL;
    }
}
