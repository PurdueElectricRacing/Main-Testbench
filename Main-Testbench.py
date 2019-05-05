from TestBench import STM32F4
import RPi.GPIO as rGPIO
import time

board = STM32F4()

while True:
    data = board.receiveDCAN()

    print('-- ID: {:<10x}Message: {:<15x}Timestamp:{:s}'
          .format(data.id, data.data, data.timestamp))
