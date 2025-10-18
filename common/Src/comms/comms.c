#include <string.h>
#include "comms/comms.h"
#include "shared/crc8.h"

#define PACKET_BUFFER_LENGTH        (8)

typedef enum {
    CommsState_Length,
    CommsState_Data,
    CommsState_CRC,
}comms_state_e;

static Comm_Interface_t *_comm;
static comms_state_e state = CommsState_Length;
static uint8_t data_byte_count = 0;

static comms_packet_t temporary_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t retx_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t ack_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t last_transmitted_packet = {.length = 0, .data = {0}, .crc = 0};

static comms_packet_t packet_buffer[PACKET_BUFFER_LENGTH];
static uint32_t packet_read_index = 0;
static uint32_t packet_write_index = 0;
static uint32_t packet_buffer_mask = PACKET_BUFFER_LENGTH - 1;


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

    for(uint8_t i = 1; i < PACKET_DATA_BYTES; i++)
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

void comms_setup(Comm_Interface_t *comm)
{
    comms_create_single_byte_packet(&retx_packet, PACKET_RETX_DATA0);
    comms_create_single_byte_packet(&ack_packet, PACKET_ACK_DATA0);
    _comm = comm;
}

void comms_update(void)
{
    while(_comm->data_available())
    {
        switch (state)
        {
            case CommsState_Length:
            
                break;
            
            default:
                state = CommsState_CRC;
                break;
        }
    }
}