#ifndef __GPIO_IF_H__
#define __GPIO_IF_H__

#include "serial-device.h"

#include <iostream>
#include <string>
#include <QSerialPort>
#include <QSerialPortInfo>

#define READ_ADC   "READ ADC "
#define READ_GPIO  "READ GPIO "
#define WRITE_DAC  "WRITE DAC "
#define WRITE_GPIO "WRITE GPIO "


class GpioDevice : public SerialDevice
{
public:
  GpioDevice() {
    
  };

  GpioDevice(QSerialPortInfo port) {
    
  };

  virtual ~GpioDevice() {

  };



  /// @brief: writes pin to value (state if it's a digital write)
  void digitalWrite(int pin, int value)
  {
    QString msg = WRITE_GPIO + QString().setNum(pin) + " " 
                + QString().setNum(value) + ";";
    sendCommand(msg);
  };


  /// @brief: reads the digital input in and returns the int value
  int digitalRead(int pin)
  {
    QString msg = READ_GPIO + QString().setNum(pin) + ";";
    int ret = -1;

    // make sure the message was sent before trying to read
    if (sendCommand(msg))
    {
      auto data = serialRead();
      QString str(data);
      std::string temp = str.toStdString();
      
      if (temp.find(";") != std::string::npos)
      {
        temp.erase(temp.find(";"));
      }

      try
      {
        if (!temp.empty())
        {
          ret = std::stoi(temp);
        }
      }
      catch (std::exception & e)
      {
        std::cerr << "Invalid data was received: " << temp << "\n";
      }
    }

    return ret;
    
  };



  /// @brief: write an analog value to the specified pin
  void analogWrite(int pin, int value)
  {
    QString msg = WRITE_DAC + QString().setNum(pin) + " " 
                + QString().setNum(value) + ";";
    sendCommand(msg);
  };



  /// @brief: read the value on the ADC pin and return as an int
  ///
  /// @return: the value read for the pin or -1 if error
  int analogRead(int pin)
  {
    QString msg = READ_ADC + QString().setNum(pin) + ";";
    int ret = -1;

    // make sure the message was sent before trying to read
    if (sendCommand(msg))
    {
      auto data = serialRead();
      std::string temp = data.toStdString();
      
      if (temp.find(";") != std::string::npos)
      {
        temp.erase(temp.find(";"));
      }

      // catch the stoi exception on bad data
      try
      {
        if (!temp.empty())
        {
          ret = std::stoi(temp);
        }
      }
      catch (std::exception & e)
      {
        std::cerr << "Invalid data was received: " << temp << "\n";
      }
    }

    return ret;
  };

};


#endif
