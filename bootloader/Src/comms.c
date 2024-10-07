#include "comms.h"
#include "uart.h"
#include "core/crc8.h"

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

static bool comms_is_retx_packet(const comms_packet_t *packet)
{
    if(packet->length != 1)
    {
        return false;
    }

    if(packet->data[0] != PACKET_RETX_DATA0)
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
                }

            }break;
        }
    }
}

bool comms_packets_available(void)
{

}

void comms_write(comms_packet_t *packet)
{

}

void comms_read(comms_packet_t *packet)
{

}

uint8_t comms_compute_crc(comms_packet_t *packet)
{
    return crc8((uint8_t*)packet, PACKET_LENGTH - PACKET_CRC_BYTES);
}