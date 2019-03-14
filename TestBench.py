from CANAdapterDevices import CANDapterDevice, CANFrame


class STMBoard:
    def __init__(self):
        self.dcan = CANDapterDevice('/dev/ttyUSB0')
        # TODO add vcan on /dev/ttyUSB2

    def sendSerial():
        pass

    def receiveSerial():
        pass

    def setGPIO():
        pass

    def receiveGPIO():
        pass

    def sendDCAN(self, *args):
        self.__sendCAN(self.dcan, *args)

    def sendVCAN(self, *args):
        self.__sendCAN(self.vcan, *args)

    def receiveDCAN(self):
        self.dcan.readCANMessage()

    def receiveVCAN(self):
        self.vcan.readCANMessage()

    def __sendCAN(self, *args):
        frame = None
        if len(args) == 2 and type(args[1]) is str:
            # The entire message was passed as a string
            if len(args[1]) < 4:
                raise ValueError('CAN is not required length')

            frame = CANFrame(
                int(args[1][0:3], 16),
                None,
                int(args[1][4:], 16)
            )
        elif len(args) == 3:
            if type(args[1]) is not int or type(args[2]) is not int:
                raise ValueError('Both parameters should be of int type')

            frame = CANFrame(
                args[1],
                None,
                args[2]
            )
        else:
            raise ValueError('Incorrect number/type of parameters.')

        args[0].sendCANMessage(frame)


class STM32F4(STMBoard):
    def __init__(self):
        super().__init__()


class STM32L4(STMBoard):
    def __init__(self):
        super().__init__()

    def sendVCAN():
        # L4 doesn't have two CAN channels, so remove one
        pass

    def receiveVCAN():
        # L4 doesn't have two CAN channels, so remove one
        pass
