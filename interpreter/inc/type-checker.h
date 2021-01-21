#ifndef __CHECK_SYNTAX_H__
#define __CHECK_SYNTAX_H__

#include "ast.h"
#include "symbol-table.h"

obj_t checkSingleParamCmd(Node * node);
obj_t checkExp(Node * exp);
obj_t checkVardecl(Node * node);
bool checkIntegralArg(Node * node);
bool checkPinWrite(Node * node);
bool checkSendMsg(Node * node);
bool checkReadMsg(Node * node);
bool checkExpectAssert(Node * root);
bool checkTypes(Node * root, Tests *tests, Routines *routines);

#endif