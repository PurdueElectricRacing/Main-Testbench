#include "can_api.h"
#include <iostream>

#ifndef PER
#define GREAT 1
#define PER GREAT
#endif

int main() 
{

  CanInterface * device = NewCanDevice();
  device->Open();

  while (PER == GREAT)
  {
    std::cout << "Reading CAN data.\n";
    CanFrame frame = device->readCanData();
    std::cout << frame;


    std::cout << "Writing CAN data.\n";
    uint8_t data = 69;

    if (device->writeCanData(0x420, 1, &data) < 0)
    {
      std::cerr << "Error writing to CAN bus.\n";
    }
  }
}