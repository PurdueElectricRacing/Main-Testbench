#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>


#include "typedefs.h"
#include <iostream>




class Node
{
public:
  std::vector<Node *> children;
  node_type_t node_type;
  std::string key;
  int line_no;
  obj_t type;

  // not using unions to minimize the necessity for pointers
  struct
  {
    std::string strval;
    int intval;
  } data;

  Node(node_type_t t, int lineno) : Node(nodeTypeToString(t), lineno){
    node_type = t;
  };
  Node(std::string *key, int lineno = 0) : Node(*key, lineno) {};
  // Constructor
  Node(std::string key = "", int lineno = 0)
  {
    this->key = key;
    node_type = generic;
    line_no = lineno;
    
    if (key == "+" || key == "-" || key == "*" || key == "/")
    {
      node_type = binary_math_node;
    }
    else if (key == "++" || key == "--")
    {
      node_type = unary_math_node;
    }
  };

  ~Node() {
    // TODO destructor lol this will be tough
    for (auto i = children.begin(); i != children.end(); i++)
    {
      delete (*i);
    }
  };

  void print(int indent = 0);
  void setString(std::string *s) {setString(*s); delete s;};
  void setString(std::string s) {type = str; data.strval = s;};
  void setInt(int i) {type = integer; data.intval = i;};
  void setCanMsg(std::string *s) {
    type = can_msg_obj; 
    data.strval = *s; 
    delete s;
  };
  void setCanMsg(std::string s) {type = can_msg_obj; data.strval = s;};
  void addChild(Node * c) {if (c) children.push_back(c);};
// virtual Node * getChild(std::string name);
  bool isLiteral() {
    return node_type == hexLiteral_node || node_type == integerLiteral_node 
           || node_type == stringLiteral_node || node_type == can_msg_node;
  }

  bool isIdentifier() { return node_type == identifier_node; };

  bool isBinaryOp() {
    return node_type == binary_math_node;
  }
  bool numChildren() { return children.size(); };
  bool numChildren(Node * node) { return node->children.size(); };
};





#endif