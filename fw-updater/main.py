import serial
from packet import packet_command, packet_is_ack


print("INIT FW-UPDATER")

with serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=2) as ser:
    print("Conectado")
    ser.flushInput()
    ser.flushOutput()


    ser.write("boot\n".encode('utf-8'))
    response = ser.readline()
    response = ser.readline()

    if("BOOT".encode('utf-8') in response):
        print("Boot mode")
        ser.flushInput()
    else:
        print("Error trying to enter boot mode")
        exit()

    print("SEND COMMAND")
    ser.write(packet_command(0x02))
    response = ser.read(18)


    if(packet_is_ack(response)):
        print("ACK")

    