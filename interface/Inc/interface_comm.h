#ifndef INC_INTERFACE_COMM_H_
#define INC_INTERFACE_COMM_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    PROTOCOL_UART2,
}Comm_ProtocolType_e;

typedef struct
{
    void    (*init)(void);
    void    (*send)(uint8_t *buffer, uint32_t len);
    uint8_t (*receive)(uint8_t *buffer, uint32_t len);
    uint8_t (*data_available)(void);
    void    (*deinit)(void);
}Comm_Interface_t;

Comm_Interface_t *Comm_ProtocolGet(Comm_ProtocolType_e type);

#endif /* INC_INTERFACE_COMM_H_ */