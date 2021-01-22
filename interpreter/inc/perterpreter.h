#ifndef __PERTERPRETER_H__
#define __PERTERPRETER_H__

#include "object.h"
#include "strobj.h"
#include "integer.h"
#include "canmsg.h"
#include "symbol-table.h"
#include <filesystem>

// Global reserved variables
//   "SERIAL_LOG_FILE",
//   "RETVAL", 
//   "LOG_FILE", 
//   "VERBOSE",  
//   "SERIAL_DEVICE", 
//   "GPIO_DEVICE"

class Perterpreter
{
public:
  Perterpreter() {
    routines = new Routines();
    tests = new Tests();
    global_table = new SymbolTable();
    global_table->initGlobals();
  }

  virtual ~Perterpreter() {
    delete routines;
    delete tests;
    delete global_table;
  }

  void setSerialLogFile(std::string path);
  void setLogFile(std::string path);
  void setGpioDev(std::string dev);
  void setSerialDev(std::string dev);
  void setVerbose(int verb);
  void createTemplateScript(std::string spath);
  bool performSyntaxAnalysis(std::filesystem::path filepath);

  void perterpret();


private:
  Routines *routines = 0;
  Tests *tests = 0;
  SymbolTable * global_table = 0;
   
  String * serial_log_file = 0;
  String * log_file = 0;
  String * serial_device = 0;
  String * gpio_device = 0;
  Object * retval = 0;
  Integer * verbose = 0;

};



#endif