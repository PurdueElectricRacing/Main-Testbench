#include "type-checker.h"
#include "synterr.h"
#include "symbol-table.h"
#include "object-factory.h"


extern std::set<std::string> global_var_keys;

/// @brief: recurses through the AST to perform syntax validation.
///         This family of functions will handle printing syntax errors
///
/// @return: true if the syntax was good, false if there was an error
bool checkTypes(Node * root, SymbolTable * currscope, Tests *tests, Routines *routines)
{

  bool ret = true;
  // create a new global symbol table pointer

  for(auto child = root->children.begin();child != root->children.end();child++)
  {
    Node * node = *child;
    node_type_t type = node->node_type;

    // recurse for any of the list nodes
    if (type == routine_list_node || type == test_list_node
        || type == vardecl_list_node || type == statement_list)
    {
      bool localret = checkTypes(node, currscope, tests, routines);

      if (ret)
      {
        ret = localret;
      }
    }
    else if (type == vardecl_node)
    {
      obj_t rhst = checkVardecl(node, currscope);
      if (rhst != invalid)
      {
        currscope->insert(node->data.strval, 
                          ObjectFactory::createObject(node->children[0], rhst));
      }
    }
    else if (type == call_node)
    {
      // die if someone is trying to call a test
      if (tests->hasTest(node->data.strval))
      {
        notCallable(node->data.strval, node->line_no);
      }
      else
      {
        routines->getRoutine(node->data.strval, node->line_no);
      }
    }
    else if (type == serial_tx || type == print || type == println
             || type == prompt_node)
    {
      checkSingleParamCmd(node, currscope);
    }
    else if (type == send_msg_node)
    {
      checkSendMsg(node, currscope);
    }
    else if (type == read_msg_node)
    {
      checkReadMsg(node, currscope);
    }
    else if (type == analog_write || type == digital_write)
    {
      checkPinWrite(node, currscope);
    }
    else if (type == loop_node)
    {
      // don't try to check the node if it's a forever keyword
      if (node->children[0]->node_type != forever_node)
      {
        checkIntegralArg(node, currscope);
      }
      checkTypes(node, currscope, tests, routines);
    }
    // these commands take 1 integral argument 
    //(can be in the form of an expressions
    else if (type == delay_node || type == loop_node)
    {
      checkIntegralArg(node, currscope);
    }
    else if (type == digital_read || type == analog_read)
    {
      if (checkIntegralArg(node, currscope))
      {
        currscope->setRetval(new Integer());
      }
    }    
    else if (type == routine_node)
    {
      currscope = routines->addRoutine(node, currscope);
      checkTypes(node, currscope, tests, routines);
    }
    else if (type == test_node)
    {
      currscope = tests->addTest(node, currscope);
      checkTypes(node, currscope, tests, routines);
    }
    else if (type == assert_node || type == expect_node)
    {
      checkExpectAssert(node, currscope);
    }
    else if (type == serial_rx)
    {
      currscope->setRetval(new String());      
    }
  }
}


/// @brief: check the parameters a pin write, must be <integer> <integer>
///         Will print error messages to stderr
///
/// @return: true if valid parameters, false if
bool checkPinWrite(Node * node, SymbolTable * currscope) 
{
  bool ret = true;
  obj_t pin_type = checkExp(node->children[0], currscope);
  
  // call to analog write
  if (node->children.size() > 1)
  {
    obj_t value_type = checkExp(node->children[1], currscope);
    if (value_type != integer)
    {
      invalidParameters(value_type, integer, node->key, node->line_no);
      ret = false;
    }
  }

  if (pin_type != integer)
  {
    invalidParameters(pin_type, integer, node->key, node->line_no);
    ret = false;
  }


  return ret;
}



/// @brief: check the parameters for single integer cmds
///         Will print error messages to stderr
///
/// @return: true if valid parameters, false if
bool checkIntegralArg(Node * node, SymbolTable * currscope) 
{
  bool ret = true;
  obj_t type = checkSingleParamCmd(node, currscope);
  if (type != integer)
  {
    invalidParameters(type, node->key, node->line_no);
  }
  return ret;
}



