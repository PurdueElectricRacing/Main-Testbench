#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include "typedefs.h"
#include <iostream>

struct Object
{
  Object() {};
  virtual ~Object() {}
  virtual obj_t type(){return none;};
  virtual std::string stringify(){ 
    return std::to_string((size_t)this) + ": type: none";
  };
  obj_t o_type = none;
};


#endif