import serial
import datetime
import warnings
import atexit

ACK = b'\x06' # CANDapter successful acknowledge

class GenericCANAdapterDevice:
    def __init__(self):
        pass

    def sendSerialMessage(self, message):
        pass

    def sendCANMessage(self, id, message):
        pass

    def readCANMessage(self):
        pass


class CANDapterDevice(GenericCANAdapterDevice):
    def __init__(self,
                 port='/dev/ttyUSB0',
                 baudrate=2500000,
                 timeout=None,
                 debug=False):

        super().__init__()
        # Set bitrate to 500Kbit and open CANDapter
        # https://www.ewertenergy.com/products/candapter/downloads/candapter_manual.pdf
        self.canDapterDevice = serial.Serial(port, baudrate, timeout=timeout)
        self.canDapter.sendSerialMessage('S6')
        self.canDapter.sendSerialMessage('O')

        # Always close the connection end, no need for the user to do it manually
        atexit.register(self.closeConnection)

    def sendSerialMessage(self, message):
        self.canDapterDevice.write('{}\r'.format(message).encode())
        self.checkCANDapterResponse()

    def __readSerialMessage(self):
        return self.canDapterDevice.read()

    def sendCANMessage(self, can_id, message):
        data_length = len(str(message)) / 2

        if(data_length % 2 == 1):
            raise ValueError('Invalid data lenght provided to CAN message')

        self.sendSerialMessage('T%(id)s%(length)s%(data)x' % {
            'id': can_id,
            'length': data_length,
            'data': message
        })

    def readCANMessage(self):
        message = self.canDapterDevice.read_until('\r').replace('\r', '')[1:]

        m_id = message[0:3]
        m_len = message[3:4]
        m_message = message[4:-4]
        m_time_stamp = str(datetime.datetime.now())

        return {
            'can_id': m_id,
            'length': m_len,
            'message': m_message,
            'timestamp': m_time_stamp
        }

    def checkCANDapterResponse(self):
        return_message = self.__readSerialMessage()
        if return_message != ACK:
            warnings.warn('CANDapter did not return ACK, instead returned {}'.format(return_message))

    def closeConnection(self):
        self.canDapterDevice.write(b'C\r')
