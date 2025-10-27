from crc import crc8

def packet_command(command):
    packet = []

    packet.append(0x01)
    packet.append(command)
    for _ in range(15):
        packet.append(0xFF)
    packet.append(crc8(packet))
    return packet

def packet_create_id(id):
    packet = []

    packet.append(0x02)
    packet.append(0x3F)
    packet.append(id)
    for _ in range(14):
        packet.append(0xFF)
    packet.append(crc8(packet))
    return packet

def packet_is_ack(response):
    if(list(response) == packet_command(0x15)):
        return True
    return False

def packet_is_sync(response):
    if(list(response) == packet_command(0x20)):
        return True
    return False

def packet_is_fail(response):
    if(list(response) == packet_command(0x59)):
        return True
    return False

def packet_is_update_res(response):
    if(list(response) == packet_command(0x37)):
        return True
    return False

def packet_is_id_req(response):
    if(list(response) == packet_command(0x3C)):
        return True
    return False

def packet_is_fw_length_req(response):
    if(list(response) == packet_command(0x42)):
        return True
    return False
