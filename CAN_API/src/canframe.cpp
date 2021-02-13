#include "canframe.h"
#include <cstring>

#ifndef WINDOWS
#include <socketcan_if.h>
#endif


/// @brief: Copy constructor
CanFrame::CanFrame(const CanFrame &frame)
{
  can_id = frame.can_id;
  can_dlc = frame.can_dlc;
  padding = frame.padding;
  reserve0 = frame.reserve0;
  reserve1 = frame.reserve1;
  timestamp = frame.timestamp;
  memcpy(data, frame.data, 8);
}


#ifndef WINDOWS
/// @brief: assignment operator overload for wrapping struct can_frame
///         does not get a timestamp.
CanFrame& CanFrame::operator=(const struct can_frame &frame)
{
  can_id  = frame.can_id;
  can_dlc = frame.can_dlc;
  padding = frame.__pad;
  reserve0 = frame.__res0;
  reserve1 = frame.__res1;
  memcpy(data, frame.data, 8);

  return *this;
}
#endif;

/// @brief: assignment operator for copying one CanFrame object to another.
CanFrame & CanFrame::operator=(const CanFrame &frame)
{
  can_id = frame.can_id;
  can_dlc = frame.can_dlc;
  padding = frame.padding;
  reserve0 = frame.reserve0;
  reserve1 = frame.reserve1;
  timestamp = frame.timestamp;
  memcpy(data, frame.data, 8);

  return *this;
}


/// @brief: Stream output operator for CanFrame. Allows for printing data frame 
///         to output stream easily
std::ostream &operator<<(std::ostream &out, const CanFrame &frame)
{
  // don't print something that has no data
  if (frame.can_id == 0 && frame.can_dlc == 0)
  {
    return out;
  }

  int val = frame.can_dlc;
  
  out << "CAN ID: " << "0x" << std::hex << frame.can_id
      << " | Data Length: " << std::hex << val << "\n";

  out << "[ ";

  for (uint8_t i = 0; i < frame.can_dlc; i++)
  {
    val = frame.data[i];
    out << std::to_string(i) << ": " << std::hex << val;
    
    if (i != frame.can_dlc - 1)
    {
      out << " | ";
    }
  }

  out << "]\n";
  return out;
}