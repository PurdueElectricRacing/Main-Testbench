#ifndef __PERTERPRETER_EXCEPTIONS_H__
#define __PERTERPRETER_EXCEPTIONS_H__

#include <exception>

class SerialDeviceNotConnected : public std::exception
{
  virtual const char *what() const throw()
  {
    return "No generic serial device is connected.\n";
  }
} static SerialDeviceNotConnected;


class NoGPIODevicesFound : public std::exception
{
  virtual const char *what() const throw()
  {
    return "No GPIO interface devices were detected.\n";
  }
} static NoGPIODevicesFound;


class GPIODeviceNotConnected : public std::exception
{
  virtual const char *what() const throw()
  {
    return "No gpio device connected.\n";
  }
} static GPIODeviceNotConnected;


class CANDeviceNotConnected : public std::exception
{
  virtual const char *what() const throw()
  {
    return "No CAN interface connected.\n";
  }
} static CANDeviceNotConnected;



#endif