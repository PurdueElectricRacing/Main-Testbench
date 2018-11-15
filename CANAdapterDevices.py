import serial


class CANFrame:
    def __init__(self, m_id, m_timestamp, m_data):
        self.id = m_id
        self.data = m_data
        self.timestamp = m_timestamp
        self.length = len(str(canFrame.data)) / 2

        if(self.length % 2 == 1):
            raise ValueError(
                'Invalid data lenght provided to CANFrame object.'
                )


class GenericCANAdapterDevice:
    def __init__(self):
        pass

    def sendSerialMessage(self, message):
        pass

    def sendCANMessage(self, id, message):
        pass

    def readCANMessage(self):
        pass


class SerialCANDapterDevice(GenericCANAdapterDevice):
    def __init__(self,
                 port='/dev/ttyUSB0',
                 baudrate=2500000,
                 timeout=None,
                 debug=False):

        super().__init__()
        self.canDapterDevice = serial.Serial(port, baudrate, timeout=timeout)

    def sendSerialMessage(self, message):
        self.canDapterDevice.write(message + '\r')

    def sendCANMessage(self, canFrame):
        self.sendSerialMessage('T%(id)s%(length)s%(data)x' % {
            'id': canFrame.id,
            'length': canFrame.length,
            'data': canFrame.data
        })

    def readCANMessage(self):
        message = self.canDapterDevice.read_until('\r').replace('\r', '')[1:]

        m_id = message[0:3]
        m_len = message[3:4]
        m_message = message[4:-4]
        m_time_stamp = str(datetime.datetime.now())

        canFrame = CANFrame(m_id, m_time_stamp, m_message)

        assert m_len == canFrame.length

        return canFrame
