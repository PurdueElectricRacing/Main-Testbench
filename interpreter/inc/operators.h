#ifndef __OPERATORS_H__
#define __OPERATORS_H__

#include "object.h"
#include "ast.h"

std::string concat(Object * lhs, Object * rhs);
std::string concat(Node * lhs, Object * rhs);
std::string concat(Node * lhs, Node * rhs);
std::string concat(Object * lhs, Node * rhs);

int math(Object * lhs, Object * rhs, std::string op);
int math(Object * lhs, Node * rhs, std::string op);
int math(Node * lhs, Object * rhs, std::string op);
int math(Node * lhs, Node * rhs, std::string op);

int unaryMath(Object * o, std::string op);
int unaryMath(Node * o, std::string op);
int unaryMath(int o, std::string op);


bool compare(Object * lhs, Object * rhs, std::string op);
bool compare(Object * lhs, Node * rhs, std::string op);
bool compare(Node * lhs, Object * rhs, std::string op);
bool compare(Node * lhs, Node * rhs, std::string op);

#endif