#ifndef _INTERGPRETER_H_
#define _INTERGPRETER_H_

#include "globals.h"
#include "scan.h"
#include <iostream>
#include <string>

class Interpreter {
  Scan * scanner;
  TokenDetails * nextToken;
  void eat(TokenType::TOKENS tokenType);
  void error(std::string msg);
  int exp();
  int term();
  int factor();

public:
  Interpreter() {}
  virtual std::string process(std::string command);
};

#endif
