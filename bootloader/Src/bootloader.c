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
    //bl_flash_erase_main_application();

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
        }

        continue;
    }


    comms_update();

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