#include "config_boot.h"
#include "bl-info.h"
#include "bl-flash.h"

// interface
#include "interface_timebase.h"
#include "interface_comm.h"
#include "interface_io.h"

// comms
#include "comms/comms.h"

// core
#include "core/simple-timer.h"

#define SYNC_SEQ_0          (0xC4)
#define SYNC_SEQ_1          (0x55)
#define SYNC_SEQ_2          (0x7E)
#define SYNC_SEQ_3          (0x10)

#define DEFAULT_TIMEOUT     (5000)

typedef enum{
    BL_State_Sync,
    BL_State_WaitForUpdateReq,
    BL_State_DeviceIDReq,
    BL_State_DeviceIDRes,
    BL_State_FWLengthReq,
    BL_State_FWLengthRes,
    BL_State_EraseApplication,
    BL_State_ReceiveFirmware,
    BL_State_Done
}bl_state_t;

static bl_state_t state = BL_State_Sync;
static uint32_t fw_length = 0;
static uint32_t bytes_written = 0;
static uint8_t sync_seq[4] = {0};
static comms_packet_t temp_packet;
simple_timer_t timer;

static void bootloading_fail(void)
{
    comms_create_single_byte_packet(&temp_packet, BL_PACKET_NACK_DATA0);
    comms_write(&temp_packet);
    state = BL_State_Done;
}

static void check_for_timeout(void)
{
    if(simple_timer_has_elapsed(&timer))
    {
        bootloading_fail();
    }
}

static bool is_device_id_packet(const comms_packet_t *packet)
{
    if(packet->length != 2)
    {
        return false;
    }

    if(packet->data[0] != BL_PACKET_DEVICE_ID_RES_DATA0)
    {
        return false;
    }

    for(uint8_t i = 2; i < PACKET_DATA_BYTES; i++)
    {
        if(packet->data[i] != 0xff)
        {
            return false;
        }
    }

    return true;
}

static bool is_fw_length_packet(const comms_packet_t *packet)
{
    if(packet->length != 5)
    {
        return false;
    }

    if(packet->data[0] != BL_PACKET_FW_LENGTH_RES_DATA0)
    {
        return false;
    }

    for(uint8_t i = 5; i < PACKET_DATA_BYTES; i++)
    {
        if(packet->data[i] != 0xFF) return false;
    }

    return true;
}

