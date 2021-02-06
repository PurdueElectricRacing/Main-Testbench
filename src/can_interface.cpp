// C includes
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/sockios.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <asm/sockios.h>
#include <iomanip>

// C++ includes
#include <iostream>

// user includes
#include "can_interface.h"

/// @brief: Constructor
///         Handles creation of CAN socket and initialization
///         of necessary data.
CanInterface::CanInterface(int type, int protocol, int enable_own_messages, std::string ifname)
{
  int fd;
  struct ifreq ifr;

  // attempt to open the socket
  fd = socket(PF_CAN, type, protocol);

  if (fd < 0)       // error opening socket
  {
    perror("CanInterface constructor socket call");
    throw CanSocketException;
  }

  strcpy(ifr.ifr_name, ifname.c_str());
  ioctl(fd, SIOCGIFINDEX, &ifr);

  can_addr.can_family = AF_CAN;
  can_addr.can_ifindex = ifr.ifr_ifindex;

  // // enable or disable receipt of our messages. Default is disabled
  setsockopt(fd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &enable_own_messages, 
            sizeof(enable_own_messages));

  // if bind fails throw an exception
  if (bind(fd, (struct sockaddr *) &can_addr, sizeof(can_addr)) != 0)
  {
    perror("CanInterface constructor bind call");
    throw CanSocketException;
  }

  can_socket_fd = fd;
  if_name = ifname;
}

/// @brief: send data to the address specified by id
///
/// @note: see https://www.kernel.org/doc/Documentation/networking/can.txt for 
///        for info on the socketCAN api
///
/// @return: number of bytes written, or -1 on error
int16_t CanInterface::writeCanData(canid_t id, uint8_t dlc, uint8_t *data)
{
  can_frame frame;
  int16_t bytes = 0;

  frame.can_dlc = dlc;
  frame.can_id = id;
  memcpy(frame.data, data, dlc);

  bytes = sendto(can_socket_fd, &frame, sizeof(struct can_frame), 0, 
                 (struct sockaddr *) &can_addr, sizeof(can_addr));

  if (bytes == -1)
  {
    perror("writeCanData: sendto");
    return 0;
  }

  return bytes;
}


/// @brief: reads whatever is in the CAN buffer and returns a CanFrame object
///
/// @return:
CanFrame CanInterface::readCanData()
{
  CanFrame frame_obj;
  struct can_frame frame;
  
  int32_t nbytes = 0;
  struct timeval timeout;
  fd_set fdset;

  timeout.tv_sec = 1; // 1 second
  timeout.tv_usec = 0;

  FD_ZERO(&fdset);
  FD_SET(can_socket_fd, &fdset);

  int rv = select(can_socket_fd+1, &fdset, NULL, NULL, &timeout);
  
  // copy pasted this from the kernel documentation
  if (rv > 0)
  {
    nbytes = read(can_socket_fd, &frame, sizeof(struct can_frame));
    if (nbytes < 0)
    {
      perror("can raw socket read");
      throw CanDataException;
    }

    // suppress compiler warnings grumble grumble
    if (((uint64_t) nbytes) < sizeof(struct can_frame))
    {
      fprintf(stderr, "read: incomplete CAN frame\n");
      throw CanDataException;
    }

    frame_obj = frame;
  }  

  // get the timestamp of the message and store it in the wrapper class.
  ioctl(can_socket_fd, SIOCGSTAMP, &(frame_obj.timestamp));

  return frame_obj;
}



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
