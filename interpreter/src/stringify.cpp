#include "typedefs.h"
#include "ast.h"
#include "canmsg.h"
#include <string>
#include <sstream>
#include <iomanip>


/// @brief: gets the string value of a literal node. Cannot be used on non-literals
std::string stringifyNode(Node * node)
{
  if (node->node_type == integerLiteral_node)
  {
    return std::to_string(node->data.intval);
  }
  else if (node->node_type == hexLiteral_node)
  {
    std::stringstream ss;
    ss << std::hex << node->data.intval;
    return std::string("0x") + ss.str();
  }
  else if (node->node_type == can_msg_node)
  {
    return node->data.strval;
  }
  else if (node->node_type == stringLiteral_node)
  {
    return node->data.strval;
  }
  return "";
}



std::string objTypeToString(obj_t t)
{
  switch (t)
  {
    case (none):
      return "None";
    case (str):
      return "String";
    case (integer):
      return "Integer";
    case(can_msg_obj):
      return "CAN Message";
    case(boolean):
      return "boolean";
    default:
      return "Invalid";
  }
}



std::string nodeTypeToString(node_type_t t)
{
  switch (t)
  {
    case (analog_read):
      return "read-pin AIN";
    case (analog_write):
      return "set-pin AOUT";
    case (digital_read):
      return "read-pin DIN";
    case (digital_write):
      return "set-pin DOUT";
    case (send_msg_node):
      return "send-msg";
    case (read_msg_node):
      return "read-msg";
    case (serial_rx):
      return "serial-rx";
    case (serial_tx):
      return "serial-tx";
    case (print):
      return "print";
    case (println):
      return "println";
    case (prompt_node):
      return "prompt";
    case (expect_node):
      return "expect";
    case (assert_node):
      return "assert";
    case (delay_node):
      return "delay";
    case (loop_node):
      return "loop";
    case (generic):
      return "generic";
    case (routine_node):
      return "routine";
    case (test_node):
      return "test";
    case (stringLiteral_node):
      return "String Literal";
    case (integerLiteral_node):
      return "Integer Literal";
    case (hexLiteral_node):
      return "Hex Literal";
    case (identifier_node):
      return "Identifier";
    case (binary_math_node):
      return "Binary math operator";
    case (unary_math_node):
      return "Unary math operator";
    case (comparison_node):
      return "Comparison";
    case (and_node):
      return "and";
    case (or_node):
      return "or";
    case (forever_node):
      return "forever";
    case (call_node):
      return "call";
    case (exit_node):
      return "exit";
    case (test_list_node):
      return "TestList";
    case (routine_list_node):
      return "RoutineList";
    case (can_msg_node):
      return "CAN Msg";
    case (vardecl_list_node):
      return "Variable Declaration List";
    case (vardecl_node):
      return "Variable Declaration / assignment";
    case (statement_list):
      return "StatementList";
    case (if_node):
      return "if";
    case (else_node):
      return "else";
    case (index_node):
      return "CAN Message Index";
    case(length_node):
      return "length";
    default:
      return "Unknown";
  }
}