int main(void)
 {
    config_drivers();
    config_interface();

    Timebase_Interface_t *ticks = timebase_get();
    IO_Interface_t *led = IO_Interface_get(IO0);
    ticks->delay(100);

    simple_timer_setup(&timer, DEFAULT_TIMEOUT, false);


    Comm_Interface_t *serial = Comm_ProtocolGet(PROTOCOL_UART2);
    comms_setup(Comm_ProtocolGet(PROTOCOL_UART2));

    //const char *test = "test\n";
    //serial->send((uint8_t*)test, 5);

    while(state != BL_State_Done)
    {
        if(state == BL_State_Sync)
        {
            if(serial->data_available())
            {
                uint8_t temp_byte;
                serial->receive(&temp_byte, 1);

                sync_seq[0] = sync_seq[1];
                sync_seq[1] = sync_seq[2];
                sync_seq[2] = sync_seq[3];
                sync_seq[3] = temp_byte;

                bool is_match = sync_seq[0] == SYNC_SEQ_0;
                is_match = is_match && (sync_seq[1] == SYNC_SEQ_1);
                is_match = is_match && (sync_seq[2] == SYNC_SEQ_2);
                is_match = is_match && (sync_seq[3] == SYNC_SEQ_3);

                if(is_match)
                {
                    comms_create_single_byte_packet(&temp_packet, BL_PACKET_SYNC_OBSERVED_DATA0);
                    comms_write(&temp_packet);
                    simple_timer_reset(&timer);
                    state = BL_State_WaitForUpdateReq;
                }else
                {
                    check_for_timeout();
                }
            }else
            {
                check_for_timeout();
            }

            continue;
        }

        comms_update();

        switch (state)
        {
            case BL_State_WaitForUpdateReq:
                if(comms_packets_available())
                {
                    comms_read(&temp_packet);
                    
                    if(comms_is_single_byte_packet(&temp_packet, BL_PACKET_FW_UPDATE_REQ_DATA0))
                    {
                        simple_timer_reset(&timer);
                        comms_create_single_byte_packet(&temp_packet, BL_PACKET_FW_UPDATE_RES_DATA0);
                        comms_write(&temp_packet);
                        state = BL_State_DeviceIDReq;
                    }else
                    {
                        bootloading_fail();
                    }
                }else
                {
                    check_for_timeout();
                }
                break;

            case BL_State_DeviceIDReq:
            {
                simple_timer_reset(&timer);
                comms_create_single_byte_packet(&temp_packet, BL_PACKET_DEVICE_ID_REQ_DATA0);
                comms_write(&temp_packet);
                state = BL_State_DeviceIDRes;
            }break;

            case BL_State_DeviceIDRes:
            {
                if(comms_packets_available())
                {
                    comms_read(&temp_packet);
                    if(is_device_id_packet(&temp_packet) && (temp_packet.data[1] == DEVICE_ID))
                    {
                        simple_timer_reset(&timer);
                        state = BL_State_FWLengthReq;
                    }else
                    {
                        bootloading_fail();
                    }

                }else
                {
                    check_for_timeout();
                }
            }break;

            case BL_State_FWLengthReq:
            {
                simple_timer_reset(&timer);
                comms_create_single_byte_packet(&temp_packet, BL_PACKET_FW_LENGTH_REQ_DATA0);
                comms_write(&temp_packet);
                state = BL_State_FWLengthRes;
            }break;

            case BL_State_FWLengthRes:
            {
                if(comms_packets_available())
                {
                    comms_read(&temp_packet);

                    fw_length = (
                        (temp_packet.data[1])       |
                        (temp_packet.data[2] << 8)  |
                        (temp_packet.data[3] << 16) |
                        (temp_packet.data[4] << 24)   
                    );

                    if(is_fw_length_packet(&temp_packet) && (fw_length <= MAX_FW_LENGTH))
                    {
                        state = BL_State_EraseApplication;
                    }else
                    {
                        bootloading_fail();
                    }
                }else
                {
                    check_for_timeout();
                }
            }break;

            case BL_State_EraseApplication:
            {
                bl_info_set_boot_update();
                bl_flash_erase_main_application();
                comms_create_single_byte_packet(&temp_packet, BL_PACKET_READY_FOR_DATA_DATA0);
                comms_write(&temp_packet);
                simple_timer_reset(&timer);
                state = BL_State_ReceiveFirmware;
            }break;

            case BL_State_ReceiveFirmware:
            {
                if(comms_packets_available())
                {
                    comms_read(&temp_packet);

                    uint8_t packet_len = (temp_packet.length & 0x0f) + 1;
                    bl_flash_write(MAIN_APP_START_ADDRESS + bytes_written, temp_packet.data, packet_len);
                    bytes_written += packet_len;
                    simple_timer_reset(&timer);

                    if(bytes_written >= fw_length)
                    {
                        comms_create_single_byte_packet(&temp_packet, BL_PACKET_UPDATE_SUCCESSFUL_DATA0);
                        comms_write(&temp_packet);
                        state = BL_State_Done;
                    }else
                    {
                        comms_create_single_byte_packet(&temp_packet, BL_PACKET_READY_FOR_DATA_DATA0);
                        comms_write(&temp_packet);
                    }
                }else
                {
                    check_for_timeout();
                }
            }break;
        
            default:
                state = BL_State_Sync;
                break;
        }

    }


    if(bl_info_verify_boot() == INFO_BOOT_OK)
    {
        deinit_boot();
        jump_to_main();
    }

    simple_timer_setup(&timer, 1000, true);

    while(1)
    {
        if(simple_timer_has_elapsed(&timer))
        {
            led->toggle();
        }
    }
}