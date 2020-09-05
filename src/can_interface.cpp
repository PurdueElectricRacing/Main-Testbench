// C includes
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>

// C++ includes
#include <iostream>

// user includes
#include "can_interface.hpp"

/// @brief: Constructor
///         Handles creation of CAN socket and initialization
///         of necessary data.
CanInterface::CanInterface(int type, int protocol, int enable_own_messages, std::string ifname)
{
  int fd;
  struct ifreq ifr;
  can_err_mask_t err_mask = CAN_ERR_MASK;   // default to receive every error

  // attempt to open the socket
  fd = socket(PF_CAN, type, protocol);

  if (fd == -1)       // error opening socket
  {
    perror("CanInterface constructor socket call");
    throw CanSocketException;
  }

  strcpy(ifr.ifr_name, ifname.c_str());

  can_addr.can_family = AF_CAN;
  can_addr.can_ifindex = ifr.ifr_ifindex;

  // enable all error messages to be received
  setsockopt(fd, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask, sizeof(err_mask));
  // enable or disable receipt of our messages. Default is disabled
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
