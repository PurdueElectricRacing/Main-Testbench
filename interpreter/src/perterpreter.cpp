
#include "parser.h"

#include "cxxopts.hpp"
#include "symbol-table.h"
#include "type-checker.h"
#include "perterpreter.h"
#include "operators.h"
#include "object-factory.h"

#include <exception>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <memory>

extern FILE *yyin;
extern std::string infilename;
extern Node * root;
extern int errors;


// used for pseudo garbage collection of the intermediate Object * created
// during evaluations
std::set<Object *> intermediate_operands;
bool halt_execution = false;


/// @brief: private helper function for clearing any intermediate operands 
///         constructed during expression evaluation. It's a good idea to call 
///         this at the end of all the functions in case something in the 
///         call-stack allocates a new object and forgets to delete it.
void clearIntermediateOps(SymbolTable * scope)
{
  for (auto op = intermediate_operands.begin(); 
       op != intermediate_operands.end();
       op++)
  {
    Object * operand = *op;
    if (!scope->find(operand))
    {
      delete operand;
    }
  }
  intermediate_operands.clear();
}



/// @brief: Function that gets called when the user specifies the -g, 
///         --generate-template parameter in command line or uses that 
///         functionality of the GUI
void Perterpreter::createTemplateScript(std::string spath)
{
  using namespace std::filesystem;
  path p = canonical(path(spath));
  
  if (is_directory(p))
  {
    p /= "example.pers";  
  }

  std::cout << "Creating sample file at " << p << "\n";

  // make sure the file extension is appended
  if (p.extension() != ".pers")
  {
    p += ".pers";
  }

  std::ofstream tgt(p.c_str(), std::ofstream::out);

  tgt << "// BEGIN GLOBAL VARIABLE INITIALIZATIONS\n"
         "// ========================================\n"
         "\n\n# This is where you create or modify any global variables\n\n"
         "// ========================================\n"
         "// END GLOBAL VARIABLE INITIALIZATIONS\n"

         "\n// BEGIN ROUTINE DECLARATIONS\n"
         "// ========================================\n"
         "routine \"routine name\" {\n  perrintln \"Howdy friends.\";\n}\n\n"
         "// ========================================\n"
         "// END ROUTINE DECLARATIONS\n"

         "\n// BEGIN TEST DECLARATIONS\n"
         "// ========================================\n"
         "test \"test name\" {\n  assert EQ 1;\n}\n\n"
         "// ========================================\n"
         "// END TEST DECLARATIONS\n"
         ;
  tgt.close();
}



/// @brief: Perform the lexical analysis/parsing and type checking only
/// @return: true on valid syntax, false on error
bool Perterpreter::performSyntaxAnalysis(std::filesystem::path filepath)
{
  infilename = filepath.c_str();
  yyin = fopen(filepath.c_str(), "r");
  extern int yydebug;

#ifdef DEBUG
  yydebug = 1;
#endif
  if (yyparse() != 0 || errors > 0)
  {
    std::cerr << "Failed to parse.\n";
    std::cerr << errors << " errors.\n";
    _root = root;
    return false;
  }
  _root = root;

  // free the memory if it's already been allocated for routine list 
  // and test list
  if (routines)
    delete routines;
  if (tests)
    delete tests;

  routines = new Routines();
  tests = new Tests();
  checkTypes(root, global_table, tests, routines);
  if (errors > 0)
  {
    std::cerr << errors << " errors.\n";
    return false;
  }
  return true;
}




/// @brief: Wrapper for symbol table getObject function; Will return CAN 
///         message indexes and lengths as well as base objects.
///         Adds any new objects to the intermediate_ops vector
Object * Perterpreter::getObject(Node * node, SymbolTable * scope)
{
  Object * ret = 0;

  if (node->isIdentifier())
  {
    ret = scope->getObject(node->data.strval);
    // accessing a member of the object
    if (node->children.size() > 0)
    {
      Node * exp = node->children[0];
      CAN_Msg * msg = static_cast<CAN_Msg*>(ret);

      if (exp->node_type == length_node)
      {
        ret = new Integer(msg->length());
        intermediate_operands.emplace(ret);
      }
      else if (exp->node_type == index_node)
      {
        // fetch the value at provided index
        ret =  perterpretExp(exp->children[0], scope);
        intermediate_operands.emplace(ret);
      }
    }
  }
  else if (node->isLiteral())
  {
    ret = ObjectFactory::createObject(node);
    intermediate_operands.emplace(ret);
  }
  else if (node->node_type == unary_math_node)
  {
    ret = perterpretExp(node, scope);
  }
  return ret;
}





