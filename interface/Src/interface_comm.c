#include "interface_comm.h"
#include "interface_instances.h"

Comm_Interface_t *Comm_ProtocolGet(Comm_ProtocolType_e type)
{
    switch (type)
    {
        case PROTOCOL_UART2: return (Comm_Interface_t*)&uart2_protocol;
        default: return NULL;
    }
}
