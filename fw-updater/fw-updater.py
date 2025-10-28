import serial
from crc import crc8
from packet import packet_command, packet_is_ack, packet_is_sync, \
    packet_is_fail, packet_is_update_res, packet_create_id, packet_is_id_req, \
    packet_is_fw_length_req, packet_create_fw_length, packet_is_ready_for_data, \
    packet_is_succesful

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
    print(len(raw_file))
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

    # SEND FIRMWARE
    written_bytes = 0
    packet_len = 0
    len_to_send = len(raw_file)

    while(not packet_is_succesful(response)):
        packet = []
        if(len_to_send <= 0):
            print("ERROR LEN")
            print(list(response))
            response = ser.read(18)
            print(list(response))
            exit()

        if(len_to_send > 16):
            packet_len = 16
        else: 
            packet_len = len_to_send

        packet.append(packet_len)
        for x in range(16):
            if(x < packet_len):
                packet.append(raw_file[written_bytes + x])
            else:
                packet.append(0xFF)
        packet.append(crc8(packet))

        ser.write(packet)
        written_bytes += packet_len
        len_to_send -= packet_len

        response = ser.read(18)
        if not packet_is_ack(response): 
            print("ERROR ACK")
            exit()
        
        response = ser.read(18)
        if(packet_is_ready_for_data(response)):
            print(str(written_bytes) + "/" + str(len(raw_file)))
            #print(packet)
            continue
        elif(packet_is_succesful(response)):
            print("SUCCESFUL")
            exit()
        else:
            print(response)
            print("ERROR RECEIVE NOT READY")
            exit()

