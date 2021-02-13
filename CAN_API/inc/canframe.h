#ifndef __CAN_FRAME_H__
#define __CAN_FRAME_H__

#include <iostream>

#include "can_exceptions.hpp"

// wrapper for the struct can_frame to allow for the = operator to be
// used for assignment
struct CanFrame
{
  CanFrame()
  {
    can_id = 0;
    can_dlc = 0;
    padding = 0;
    reserve0 = 0;
    reserve1 = 0;
  };

  CanFrame(const CanFrame & frame);

  // do nothing since there's no nested pointers
  virtual ~CanFrame() {};

  uint16_t can_id;
  uint8_t can_dlc;
  uint8_t padding;
  uint8_t reserve0;
  uint8_t reserve1;
  uint8_t data[8];
  struct timeval timestamp;

#ifndef WiNDOWS
  CanFrame &operator=(const struct can_frame &frame);
#endif
  CanFrame &operator=(const CanFrame &frame);
};

std::ostream &operator<<(std::ostream &out, const CanFrame &frame);


#endif