void Perterpreter::perterpretExpectAssert(Node * node, SymbolTable * scope)
{
  Node * exp = node->children[0];
  Object * expectation = perterpretExp(exp, scope);
  Integer * i = static_cast<Integer *>(expectation);

  if (!i->value)
  {
    printf("Expectation unsatisified on line %d\n", node->line_no);
    // mark the test as failed
    if (scope->type() == test_table)
    {
      Test * t = static_cast<Test *>(scope);
      t->failTest();
    }
  }

  // kill the current execution
  if (node->node_type == assert_node)
  {
    // TODO assertion nodes
    halt_execution = true;
  }
}



/// @brief: Performs a binary expression evaluation
///         adds any newly created objects to the intermediate_ops vector
Object * Perterpreter::perterpretBinaryOp(Node * node, SymbolTable * scope)
{
  Node * lhs = node->children[0];
  Node * rhs = node->children[1];

  Object * ret = 0;
  Object * rhso = 0;
  Object * lhso = 0;

  lhso = perterpretExp(lhs, scope);
  rhso = perterpretExp(rhs, scope);

  if (node->node_type == comparison_node)
  {
    ret = new Integer(compare(lhso, rhso, node->data.strval));
    intermediate_operands.emplace(ret);
  }
  // concatenating a string
  else if (lhso->type() == str || rhso->type() == str)
  {
    ret = new String(concat(lhso, rhso));
    intermediate_operands.emplace(ret);
  }
  // math operation
  else
  {
    ret = new Integer(math(lhso, rhso, node->data.strval));
    intermediate_operands.emplace(ret);
  }

  return ret;
}



/// @brief: Interpret any arbitrary expression. Will push new objects to the 
///         intermediate ops vector
Object * Perterpreter::perterpretExp(Node * node, SymbolTable * scope)
{
  Object * ret = 0;
  // binary operator  
  if (node->children.size() == 2)
  {
    ret = perterpretBinaryOp(node, scope);
  }
  else if (node->isLiteral())
  {
    Object * o = ObjectFactory::createObject(node);
    intermediate_operands.emplace(o);
    return o;
  }
  else if (node->isIdentifier())
  {
    return getObject(node, scope);
  }
  else if (node->node_type == unary_math_node)
  {
    Object * o = getObject(node->children[0], scope);
    Integer * i = new Integer(unaryMath(o, node->data.strval));
    intermediate_operands.emplace(i);
    ret = i;
  }
  
  return ret;
}




/// @brief: perform a delay call
void Perterpreter::perterpretDelay(Node * node, SymbolTable * scope)
{
  Node * delay = node->children[0];
  size_t delayval = 0;

  if (delay->isLiteral())
  {
    delayval = delay->data.intval;
  }
  else
  {
    Integer * i = static_cast<Integer *>
                  (perterpretExp(node->children[0], scope));
    delayval = i->value;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(delayval));
}




/// @brief: returns vector of serial devices currently accessible
std::vector<std::string> Perterpreter::listSerialDevices()
{

}




/// @brief: perform a variable assignment / reassignment
void Perterpreter::perterpretVardecl(Node * node, SymbolTable * scope)
{
  // fetch the object being assigned to
  Node * rhs = node->children[0];
  Object * lhso = scope->getObject(node->data.strval);
  Object * rhso = perterpretExp(rhs, scope);

  // length or index node too
  if (node->children.size() > 1 && lhso->type() == can_msg_obj)
  {
    CAN_Msg * can = static_cast<CAN_Msg *>(lhso);

    // second child is always the access modifier
    Node * exp = node->children[1];
    Integer * target_val = static_cast<Integer *>(rhso);

    if (exp->node_type == index_node)
    {
      Node * idx = exp->children[0];
      Integer * val = static_cast<Integer *>(perterpretExp(idx, scope));

      if (can->setData(val->value, target_val->value) != target_val->value)
      {
        outOfBoundsError(can->length(), val->value, node->line_no);
      }
    }
    else if (exp->node_type == length_node)
    {
      can->setLeng(target_val->value);
    }
  }
  else
  {
    scope->setObject(node->data.strval, rhso);
  }

  clearIntermediateOps(scope);
}




/// @brief: performs a print / println
void Perterpreter::perterpretPrint(Node * node, SymbolTable * scope)
{
  Node * exp = node->children[0];
  Object * output = perterpretExp(exp, scope);

  printf("%s", output->stringify().c_str());

  if (node->node_type == println)
  {
    std::cout << std::endl;
  }

  clearIntermediateOps(scope);
}




