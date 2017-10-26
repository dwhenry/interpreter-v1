#ifndef _INTERGPRETER_H_
#define _INTERGPRETER_H_

#include "globals.h"
#include "ast.h"
#include "scan.h"
#include <iostream>
#include <string>

class Interpreter {
  Scan * scanner;
  TokenDetails * nextToken;
  void eat(TokenType::TOKENS tokenType);
  void error(std::string msg);
  AST * exp();
  AST * term();
  AST * factor();

  int visit(AST * node);
  int visit(BinAST * node);
  int visit(NumAST * node);

public:
  Interpreter() {}
  virtual std::string process(std::string command);
};

#endif
