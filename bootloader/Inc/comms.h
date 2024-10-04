#ifndef INC_COMMS_H_
#define INC_COMMS_H_

#include "common-defines.h"

#define PACKET_DATA_LENGTH  (16)

typedef struct comms_packet_t{
    uint8_t length;
    uint8_t data[PACKET_DATA_LENGTH];
    uint8_t crc;
}comms_packet_t;

void comms_setup(void);
void comms_update(void);

bool comms_packets_available(void);
void comms_write(comms_packet_t *packet);
void comms_read(comms_packet_t *packet);


#endif /* INC_COMMS_H_*/