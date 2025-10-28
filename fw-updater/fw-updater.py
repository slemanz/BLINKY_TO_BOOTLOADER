import serial
from packet import packet_command, packet_is_ack, packet_is_sync, \
    packet_is_fail, packet_is_update_res, packet_create_id, packet_is_id_req, \
    packet_is_fw_length_req, packet_create_fw_length, packet_is_ready_for_data

print("INIT FW-UPDATER")

try:
    BOOTLOADER_SIZE = 0x8000
    with open("Build/flash.bin", "rb") as f:
        f.read(BOOTLOADER_SIZE)
        raw_file = f.read()
except:
    print("Error trying to open flash.bin file")
    exit()


with serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=2) as ser:
    print("Conectado")
    ser.flushInput()
    ser.flushOutput()

    # SYNC
    sync = [0xC4, 0x55, 0x7E, 0x10]
    ser.write(sync)
    response = ser.read(18)
    print("SYNC") if packet_is_sync(response) else exit()


    # UPDATE REQ
    ser.write(packet_command(0x31))
    response = ser.read(18)
    if not packet_is_ack(response): exit()

    response = ser.read(18)
    if(packet_is_update_res(response)):
        print("UPDATE RES")
    elif(packet_is_fail(response)):
        print("UPDATE RES FAIL")
        exit()
    else:
        exit()


    # ID
    response = ser.read(18)
    if(packet_is_id_req(response)):
        print("ID REQ")
    else:
        exit()
    
    ser.write(packet_create_id(0x42))
    response = ser.read(18)
    if not packet_is_ack(response): exit()

    # FW LENGTH REQ
    response = ser.read(18)
    if(packet_is_fw_length_req(response)):
        print("FW LENGTH REQ")
    elif (packet_is_fail(response)):
        print("FW UPDATE FAIL")
        exit()
    else:
        exit()

    # FW LENGTH RES
    print("FW LENGTH RES")
    ser.write(packet_create_fw_length(len(raw_file)))
    response = ser.read(18)
    if not packet_is_ack(response): exit()

    # READY FOR DATA
    ser.timeout = 20

    response = ser.read(18)
    if(packet_is_ready_for_data(response)):
        print("READY FOR DATA")
    elif (packet_is_fail(response)):
        print("FW UPDATE FAIL")
        exit()
    else:
        exit()
    

    ser.timeout = 2

