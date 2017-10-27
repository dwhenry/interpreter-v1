#ifndef _AST_H_
#define _AST_H_

#include "globals.h"
#include <iostream>

class AST {
public:
  virtual void accept(class Visiter &i) = 0;

};

class BinAST : public AST {
public:
  AST * left;
  TokenType::TOKENS op;
  AST * right;
  BinAST(AST * left, TokenType::TOKENS op, AST * right);
  void accept(Visiter &i);
};

class NumAST : public AST {
public:
  int value;
  NumAST(int value);
  void accept(Visiter &i);
};

#endif
