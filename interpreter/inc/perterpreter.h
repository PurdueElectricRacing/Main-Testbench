#ifndef __PERTERPRETER_H__
#define __PERTERPRETER_H__

#include "object.h"
#include "strobj.h"
#include "integer.h"
#include "canmsg.h"
#include "symbol-table.h"
#include <filesystem>

#include <iostream>
#include <fstream>

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
  Node * _root = 0;
  Perterpreter() {
    routines = new Routines();
    tests = new Tests();
    global_table = new SymbolTable();
    global_table->initGlobals();
  }

  virtual ~Perterpreter() {
    delete global_table;
    delete routines;
    delete tests;
    if (!_root)
    {
      delete _root;
    }
  }

  void setSerialLogFile(std::string path) {serial_log_file = path;};
  void setLogFile(std::string path) {log_file = path;};
  void setGpioDev(std::string dev) {gpio_device = dev;};
  void setSerialDev(std::string dev) {serial_device = dev;};
  void setVerbose(int verb) {verbose = verb;};
  void createTemplateScript(std::string spath);
  bool performSyntaxAnalysis(std::filesystem::path filepath);

  void perterpret(std::string func="");


  std::vector<std::string> listSerialDevices();

  // TODO stream operator for writing to files and console without boost

private:

  void perterpretVardecl(Node * node, SymbolTable * scope);
  void perterpretCall(Node * node, SymbolTable * scope);
  void perterpretDelay(Node * node, SymbolTable * scope);
  void perterpretLoop(Node * node, SymbolTable * scope);
  void perterpretExpectAssert(Node * node, SymbolTable * scope);
  void perterpretPrint(Node * node, SymbolTable * scope);
  void perterpretSerialTx(Node * node, SymbolTable * scope);
  void perterpretSerialRx(Node * node, SymbolTable * scope);
  void perterpretPrompt(Node * node, SymbolTable * scope);
  void perterpretDRead(Node * node, SymbolTable * scope);
  void perterpretDWrite(Node * node, SymbolTable * scope);
  void perterpretAread(Node * node, SymbolTable * scope);
  void perterpretAwrite(Node * node, SymbolTable * scope);
  void perterpretSendMsg(Node * node, SymbolTable * scope);
  void perterpretReadMsg(Node * node, SymbolTable * scope);
  void perterpretNode(Node * node, SymbolTable * scope);
  void perterpretIf(Node * node, SymbolTable * scope);
  
  Object * perterpretExp(Node * node, SymbolTable * scope);
  Object * perterpretBinaryOp(Node * node, SymbolTable * scope);
  Object * getObject(Node * node, SymbolTable * scope);


  Routines *routines = 0;
  Tests *tests = 0;
  SymbolTable * global_table = 0;
   
  std::string serial_log_file;
  std::string log_file;
  std::string serial_device;
  std::string gpio_device;
  bool verbose = false;
  Object * retval = 0;

};



#endif