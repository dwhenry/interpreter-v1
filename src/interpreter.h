#ifndef _INTERGPRETER_H_
#define _INTERGPRETER_H_

#include "globals.h"
#include "scan.h"
#include <iostream>
#include <string>

class Interpreter {

public:
  Interpreter() {};
  virtual std::string process(std::string command);
};

#endif
