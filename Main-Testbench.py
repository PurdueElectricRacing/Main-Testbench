from CANAdapterDevices import SerialCANDapterDevice

canDapter = SerialCANDapterDevice()

while True:
    data = canDapter.readCANMessage()

    print('-- ID:%(id)x \tMessage:%(message)s \tTimestamp: %(time)s' % {
            'id': data['id'],
            'message': data['message'],
            'time': data['timestamp']
    })
