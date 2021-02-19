#ifndef __CAN_MSG_H__
#define __CAN_MSG_H__

#include "object.h"
#include <cstring>
#include <sstream>
#include <iomanip>
#include <exception>
#include <iostream>
#include "canframe.h"


class CAN_Msg : public Object
{
public:

  CAN_Msg(std::string input) : CAN_Msg() {
    len = -1;
    parse(input);
    o_type = can_msg_obj;
  };
  CAN_Msg() {
    memset(data, 0, 8);
  };

  CAN_Msg(CanFrame frame) {
    len = frame.can_dlc;
    memcpy(data, frame.data, frame.can_dlc);
    valid = true;
  };

  virtual ~CAN_Msg(){};

  void parse(std::string input)
  {
    size_t i = 0; 
    size_t last_sep = input.find("|");

  try
  {
    while (last_sep != std::string::npos)
    {
      std::string byteval = input.substr(0, last_sep);
      uint val = 0;
      input.erase(0, last_sep + 1);
      byteval = "0x" + byteval;
      val = std::stoul(byteval, 0, 16);

      if (val > 0xFF)
      {
        valid = false;
        return;
      }

      data[i] = val;

      last_sep = input.find("|");
      i++;
    }
    if (!input.empty())
    {
      input = "0x" + input;
      data[i] = std::stoul(input, 0, 16);;
    }
    valid = true;
    len = i + 1;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what();
    valid = false;
  }
  };

  virtual obj_t type() {return can_msg_obj;};

  virtual std::string stringify() { 
    std::string ret;

    for (size_t i = 0; i < 8; i++)
    {
      // do not move this variable out of the loop
      // it needs re-init every iteration
      std::stringstream ss;
      ss << std::hex << (uint) data[i];
      ret += ss.str();
      if (i < 7)
        ret += "|";
    }
    return ret;
  };

  bool validData() {return valid;};

  uint8_t get(int idx)
  {
    if (idx >= len)
    {
      return data[len - 1];
    }
    return data[idx];
  };

  uint8_t length() {
    return len;
  }

  uint8_t setData(uint index, uint val) 
  {
    if (index > len)
    {
      return -1;
    }
    data[index] = val;
    return val;
  }

  uint setLeng(uint8_t newlen) { 
    if (newlen <= 8) 
    {
      len = newlen; 
      return newlen;
    }
    std::cerr << "Runtime error: Cannot assign new length of " << newlen 
              << " to CAN Frame. Length is greater than 8.\n\n";
    return -1;
  };

  std::string toString()
  {
    std::string ret = "[";
    for (uint8_t i = 0; i < len; i++)
    {
      ret += " " + std::to_string(data[i]);
    }

    ret += " ]";
    return ret;
  }

  uint8_t * Data() { return data; };
  uint8_t Len() { return len; };

  std::ostream& operator<<(std::ostream &stream)
  {
    stream << toString();
    return stream;
  }

private:
  uint8_t data[8];
  uint8_t len;
  bool valid = false;
};

#endif