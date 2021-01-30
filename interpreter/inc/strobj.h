#ifndef __STRING_OBJ_H__
#define __STRING_OBJ_H__

#include "object.h"
#include <string>

struct String : public Object
{
  String(std::string val = "") {
    o_type = str;
    value = val;};
  String(std::string * val) : String(*val){ delete val;};
  virtual obj_t type() {return str;};
  virtual std::string stringify() { return value; };

  std::string value;

};

#endif