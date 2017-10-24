#ifndef _INTERGPRETER_H_
#define _INTERGPRETER_H_

#include <string>

class Interpreter {

public:
  Interpreter() {};
  virtual std::string * process(std::string command);
};

#endif