/// @brief: perform a prompt blocking call, and interpret the expression arg
///         and print it to stdout. Blocks until user presses enter
void Perterpreter::perterpretPrompt(Node * node, SymbolTable * scope)
{
  Node * exp = node->children[0];
  Object * value = perterpretExp(exp, scope);
  std::string whatever;

  printf("%s\n", value->stringify().c_str());
  clearIntermediateOps(scope);
  printf("Press enter to continue...\n");

  std::getline(std::cin, whatever);
}




/// @brief: Interpret an if or if/else block
void Perterpreter::perterpretIf(Node * node, SymbolTable * scope)
{
  Node * exp = node->children[0];
  Node * statements = node->children[1];
  Node * elsenode = 0;
  Node * else_statements;

  Object * value = perterpretExp(exp, scope);
  Integer * i = static_cast<Integer *>(value);

  if (i->value)
  {
    perterpretNode(statements, scope);
  }
  else
  {
    // if there is an else clause perform that 
    if ((elsenode = node->getChild(else_node)))
    {
      else_statements = elsenode->children[0];
      perterpretNode(else_statements, scope);
    }
  }

  clearIntermediateOps(scope);
}




void Perterpreter::perterpretCall(Node * node, SymbolTable * scope)
{
  // the routine name has to be the next argument and it has to be a literal
  std::string routine_name = node->data.strval;
  Routine * r = routines->getRoutine(routine_name, node->line_no);
  perterpretNode(r->getRoot(), r);

  clearIntermediateOps(scope);
}




/// @brief: Execute the loops
void Perterpreter::perterpretLoop(Node * node, SymbolTable * scope)
{
  Node * exp = node->children[0];
  Node * statements = node->children[1];

  if (exp->node_type == forever_node)
  {
    while(PER == GREAT)
    {
      perterpretNode(statements, scope);
    }
    return;
  }
  else
  {
    Integer * i = static_cast<Integer *>(perterpretExp(exp, scope));

    while (i->value)
    {
      perterpretNode(statements, scope);
      i = static_cast<Integer *>(perterpretExp(exp, scope));
    }
  }  
  clearIntermediateOps(scope);
}




/// @brief: Dispatcher for interpreting list nodes. Calling this with a 
///         non-list node will result in undefined behavior.
void Perterpreter::perterpretNode(Node * node, SymbolTable * scope)
{
  for (auto n = node->children.begin(); n != node->children.end(),
       !halt_execution; n++)
  {
    Node * child = *n;
    node_type_t nodetype = child->node_type;

    // recurse on the list nodes
    switch (nodetype)
    {
      case (vardecl_list_node):
      case (statement_list):
      {
        perterpretNode(child, scope);
        break;
      }
      case (unary_math_node):
        perterpretExp(child, scope);
        break;
      case (vardecl_node):
        perterpretVardecl(child, scope);
        break;
      case (call_node):
        perterpretCall(child, scope);
        break;
      case (delay_node):
        perterpretDelay(child, scope);
        break;
      case (loop_node):
        perterpretLoop(child, scope);
        break;
      case (expect_node):
      case (assert_node):
        perterpretExpectAssert(child, scope);
        break;
      case (print):
      case (println):
        perterpretPrint(child, scope);
        break;
      case (exit_node):
        // TODO exit code
        break;
      case (serial_tx):
        break;
      case (serial_rx):
        break;
      case (prompt_node):
        perterpretPrompt(child, scope);
        break;
      case (digital_read):
        break;
      case (digital_write):
        break;
      case (analog_read):
        break;
      case (analog_write):
        break;
      case (send_msg_node):
        break;
      case (read_msg_node):
        break;
      case (if_node):
        perterpretIf(child, scope);
        break;
      default:
        break;
    }
  
  }
}



/// @brief: This is what it's all been for. PER has it's own language now
void Perterpreter::perterpret(std::string func)
{
  if (func.empty())
  {
    // interpret all the tests only
    for (auto t = tests->tests.begin(); t != tests->tests.end(); t++)
    {
      Test * test = t->second; 
      perterpretNode(test->root, test);
      halt_execution = false;

      if (test->testPassed())
      {
        // TODO output that test is passed
      }
      else 
      {
        // TODO output that test is failed
      }

      // TODO color output conditionally 
    }
  }
  else if (tests->hasTest(func))
  {
    Test * test = tests->getTest(func);
    perterpretNode(test->root, test);
  }
  else if (routines->hasRoutine(func))
  {
    Routine * r = routines->getRoutine(func);
    perterpretNode(r->root, r);
  }
}




