import serial

def crc8(data):
    crc = 0
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x80:
                crc = (crc << 1) ^ 0x07
            else:
                crc <<= 1
    return (crc & 0xFF)

print("Init fw-updater")

with serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout=20) as ser:
    print("Conectado")
    ser.flushInput()
    ser.flushOutput()
    response = ser.read(10)
    print(response)
    print(''.join(format(x, ' 02x') for x in response))