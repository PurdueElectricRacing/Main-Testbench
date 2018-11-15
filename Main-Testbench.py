from CANAdapterDevices import SerialCANDapterDevice

canDapter = SerialCANDapterDevice()

# Set bitrate to 500Kbit and open CANDapter
canDapter.sendSerialMessage('S6')
canDapter.sendSerialMessage('O')

while True:
    data = canDapter.readCANMessage()

    print('-- ID:%(id)x \tMessage:%(message)s \tTimestamp: %(time)s' % {
            'id': data['id'],
            'message': data['message'],
            'time': data['timestamp']
    })
