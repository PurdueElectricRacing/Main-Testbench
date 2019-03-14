from CANAdapterDevices import CANDapterDevice

canDapter = CANDapterDevice()

while True:
    data = canDapter.readCANMessage()

    print('-- ID:%(id)x \tMessage:%(message)s \tTimestamp: %(time)s' % {
            'id': data['id'],
            'message': data['message'],
            'time': data['timestamp']
    })
