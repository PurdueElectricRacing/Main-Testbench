
#include <exception>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "parser.h"

#include "cxxopts.hpp"
#include "symbol-table.h"
#include "type-checker.h"
#include "perterpreter.h"

extern FILE *yyin;
extern std::string infilename;
extern Node * root;
extern int errors;



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
    return false;
  }

  // free the memory if it's already been allocated for routine list 
  // and test list
  if (routines)
    delete routines;
  if (tests)
    delete tests;

  routines = new Routines();
  tests = new Tests();
  
  if (!checkTypes(root, global_table, tests, routines))
  {
    std::cerr << errors << " errors.\n";
    return false;
  }
  return true;
}





/// @brief: setter function for the gloabl read-only variable SERIAL_LOG_FILE
void Perterpreter::setSerialLogFile(std::string path)
{
  global_table->setReadOnlyVar("SERIAL_LOG_FILE", new String(path));
}



/// @brief: setter function for the gloabl read-only variable LOG_FILE
void Perterpreter::setLogFile(std::string path)
{

  global_table->setReadOnlyVar("LOG_FILE", new String(path));
}



/// @brief: setter function for the gloabl read-only variable GPIO_DEVICE
void Perterpreter::setGpioDev(std::string dev)
{
  global_table->setReadOnlyVar("GPIO_DEVICE", new String(dev));
}



/// @brief: setter function for the gloabl read-only variable SERIAL_DEVICE
void Perterpreter::setSerialDev(std::string dev)
{
  global_table->setReadOnlyVar("SERIAL_DEVICE", new String(dev));
}



/// @brief: setter function for the gloabl read-only variable VERBOSE
void Perterpreter::setVerbose(int verb)
{
  global_table->setReadOnlyVar("VERBOSE", new Integer(verb));
}




/// @brief: This is what it's all been for. PER has it's own language now
void Perterpreter::perterpret()
{

}




// =============================================================================
#ifdef STANDALONE
int main (int argc, char ** argv)
{
  using namespace cxxopts;

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
  

  // TODO support the other command line options
  if (!device.empty())
  {

  }

  if (!io.empty())
  {

  }

  if (!logfile.empty())
  {

  }

  if (!toutfile.empty())
  {

  }
}
catch (std::exception& e)
{
  std::cout << e.what() << "\n";
}
  
}
#endif