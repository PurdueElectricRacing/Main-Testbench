#ifndef __INTEGER_H__
#define __INTEGER_H__

#include "object.h"
#include "typedefs.h"

struct Integer : public Object 
{
  Integer(int val = 0) 
  { 
    o_type = integer; 
    value = val; 
  };
  virtual ~Integer() {};
  virtual obj_t type() {return integer;};
  virtual std::string stringify() { return std::to_string(value); };
  int value;
};

#endif