/// @brief: check the parameters for send-msg - must provide integral ID and 
///         CAN-Msg type for the data to send
///         Will print error messages to stderr
///
/// @return: true if valid parameters, false if not
bool checkSendMsg(Node * node, SymbolTable * currscope) 
{
  bool ret = true;
  obj_t id_type = checkExp(node->children[0], currscope);
  obj_t msg_type = checkExp(node->children[1], currscope);

  if (msg_type != can_msg_obj)
  {
    invalidParameters(msg_type, can_msg_obj, node->key, node->line_no);
    ret = false;
  }

  if (id_type != integer)
  {
    invalidParameters(id_type, integer, node->key, node->line_no);
    ret = false;
  }

  return ret;
}



/// @brief: check the parameters for read-msg - must have integral 
///         Will print error messages to stderr
///
/// @return: true if valid parameters, false if not
bool checkReadMsg(Node * node, SymbolTable * currscope) 
{
  bool ret = true;
  obj_t id_type = checkExp(node->children[0], currscope);
  currscope->setRetval(new CAN_Msg());

  if (id_type != integer)
  {
    invalidParameters(id_type, integer, node->key, node->line_no);
    ret = false;
  }

  return ret;
}



/// @brief: check the parameters for serial-tx - ensure no type mismatch
///         Will print error messages to stderr
///
/// @return: true if valid parameters, false if not
obj_t checkSingleParamCmd(Node * node, SymbolTable * currscope) 
{
  Node * exp = node->children[0];
  obj_t exptype = checkExp(exp, currscope);

  if (exptype == invalid || exptype == none)
  {
    invalidParameters(exptype, node->key, node->line_no);
  }

  return exptype;
}



/// @brief: check the parameters for the variable declaration / assignment
///         (no invalid expressions)
///         Will print error messages to stderr
///
/// @return: true if valid parameters, false if not
obj_t checkVardecl(Node * node, SymbolTable * currscope) 
{
  obj_t exptype = checkExp(node->children[0], currscope);
  std::string varname = node->data.strval;

  if (global_var_keys.find(varname) != global_var_keys.end())
  {
    if (varname != "RETVAL" && exptype != currscope->objectType(varname))
    {
      invalidGlobalOverwrite(varname, node->line_no, exptype);
      exptype = invalid;
    }
    return exptype;
  }

  if (exptype == invalid)
  {
    invalidVarDecl(exptype, node->line_no);
  }

  if (currscope->getObject(node->data.strval) != NULL)
  {
    varAlreadyDefined(node->data.strval, node->line_no);
    exptype = invalid;
  } 

  return exptype;
}



/// @brief: checks the expressions for and / or in expect / assert calls
///         will print error message to stderr
/// @return: the type that all sub expressions return, or invalid if some dont' match
obj_t checkLogicalExp(Node * exp, SymbolTable * currscope)
{
    Node * lhs = exp->children[0];
    Node * rhs = exp->children[1];
    // recursively check the left and right hand sides of the subtrees
    obj_t lhst = none;
    obj_t rhst = none;

    // recurse if logical conjuction
    if (lhs->node_type == and_node || lhs->node_type == or_node)
    {
      lhst = checkLogicalExp(lhs, currscope);
    }
    else if (lhs->node_type == comparison_node)
    {
      lhs = lhs->children[0];
      lhst = checkExp(lhs, currscope);
    }
    // Something done messed up
    else 
    {
      std::cerr<<"you done messed up son. The child of a logical conjunction was " << nodeTypeToString(lhs->node_type);
      lhst = invalid;
    }

     // recurse if logical conjuction
    if (rhs->node_type == and_node || rhs->node_type == or_node)
    {
      rhst = checkLogicalExp(rhs, currscope);
    }
    else if (rhs->node_type == comparison_node)
    {
      rhs = rhs->children[0];
      rhst = checkExp(rhs, currscope);
    }
    // Something done messed up
    else 
    {
      std::cerr<<"you done messed up son. The child of a logical conjunction was " << nodeTypeToString(rhs->node_type);
      rhst = invalid;
    }

    if (rhst != lhst)
    {
      mismatched_type(lhst, rhst, exp->line_no, exp->key);
      return invalid;
    }

  return lhst;
}



