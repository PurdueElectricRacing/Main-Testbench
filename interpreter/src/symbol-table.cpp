#include "symbol-table.h"
#include "integer.h"
#include "canmsg.h"
#include "strobj.h"

#include "synterr.h"

std::set<std::string> global_var_keys = {
  "SERIAL_LOG_FILE",
  "RETVAL", 
  "LOG_FILE", 
  "VERBOSE",  
  "SERIAL_DEVICE", 
  "GPIO_DEVICE"
};


SymbolTable::SymbolTable(Node * root) 
{
  this->root = root;
  globals = 0;
}



/// @brief: deletes the old object and updates it to be o. Must be a heap object
void SymbolTable::setRetval(Object * o)
{
  setObject("RETVAL", o);
}


void SymbolTable::setReadOnlyVar(std::string key, Object * o)
{

}



/// @brief: updates the variable "key" with the new object o
///         This is strictly for adding global variables or modifying existing 
///         ones
bool SymbolTable::setGlobal(std::string key, Object * o)
{
  // don't allow writing to global RO vars
  if (global_var_keys.find(key) != global_var_keys.end() && key != "RETVAL")
  {
    invalidWriteToReadOnlyValue(key);
    return false;
  }

  // global symbol table
  if (type() == generic_table)
  {
    if (symbols.find(key) != symbols.end())
    {
      Object * old = symbols[key];
      delete old;
      symbols[key] = o;
    }
    else
    {
      symbols.emplace(key, o);
    }
  }
  else
  {
    globals->setGlobal(key, o);
  }
  return true;
}



/// @brief: updates the variable "key" with the new object o
///         will check both global and local symbols for the key
void SymbolTable::setObject(std::string key, Object * o)
{
  Object * old = 0;

  // check the current scope first, and delete it if it exists
  if (symbols.find(key) != symbols.end())
  {
    old = symbols[key];
    delete old;
    symbols[key] = o;
  }
  // if this table is not the global one, then check the global
  // table for the symbol before adding it this table
  else if (globals && globals->getObject(key))
  {
    globals->setObject(key, o);
  }
  // object wasn't in globals and not in this one, add it to this one
  else 
  {
    symbols.emplace(key, o);
  }
}


bool SymbolTable::find(Object * o)
{
  for (auto i = symbols.begin(); i != symbols.end(); i++)
  {
    if (i->second == o)
    {
      return true;
    }
  }
  return false;
}



/// @brief: get the object named <key> from either a local or global scope
///
/// @return: pointer to the object if it exists, NULL if not
Object * SymbolTable::getObject(std::string key)
{
  if (symbols.find(key) != symbols.end())
  {
    return symbols[key];
  }
  if (type() != generic_table && globals)
  {
    return globals->getObject(key);
  }

  // this theoretically should never happen
  return NULL;
}



/// @brief Constructor for a routine symbol table
Routine::Routine(Node * root, SymbolTable * globes)
{
  this->root = root;
  this->globals = globes;
}


/// @brief Constructor for a Test symbol table
Test::Test(Node * root, SymbolTable * globes)
{
  this->root = root;
  this->globals = globes;
}




/// @brief: add a new routine to the contained symbol table
///         Will print error if a matching routine was already declared.
///
/// @return: pointer to the new Routine object on success, null on fail
Routine * Routines::addRoutine(Node * node, SymbolTable * global)
{
  Routine * r = 0;
  if (routines.find(node->data.strval) != routines.end())
  {
    funcAlreadyDefined(node->data.strval, "routine", node->line_no);
    return NULL;
  }
  r = new Routine(node, global);
  routines.emplace(node->data.strval, r);
  return r;
}



/// @brief: get the routine with name key from the list. Will print error if 
///         the routine is not found.
///
/// @return: pointer to the routine table if found or NULL on error;
Routine * Routines::getRoutine(std::string key, int lineno)
{
  if (routines.find(key) != routines.end())
  {
    return routines[key];
  }
  funcUndefined(key, "routine", lineno);
  return NULL;
}


bool Routines::hasRoutine(std::string key)
{
  if (routines.find(key) != routines.end())
  {
    return true;
  }
  return false;
}






/// @brief: add a new test to the contained symbol table
///         Will print error if a matching test was already declared.
///
/// @return: pointer to the new Test object on success, null on fail
Test * Tests::addTest(Node * node, SymbolTable * global)
{
  Test * t = 0;
  if (tests.find(node->data.strval) != tests.end())
  {
    funcAlreadyDefined(node->data.strval, "test", node->line_no);
    return NULL;
  }
  t = new Test(node, global);
  tests.emplace(node->data.strval, t);
  return t;
}



/// @brief: get the test with name key from the list. Will print error if 
///         the test is not found.
///
/// @return: pointer to the Test table if found or NULL on error;
Test * Tests::getTest(std::string key, int lineno)
{
  if (tests.find(key) != tests.end())
  {
    return tests[key];
  }
  funcUndefined(key, "test", lineno);
  return NULL;
}

/// @brief: check if the test name is defined.
///
/// @return: true if it is, false if not
bool Tests::hasTest(std::string key)
{
  return (tests.find(key) != tests.end());
}