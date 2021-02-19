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
      checkVardecl(node, currscope);
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
      // TODO fix sendMsg to check for CAN msg
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
    else if (type == if_node)
    {
      checkIfElse(node, currscope, tests, routines);
    }
    // these commands take 1 integral argument 
    //(can be in the form of an expressions
    else if (type == delay_node)
    {
      checkIntegralArg(node, currscope);
    }
    else if (type == loop_node)
    {
      obj_t param = checkSingleParamCmd(node, currscope);
      if (param != boolean && param != integer)
      {
        invalidParameters(param, nodeTypeToString(node->node_type), 
                          node->line_no);
      }
      checkTypes(node, currscope, tests, routines);
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
  return true;
}



/// @brief: check the parameters for if expression
///
/// @return: true if valid parameters, false if
bool checkIfElse(Node * node, SymbolTable * currscope, Tests *tests, Routines *routines)
{
  Node * elsenode = node->getChild(else_node);
  Node * statements = node->children[1];
  // the expression is the first child
  obj_t exptype = checkExp(node->children[0], currscope); 
  bool ret = true;
  
  // can't have non-boolean types as conditions
  if (exptype != boolean && exptype != integer && exptype != invalid)
  {
    mismatched_type(exptype, boolean, node->line_no, "if");
    return false;
  }
  ret = checkTypes(statements, currscope, tests, routines);

  // else isn't a required parameter
  if (elsenode != NULL)
  {
    ret = checkTypes(elsenode->children[0], currscope, tests, routines);
  }

  return ret;
}



/// @brief: check the parameters for a pin write, must be <integer> <integer>
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
    ret = false;
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
/// @return: the variables object type or invalid on error
obj_t checkVardecl(Node * node, SymbolTable * currscope) 
{
  Node * exp = node->children[0];
  Node * member_access = 0;
  obj_t exptype = checkExp(exp, currscope);
  std::string varname = node->data.strval;
  Object * o = 0;

  if (exptype == invalid)
  {
    invalidVarDecl(exptype, node->line_no);
  }

  o = currscope->getObject(varname);

  // if there are children it must be a can object
  if ((member_access = node->getChild(length_node)) 
      || (member_access = node->getChild(index_node)))
  {
    // can't modify parameters for a just created object
    if (o == NULL)
    {
      noVariable(varname, node->line_no);
      return invalid;
    }

    if (o->type() != can_msg_obj)
    {
      invalidParameters(o->type(), can_msg_obj, member_access->data.strval,
                        node->line_no);
      return invalid;
    }
    exptype = integer;
  }
  else
  {
    currscope->setObject(varname, ObjectFactory::createObject(exp, exptype));
  }
  return exptype;
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
  exptype = checkExp(exp, currscope);

  if (exptype != boolean)
  {
    invalidParameters(exptype, boolean, node->data.strval, exp->line_no);
    return false;
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
  node_type_t nodetype = exp->node_type;
  std::string key = exp->data.strval;

  // binary operation i.e. + / - * or comparisons / conjunctions
  if (children == 2)
  {
    Node * lhs = exp->children[0];
    Node * rhs = exp->children[1];

    // recursively check the left and right hand sides of the subtrees
    obj_t lhst = checkExp(lhs, currscope);
    obj_t rhst = checkExp(rhs, currscope);

    // logical conjunctions    
    if (nodetype == and_node || nodetype == or_node)
    {
      if (lhst != rhst)
      {
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
    }
    else if (nodetype == comparison_node)
    {
      if (lhst != rhst)
      {
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
      // cannot use other comparisons for non integerals
      if (key != "EQ" && key != "NE"
          && (rhst != integer || lhst != integer))
      {
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
      ret = boolean;
    }
    else if (key == "+")
    {
      // concatenate a string and something else
      if (lhst == str || rhst == str)
      {
        ret = str;
      }
      else if (lhst != integer || rhst != integer)
      {
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
      else
      {
        ret = lhst;
      }
    }
    // some other math node 
    else 
    {
      if (lhst != integer || rhst != integer)
      {
        mismatched_type(lhst, rhst, lhs->line_no, key);
        return invalid;
      }
      ret = lhst;
    }
  }
  else if (children == 1 && !exp->isLiteral() && !exp->isIdentifier())
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
    ret = type;
  }
  // variable or literal node
  else 
  {
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
      
      // check if there is [] or 'length'
      // both operators return integers
      if (exp->children.size() > 0)
      {
        Node * child = exp->children[0];
        obj_t exptype = none;

        if (child->node_type == index_node)
        {
          // cannot use [] on non-can message types
          if (ret != can_msg_obj)
          {
            mismatched_type(ret, child->line_no, "[]");
            return invalid;
          }
          child = child->children[0];
          exptype = checkExp(child, currscope);

          // error if the index expression is not an integer
          if (exptype != integer)
          {
            mismatched_type(ret, exptype,child->line_no, "[]");
            return invalid;
          } 
        }
        // likewise, length can only be manipulated on CAN messages
        else if (child->node_type == length_node && ret != can_msg_obj)
        {
          mismatched_type(ret, child->line_no, "length");
          return invalid;
        }
        ret = integer;
      }
    }
  }

  return ret;
} 



