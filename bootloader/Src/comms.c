#include "assert.h"
#include "comms.h"
#include "shared/crc8.h"

#define PACKET_BUFFER_LENGTH (8)

typedef enum comms_state_t
{
    CommsState_Length,
    CommsState_Data,
    CommsState_CRC
} comms_state_t;

static comms_state_t state = CommsState_Length;
static uint8_t data_byte_count = 0;

static comms_packet_t temporary_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t retx_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t ack_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t last_transmitted_packet = {.length = 0, .data = {0}, .crc = 0};

// like the ring buffer structure, but not for only one byte
static comms_packet_t packet_buffer[PACKET_BUFFER_LENGTH];
static uint32_t packet_read_index = 0;
static uint32_t packet_write_index = 0;
static uint32_t packet_buffer_mask = PACKET_BUFFER_LENGTH; 

static bool comms_is_single_byte_packet(const comms_packet_t *packet, uint8_t byte)
{
    if(packet->length != 1)
    {
        return false;
    }

    if(packet->data[0] != byte)
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

static void comms_packet_copy(const comms_packet_t *source, comms_packet_t *dest)
{
    dest->length = source->length;
    for(uint8_t i = 0; i < PACKET_DATA_LENGTH; i++)
    {
        dest->data[i] = source->data[i];
    }
    dest->crc = source->crc;
}

void comms_setup(void)
{
    retx_packet.length = 1;
    retx_packet.data[0] = PACKET_RETX_DATA0;
    for(uint8_t i = 1; i < PACKET_DATA_LENGTH; i++)
    {
        retx_packet.data[i] = 0xff;
    }
    retx_packet.crc = comms_compute_crc(&retx_packet);


    ack_packet.length = 1;
    ack_packet.data[0] = PACKET_ACK_DATA0;
    for(uint8_t i = 1; i < PACKET_DATA_LENGTH; i++)
    {
        ack_packet.data[i] = 0xff;
    }
    ack_packet.crc = comms_compute_crc(&ack_packet);
}

void comms_update(void)
{
    while(uart_data_available())
    {
        switch (state)
        {
            case CommsState_Length:
            {
                temporary_packet.length = uart_read_byte();
                state = CommsState_Data;
            }break;
            case CommsState_Data:
            {
                temporary_packet.data[data_byte_count++] = uart_read_byte();
                if(data_byte_count >= PACKET_DATA_LENGTH)
                {
                    data_byte_count = 0;
                    state = CommsState_CRC;
                }

            }break;
            case CommsState_CRC:
            {
                temporary_packet.crc = uart_read_byte();

                if(temporary_packet.crc != comms_compute_crc(&temporary_packet))
                {
                    comms_write(&retx_packet);
                    state = CommsState_Length;
                    break;
                }

                if(comms_is_single_byte_packet(&temporary_packet, PACKET_ACK_DATA0))
                {
                    comms_write(&last_transmitted_packet);
                    state = CommsState_Length;
                    break;
                }

                uint32_t next_write_index = (packet_write_index + 1) & packet_buffer_mask;
                assert(next_write_index != packet_read_index); // debug


                comms_packet_copy(&temporary_packet, &packet_buffer[packet_write_index]);
                packet_write_index = (packet_write_index + 1) & packet_buffer_mask;
                comms_write(&ack_packet);
                state = CommsState_Length;
            }break;

            default:
            {
                state = CommsState_Length;
            }
        }
    }
}

bool comms_packets_available(void)
{
    return packet_read_index != packet_write_index;
}

void comms_write(comms_packet_t *packet)
{
    uart_write((uint8_t*)packet, PACKET_LENGTH);
}

void comms_read(comms_packet_t *packet)
{
    comms_packet_copy(&packet_buffer[packet_read_index], packet);
}

uint8_t comms_compute_crc(comms_packet_t *packet)
{
    return crc8((uint8_t*)packet, PACKET_LENGTH - PACKET_CRC_BYTES);
}