// =============================================================================
#ifdef STANDALONE
int main (int argc, char ** argv)
{
  using namespace cxxopts;
  std::ofstream f;
  f << "poop";

  Perterpreter p;
  
  std::string infile, device, io, logfile, toutfile, sdest;
  std::vector<std::string> routines_to_run, tests_to_run;

  bool verbose = false, syntax_check = false;
  bool good_syntax = false;
try
{
  Options options("perterpreter", "Interpreter for the PER automated" 
                                  "testing / scripting language");

  options.custom_help("filename [(-V, --validate} | (-rt, --run-tests testlist) | (-rr, --run-routines routinelist)] | -g dest [OPTIONS...]");

  options.positional_help("");

  options.add_options("Options")
    ("d,device", 
     "Name of the serial device for generic serial Tx/Rx.",
     value<std::string>(device))
    
    ("io", 
     "Name of the serial device controlling GPIO.",
     value<std::string>(io))
    
    ("v,verbose", 
     "Enable verbose printing of all script commands",
     value<bool>(verbose))
    
    ("h,help", "Print help message")
    
    ("l,log", 
     "Filepath to use as the log file.", 
     value<std::string>(logfile))

    ("t,test-output", 
     "Filename where test output should be logged", 
      value<std::string>(toutfile))

    ("infile", 
     "Filename for script file to run.", 
     value<std::string>(infile))

    ("g,generate-sample", 
     "Create a sample .pers file and put it in <dest>.", 
     value<std::string>(sdest))

    ("V,validate-syntax", "if this switch is passed, the interpreter will not" 
                          "execute. It will instead only perform syntax parsing"
                          " and type checking. This is useful for checking "
                          "scripts before actually running them if you don't "
                          "want to run them.", value<bool>(syntax_check))

    ("T,run-tests", "This is a comma-separated list of tests to run if you "
                     "don't want to run all of them. Default is to run all "
                     "tests. Example: '-T \"test 1\",\"test 2\". Ensure no "
                     "spaces between values. Optionally, you can pass this "
                     "parameter multiple times with each test name being the "
                     "subsequent parameter e.g. -T \"test 1\" -T \" test 2\"."
                     "The order specified will be the order scripts are run in",
                     value<std::vector<std::string> >(tests_to_run))

    ("R,run-routines", "This is a comma-separated list of routines to run if "
                        "you want to run any of them. Default behavior is to "
                        "not run any. See -T for examples, as the syntax is "
                        "the same. The order specified will be the order scripts are run in", 
                        value<std::vector<std::string> >(routines_to_run))
    ;
  
  options.parse_positional({"infile"});
  auto cmdline = options.parse(argc, argv);

  if (cmdline.count("help"))
  {
    std::cout << options.help({"", "Options"}) << "\n";
    exit(0);
  }

  // -g command provided
  if (cmdline.count("g"))
  {
    if (!sdest.empty())
    {
      p.createTemplateScript(sdest);
      exit(0);
    }
    else
    {
      std::cerr << "No destination provided for -g switch";
      exit(-1);
    }
  }

  // TODO routines to run and tests to run
  
  if (infile.empty())
  {
    std::cerr << "No input file specified.\n";
    std::cout << options.help({"", "Options"}) << "\n";
    exit(-1);
  }

  // print a passive-aggressive message about file extension
  if (infile.find(".pers") == std::string::npos)
  {
    std::cerr << "Invalid file extension. You seem to have forgotten the "
                  "'.pers' extension.\n";
    exit(-1);
  }

  if (!std::filesystem::exists(infile))
  {
    std::cerr << "File not found \"" << infile << "\"\n";
    exit(-1);
  }

  // this is a global variable that the error printer uses.
  good_syntax = p.performSyntaxAnalysis(infile);
  
  // terminate if this switch was passed
  if (syntax_check)
  {
    return good_syntax;
  }
  
  if (!good_syntax)
  {
    exit(-1);
  }

  // TODO support the other command line options
  if (!device.empty())
  {
    p.setSerialDev(device);
  }

  if (!io.empty())
  {
    p.setGpioDev(io);
  }

  if (!logfile.empty())
  {
    p.setLogFile(logfile);
  }

  if (!toutfile.empty())
  {
  }
  p.perterpret();
}
catch (std::exception& e)
{
  std::cout << e.what() << "\n";
}
  
}
#endif