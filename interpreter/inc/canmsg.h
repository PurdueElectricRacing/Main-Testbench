#ifndef __CAN_MSG_H__
#define __CAN_MSG_H__

#include "object.h"
#include <cstring>
#include <sstream>
#include <iomanip>
#include <exception>
#include <iostream>


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
      input.erase(0, last_sep + 1);
      int val = std::stoi(byteval);

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
      data[i] = std::stoi(input);
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
    std::stringstream ss;

    for (size_t i = 0; i < 8; i++)
    {
      ss << std::hex << data[i];
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

  uint8_t * Data() { return data; };
  uint8_t Len() { return len; };

private:
  uint8_t data[8];
  uint8_t len;
  bool valid = false;
};

#endif