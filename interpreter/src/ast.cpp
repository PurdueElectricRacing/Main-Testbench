#include "ast.h"

#define INDENT(i) std::string(indent, ' ')


/// @brief: Prints an AST node to stdout in a formatted way
void Node::print(int indent)
{
  using namespace std;
  cout << INDENT(indent) << "Key: " << key << "\n"
       << INDENT(indent) << "Type: " << objTypeToString(type) << "\n"
       << INDENT(indent) << "Value: ";

  if (type == str || type == can_msg_obj) 
  {
    cout <<  data.strval;
  }
  else if (type == integer)
  {
    cout <<  data.intval;
  }
  else
  {
    cout <<  "Undefined.";
  }
  cout << "\n";

  cout << INDENT(indent) << "Line number: " << to_string(line_no) << "\n"
       << INDENT(indent) << "Children: " << children.size() << "\n"
       << INDENT(indent) << indent
       << "\n===============================================\n";

  for (auto itr = children.begin(); itr != children.end(); ++itr)
  {
    if (*itr != NULL)
    {
      (*itr)->print(indent + 4);
    }
  }
}