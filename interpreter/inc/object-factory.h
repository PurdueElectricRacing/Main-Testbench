#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__


#include "ast.h"
#include "object.h"
#include "strobj.h"
#include "integer.h"
#include "canmsg.h"
#include "synterr.h"

// Factory for creating objects from a given node
namespace ObjectFactory {


/// @note: The family of functions in this section are for local use only and
//         are intended to allow for unit testing 
// ==========================================================

static Object * createLiteral(obj_t type, std::string s, int lineno=0)
{
  Object * ret = 0;
  if (type == str)
  {
    ret = new String(s);
  }
  else 
  {
    CAN_Msg * m = new CAN_Msg(s);
        
    if (m->validData())
    {
      ret = m;
    }
    else
    {
      invalidCanDecl(s, lineno);
      ret = NULL;
    }
  }
  return ret;
}



static Object * createLiteral(int val)
{
  return new Integer(val);
}


static Object * createGeneric(obj_t otype)
{
  Object * ret = 0;
  if (otype == integer)
  {
    ret = new Integer();
  }
  else if (otype == str)
  {
    ret = new String();
  }
  else if (otype == can_msg_obj)
  {
    ret = new CAN_Msg();
  }
  else if (otype == none)
  {
    ret = new Object();
  }
  else
  {
    ret = NULL;
  }
  return ret;
}

// ==========================================================


/// @brief: creates a new object based on the information stored in the Node *
///         if the node is a literal it will read the data value and return an 
///         object with that data, otherwise it will create an empty object of 
///         the type specified by otype
static Object * createObject(Node * node, obj_t otype = invalid)
{
  Object * ret = 0;
  
  if (node->isLiteral())
  {
    if (node->type == str || node->type == can_msg_obj)
    {
      ret = createLiteral(node->type, node->data.strval);
    }
    else if (node->type == integer)
    {
      ret = createLiteral(node->data.intval);
    }
  }
  else
  {
    ret = createGeneric(otype);
  }

  return ret;
}
};


#endif