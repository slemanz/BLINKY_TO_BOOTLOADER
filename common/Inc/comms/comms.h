#ifndef INC_COMMS_H_
#define INC_COMMS_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "interface_comm.h"

#define PACKET_DATA_BYTES       (16)
#define PACKET_LENGTH_BYTES     (1)
#define PACKET_CRC_BYTES        (1)
#define PACKET_LENGTH           (PACKET_DATA_BYTES + PACKET_LENGTH_BYTES + PACKET_CRC_BYTES)

#define PACKET_RETX_DATA0       (0x19)
#define PACKET_ACK_DATA0        (0x15)

typedef struct
{
    uint8_t length;
    uint8_t data[PACKET_DATA_BYTES];
    uint8_t crc;
}comms_packet_t;

void comms_setup(Comm_Interface_t *comm);
void comms_update(void);

bool comms_packets_available(void);
void comms_write(comms_packet_t *packet);
void comms_read(comms_packet_t *packet);
uint8_t comms_compute_crc(comms_packet_t *packet);
bool comms_is_single_byte_packet(const comms_packet_t *packet, uint8_t byte);
void comms_create_single_byte_packet(comms_packet_t *packet, uint8_t byte);

#endif /* INC_COMMS_H_ */