/// @brief: check the parameters for expect / assert and ensure no type mismatch
///         Will print error messages to stderr
///
/// expect statements take the form expect | assert <comparison> Exp 
///                                             (and|&& <comparison> Exp)* 
///                                             (or|'||' <comparison> Exp)* 
///                                             (and|&& <comparison> Exp)*
/// Exp must resolve to one of the primitive types (string, integer, can-msg)
/// cannot be a none type
///
/// @return: true if valid parameters, false if not
bool checkExpectAssert(Node * node, SymbolTable * currscope) 
{
  bool ret = true;
  obj_t exptype = none;
  Node * exp = node->children[0];
  Object * retval = currscope->getObject("RETVAL");

  if (exp->node_type == and_node || exp->node_type == or_node)
  {
    exptype = checkLogicalExp(exp, currscope);
  }
  else if (exp->node_type == comparison_node)
  {
    std::string op = exp->data.strval;
    exp = exp->children[0];
    exptype = checkExp(exp, currscope);

    // these two ops can be used for all types, whereas the others
    // can only be used to compare integers
    if (op != "EQ" && op != "NE")
    {
      if (exptype != integer)
      {
        invalidParameters(exptype, integer, op, exp->line_no);
        ret = false;
      }
    }
  }

  // can't compare objects of different types
  if (exptype != retval->type())
  {
    invalidParameters(exptype, retval->type(), "comparison", exp->line_no);
    std::cerr << "\tDid you try to call expect/assert without a prior read call?\n\n";
    ret = false;
  }

  return ret;
}



/// @brief: recurses through the local ast rooted at exp and validates that 
///         the operations performed are acceptible
/// @note:  'Exp's can only have up to 2 immediate children
///
/// @return: the object type that the expression resolves to
obj_t checkExp(Node * exp, SymbolTable * currscope)
{
  if (exp == NULL)
  {
    std::cerr << "\nInvalid expression: NULL provided for expression in checkExp\n";
    return invalid;
  }

  obj_t ret = none;
  size_t children = exp->children.size();
  std::string key = exp->key;

  // binary operation i.e. + / - *
  if (children == 2)
  {
    Node * lhs = exp->children[0];
    Node * rhs = exp->children[1];

    // recursively check the left and right hand sides of the subtrees
    obj_t lhst = checkExp(lhs, currscope);
    obj_t rhst = checkExp(rhs, currscope);

    if (key != "+")
    {
      // other binary operators only apply to numeric types
      if (lhst != rhst || lhst != integer || rhst != integer)
      { 
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
    }
    else
    {
      // cannot concatenate int and can message
      if ((lhst == integer && rhst == can_msg_obj) 
          || (lhst == can_msg_obj && rhst == integer))
      {
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
      else if (lhst == str || rhst == str)
      {
        ret = str;
      }
      else
      {
        ret = invalid;
      }
    }
  }
  else if (children == 1)
  {
    Node * child = exp->children[0];
    obj_t type = checkExp(child, currscope);

    if ((exp->node_type == unary_math_node 
         || exp->node_type == binary_math_node)
        && type != integer)
    { 
      mismatched_type(type, child->line_no, key);
      return invalid;
    }
    ret = integer;
  }
  else 
  {
    // identifier or literal
    if (exp->isLiteral())
    {
      ret = exp->type;
    }
    else if (exp->isIdentifier())
    {
      Object * o = 0;
      std::string key = exp->data.strval;
      o = currscope->getObject(key);
      // check for null ptr
      if (!o)
      {
        noVariable(key, exp->line_no);
        return invalid;
      }
      ret = o->type();
    }
  }

  return ret;
} 



