#ifndef CAN_IF_H
#define CAN_IF_H

#include <string>
#include <map>
#include <exception>
#include <linux/can.h>
#include <linux/can/raw.h>


// user includes here
#include "exceptions.hpp"



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

  // do nothing
  virtual ~CanFrame() {};

  uint8_t can_id;
  uint8_t can_dlc;
  uint8_t padding;
  uint8_t reserve0;
  uint8_t reserve1;
  uint8_t data[8];
  struct timeval timestamp;

  CanFrame &operator=(const struct can_frame &frame);
  CanFrame &operator=(const CanFrame &frame);
};

/// @note: see https://www.kernel.org/doc/Documentation/networking/can.txt for
///        for info on the socketCAN api
class CanInterface
{
public:
  // Using CAN_RAW sockets is extensively comparable to the commonly
  //     known access to CAN character devices.To meet the new possibilities
  //         provided by the multi user SocketCAN approach,
  //     some reasonable
  //             defaults are set at RAW socket binding time :

  //     -The filters are set to exactly one filter receiving everything -
  //     The socket only receives valid data frames(= > no error message 
  //     frames) - The loopback of sent CAN frames is enabled(see chapter 3.2) 
  //     - The socket does not receive its own sent frames(in loopback mode)

  // these values can be changed to test stuff but i'm not sure how to use the 
  // BCM protocol so it probably won't be changed

  CanInterface(int type = SOCK_RAW, int protocol = CAN_RAW, 
               int enable_own_messages = 0, std::string ifname = "can0");
  virtual ~CanInterface() {};

  CanFrame readCanData();
  int16_t writeCanData(canid_t id, uint8_t dlc, uint8_t * data);

private:
  int can_socket_fd;
  std::string if_name;
  struct sockaddr_can can_addr;
};

#endif