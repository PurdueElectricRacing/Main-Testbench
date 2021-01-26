#ifndef __CHECK_SYNTAX_H__
#define __CHECK_SYNTAX_H__

#include "ast.h"
#include "symbol-table.h"

obj_t checkSingleParamCmd(Node * node, SymbolTable * currscope);
obj_t checkExp(Node * exp, SymbolTable * currscope);
obj_t checkVardecl(Node * node, SymbolTable * currscope);
bool checkIntegralArg(Node * node, SymbolTable * currscope);
bool checkPinWrite(Node * node, SymbolTable * currscope);
bool checkSendMsg(Node * node, SymbolTable * currscope);
bool checkReadMsg(Node * node, SymbolTable * currscope);
bool checkExpectAssert(Node * root, SymbolTable * currscope);
bool checkIfElse(Node * node, SymbolTable * currscope, Tests *tests, Routines *routines);
bool checkTypes(Node * root, SymbolTable * currscope, Tests *tests, Routines *routines);

#endif