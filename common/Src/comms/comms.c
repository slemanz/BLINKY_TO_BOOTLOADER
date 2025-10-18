#include <string.h>
#include "comms.h"
#include "shared/crc8.h"

#define PACKET_BUFFER_LENGTH        (8)

typedef enum {
    CommsState_Length,
    CommsState_Data,
    CommsState_CRC,
}comms_state_e;

bool comms_is_single_byte_packet(const comms_packet_t *packet, uint8_t byte)
{
    if(packet->length != 1)
    {
        return false;
    }

    if(packet->data != byte)
    {
        return false;
    }

    for(uint8_t i = 1; i < PACKET_DATA_LENGTH; i++)
    {
        if(packet->data[i] != 0xff)
        {
            return false;
        }
    }

    return true;
}

void comms_create_single_byte_packet(comms_packet_t *packet, uint8_t byte)
{
    memset(packet, 0xff, sizeof(comms_packet_t));
    packet->length = 1;
    packet->data[0] = byte;
    packet->crc = comms_compute_crc(packet);
}