#ifndef __LOL_IDK_MAN_H__
#define __LOL_IDK_MAN_H__

#include <string>

// enum for determining an object's data type
enum obj_t
{
  none,
  str,
  integer,
  can_msg_obj,
  invalid,
  boolean,
};


enum node_type_t
{
  analog_read,
  analog_write,
  digital_read,
  digital_write,
  send_msg_node,
  read_msg_node,
  serial_tx,
  serial_rx,
  print,
  println,
  prompt_node,
  expect_node,
  assert_node,
  delay_node,
  loop_node,
  generic,
  statement_list,
  routine_node,
  test_node,
  stringLiteral_node,
  integerLiteral_node,
  hexLiteral_node,
  identifier_node,
  binary_math_node,
  unary_math_node,
  comparison_node,
  and_node,
  or_node,
  forever_node,
  call_node,
  exit_node,
  test_list_node,
  routine_list_node,
  can_msg_node,
  vardecl_node,
  vardecl_list_node,
  if_node,
  else_node,
  index_node,
  length_node,
  empty_node,
};


std::string nodeTypeToString(node_type_t t);

std::string objTypeToString(obj_t t);

#endif