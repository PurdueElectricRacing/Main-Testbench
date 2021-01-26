#ifndef __SYNTAX_ERROR_H__
#define __SYNTAX_ERROR_H__

#include "typedefs.h"
#include "ast.h"

void mismatched_type(obj_t lhs, obj_t rhs, int lineno, std::string op = "");
void mismatched_type(obj_t lhs, int lineno, std::string op = "");
void invalidCallType(std::string callee, Node * n);
void funcAlreadyDefined(std::string name, std::string type, int lineno);
void funcUndefined(std::string name, std::string type, int lineno);
void invalidParameters(obj_t param_type, std::string func, int lineno);
void invalidParameters(obj_t param_type, obj_t expect, std::string func, int lineno);
void invalidVarDecl(obj_t exp_type, int lineno);
void noVariable(std::string key, int lineno);
void notCallable(std::string name, int lineno);
void invalidCanDecl(std::string decl, int lineno);
void varAlreadyDefined(std::string name, int lineno);
void invalidGlobalOverwrite(std::string var, int lineno, obj_t otype);
void invalidWriteToReadOnlyValue(std::string var, int lineno = -1);
void outOfBoundsError(int len, int actual, int lineno);

#endif