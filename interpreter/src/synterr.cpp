#include "synterr.h"

#include <iostream>


extern std::string infilename;
extern int errors;

/// @brief: prints a message for a binary operation performed on types which /
///         are not compatible.
void mismatched_type(obj_t lhs, obj_t rhs, int lineno, std::string op)
{
  std::cerr << "Error on line " << infilename << ":" << lineno
            << "\n\tInvalid operation: '" << op << "' cannot be performed for " 
            << objTypeToString(lhs) << " and " << objTypeToString(rhs) << "\n\n";
  errors++;
}


void invalidWriteToReadOnlyValue(std::string var, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno
            << "\n\tInvalid operation: Cannot write to read-only variable '" 
            << var << "'.\n\n";
  errors++;
}


/// @brief: prints a message for a binary operation performed on types which /
///         are not compatible.
void mismatched_type(obj_t lhs, int lineno, std::string op)
{
  std::cerr << "Error on line " << infilename << ":" << lineno
            << "\n\tInvalid operation: '" << op << "' cannot be performed for " 
            << objTypeToString(lhs) << "\n\n";
  errors++;
}

/// @brief: Display an error message about assigning a value that is not 
///         assignable to the reserved variables
void invalidGlobalOverwrite(std::string var, int lineno, obj_t otype)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n"
            << "\t'" << var << "' cannot be assigned to type '" 
            << objTypeToString(otype) << "'\n\n";
  errors++;
}


/// @brief: Display an error message about calling a routine that doesn't exist
void invalidCallType(std::string callee, Node * n)
{
  std::cerr << "Error on line " << infilename << ":" << n->line_no << "\n"
            << "\t'" << callee << "' is not a valid routine.\n\n";   
  errors++;
}


/// @brief: Error message for when multiple definitions for the same <function> 
///         name have been found.
void funcAlreadyDefined(std::string name, std::string type, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << type << " \"" << name << "\" is already defined.\n\n";
  errors++;
}

/// @brief: Error message for when multiple definitions for the same <function> 
///         name have been found.
void varAlreadyDefined(std::string name, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            "Variable \"" << name << "\" is already defined.\n\n";
  errors++;
}


/// @brief: Error message for when no function <name> was found
void funcUndefined(std::string name, std::string type, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << type << " \"" << name << "\" is undefined.\n\n";
  errors++;
}




/// @brief: Error message for when invalid parameters were passed to a command
void invalidParameters(obj_t param_type, std::string func, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "Invalid argument '" << objTypeToString(param_type) << "' for "
            "function '" << func << "'\n\n";
  errors++;
}


/// @brief: Error message for when invalid parameters were passed to a command
void invalidParameters(obj_t param_type, obj_t expect, std::string func, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "Invalid argument '" << objTypeToString(param_type) << "' for "
            "function '" << func << "'. Expected '" << objTypeToString(expect) 
            << "'\n\n";
  errors++;
}


/// @brief: Error message for when a variable is created with invalid parameters
void invalidVarDecl(obj_t exp_type, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "Cannot declare a variable with type '" 
            << objTypeToString(exp_type) << "'\n\n";
  errors++;
}


/// @brief: Error message for when a nonexistant variable is referenced
void noVariable(std::string key, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "Reference to undefined object '" << key << "' not allowed.\n\n";
  errors++;
}


/// @brief: Error message that a test is not callable
void notCallable(std::string name, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "'" << name << "' is not a callable routine.\n\n";
  errors++;
}

/// @brief: Error message that a CAN message has incorrect format
void invalidCanDecl(std::string decl, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "'" << decl << "' is not a valid CAN message format Valid"
            " formats are of the form [0-9AaBbCcDdEeFf][0-9AaBbCcDdEeFf]? "
            "(\\|[0-9AaBbCcDdEeFf][0-9AaBbCcDdEeFf]?){0,7}.\n\n";
  errors++;
}



/// @brief: called by interpreter if there is an out of bounds access to a can message
void outOfBoundsError(int len, int actual, int lineno)
{
  std::cerr << "Error on line " << infilename << ":" << lineno << "\n\t"
            << "Index " << actual << " is outside the current length boundary "
            "of " << len << ". Perhaps you need to resize your CAN frame first?\n\n";
  errors++;
}
