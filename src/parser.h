#ifndef _INTERGPRETER_H_
#define _INTERGPRETER_H_

#include "globals.h"
#include "ast.h"
#include "visitor.h"
#include "scan.h"
#include <iostream>
#include <string>

class Parser {
  Scan * scanner;
  TokenDetails * nextToken;
  void eat(TokenType::TOKENS tokenType);
  void error(std::string msg);
  AST * exp();
  AST * term();
  AST * factor();

public:
  Parser() {}
  virtual std::string process(std::string command);
};

#endif
