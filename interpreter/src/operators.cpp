#include "operators.h"
#include "canmsg.h"
#include "strobj.h"
#include "integer.h"
#include "ast.h"


std::string concat(Object * lhs, Object * rhs)
{
 return (lhs->stringify() + rhs->stringify());
}



std::string concat(Node * lhs, Object * rhs)
{
  return lhs->data.strval + rhs->stringify();
}



std::string concat(Node * lhs, Node * rhs)
{
  return lhs->data.strval + rhs->data.strval;
}



std::string concat(Object * lhs, Node * rhs)
{
  return lhs->stringify() + rhs->data.strval;
}



int unaryMath(Object * o, std::string op)
{
  Integer * i = static_cast<Integer *>(o);
  if (op == "++")
  {
    return i->value++;
  }
  else if (op == "--")
  {
    return i->value--;
  }
  else if (op == "-")
  {
    return -i->value;
  }
  return i->value;
}


int unaryMath(Node * o, std::string op)
{
  if (op == "++")
  {
    return o->data.intval + 1;
  }
  else if (op == "--")
  {
    return o->data.intval - 1;
  }
  else if (op == "-")
  {
    return -o->data.intval;
  }
  return o->data.intval;
}

int unaryMath(int o, std::string op)
{
  if (op == "++")
  {
    return o + 1;
  }
  else if (op == "--")
  {
    return o - 1;
  }
  else if (op == "-")
  {
    return -o;
  }
  return o;
}




/// @brief: Performs a given math operation on the Objects
///         Can be used for unary ops if lhs is the desired object
///         and NULL is passed for rhs
int math(Object * lhs, Object * rhs, std::string op)
{
  Integer * lhsi = static_cast<Integer*>(lhs);
  Integer * rhsi = static_cast<Integer*>(rhs);

  if (op == "+")
  {
    return (lhsi->value + rhsi->value);
  }
  else if (op == "-")
  {
    return (lhsi->value - rhsi->value);
  }
  else if (op == "/")
  {
    return (lhsi->value / rhsi->value);
  }
  else if (op == "*")
  {
    return (lhsi->value * rhsi->value);
  }
  return -1;
}



/// @brief: Performs a given math operation on the Objects
///         Can be used for unary ops if lhs is the desired object
///         and NULL is passed for rhs
int math(Node * lhs, Node * rhs, std::string op)
{
  if (op == "+")
  {
    return (lhs->data.intval + rhs->data.intval);
  }
  else if (op == "-")
  {
    return (lhs->data.intval - rhs->data.intval);
  }
  else if (op == "/")
  {
    return (lhs->data.intval / rhs->data.intval);
  }
  else if (op == "*")
  {
    return (lhs->data.intval * rhs->data.intval);
  }
  return -1;
}



int math(Object * lhs, Node * rhs, std::string op)
{
  Integer * lhsi = static_cast<Integer *>(lhs);
  if (op == "+")
  {
    return (lhsi->value + rhs->data.intval);
  }
  else if (op == "-")
  {
    return (lhsi->value - rhs->data.intval);
  }
  else if (op == "/")
  {
    return (lhsi->value / rhs->data.intval);
  }
  else if (op == "*")
  {
    return (lhsi->value * rhs->data.intval);
  }
  return -1;
}




int math(Node * lhs, Object * rhs, std::string op)
{
  Integer * rhsi = static_cast<Integer *>(rhs);
  if (op == "+")
  {
    return (lhs->data.intval + rhsi->value);
  }
  else if (op == "-")
  {
    return (lhs->data.intval - rhsi->value);
  }
  else if (op == "/")
  {
    return (lhs->data.intval / rhsi->value);
  }
  else if (op == "*")
  {
    return (lhs->data.intval * rhsi->value);
  }
  return -1;
}




bool compare(Object * lhs, Object * rhs, std::string op)
{
  // be lazy and just turn them both into strings because I don't want to write all the code required
  if (op == "EQ" || op == "==")
  {
    return lhs->stringify() == rhs->stringify();
  }
  else if (op == "NE" || op == "!=")
  {
    return lhs->stringify() != rhs->stringify();
  }
  else 
  {
    Integer * l = static_cast<Integer *>(lhs);
    Integer * r = static_cast<Integer *>(rhs);

    if (op == "GT" || op == ">")
    {
      return l->value > r->value;
    }
    else if (op == "LT" || op == "<")
    {
      return l->value < r->value;

    }
    else if (op == "LE" || op == "<=")
    {
      return l->value <= r->value;
    }
    else if (op == "GE" || op == ">=")
    {
      return l->value >= r->value;
    }
  }
  return false;
}


bool compare(Object * lhs, Node * rhs, std::string op)
{
  // be lazy and just turn them both into strings because I don't want to write all the code required
  std::string rhs_str;

  if (rhs->node_type == integerLiteral_node)
  {
    rhs_str = std::to_string(rhs->data.intval);
  }
  else
  {
    rhs_str = rhs->data.strval;
  }

  if (op == "EQ")
  {
    return lhs->stringify() == rhs_str;
  }
  else if (op == "NE")
  {
    return lhs->stringify() != rhs_str;
  }
  else 
  {
    Integer * l = static_cast<Integer *>(lhs);

    if (op == "GT")
    {
      return l->value > rhs->data.intval;
    }
    else if (op == "LT")
    {
      return l->value < rhs->data.intval;

    }
    else if (op == "LE")
    {
      return l->value <= rhs->data.intval;
    }
    else if (op == "GE")
    {
      return l->value >= rhs->data.intval;
    }
  }
  return false;
}




bool compare(Node * lhs, Object * rhs, std::string op)
{
  std::string lhs_str;
  if (lhs->node_type == integerLiteral_node)
  {
    lhs_str = std::to_string(lhs->data.intval);
  }
  else
  {
    lhs_str = lhs->data.strval;
  }

  if (op == "EQ")
  {
    return lhs_str == rhs->stringify();
  }
  else if (op == "NE")
  {
    return lhs_str != rhs->stringify();
  }
  else 
  {
    Integer * r = static_cast<Integer *>(rhs);

    if (op == "GT")
    {
      return lhs->data.intval > r->value;
    }
    else if (op == "LT")
    {
      return lhs->data.intval < r->value;

    }
    else if (op == "LE")
    {
      return lhs->data.intval <= r->value;
    }
    else if (op == "GE")
    {
      return lhs->data.intval >= r->value;
    }
  }
  return false;
}




bool compare(Node * lhs, Node * rhs, std::string op)
{
  std::string lhs_str;
  std::string rhs_str;

  if (lhs->node_type == integerLiteral_node)
  {
    lhs_str = std::to_string(lhs->data.intval);
  }
  else
  {
    lhs_str = lhs->data.strval;
  }
  
  if (rhs->node_type == integerLiteral_node)
  {
    rhs_str = std::to_string(rhs->data.intval);
  }
  else
  {
    rhs_str = rhs->data.strval;
  }

  if (op == "EQ")
  {
    return lhs_str == rhs_str;
  }
  else if (op == "NE")
  {
    return lhs_str != rhs_str;
  }
  else 
  {

    if (op == "GT")
    {
      return lhs->data.intval > rhs->data.intval;
    }
    else if (op == "LT")
    {
      return lhs->data.intval < rhs->data.intval;

    }
    else if (op == "LE")
    {
      return lhs->data.intval <= rhs->data.intval;
    }
    else if (op == "GE")
    {
      return lhs->data.intval >= rhs->data.intval;
    }
  }
  return false;
}




