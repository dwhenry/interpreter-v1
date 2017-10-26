#ifndef _AST_H_
#define _AST_H_

#include "globals.h"
#include <iostream>

class AST {};

class BinAST : public AST {
public:
  AST * left;
  TokenType::TOKENS op;
  AST * right;
  BinAST(AST * left, TokenType::TOKENS op, AST * right) {
    this->left = left;
    this->op = op;
    this->right = right;
  }
};

class NumAST : public AST {
public:
  int value;
  NumAST(int value) {
    this->value = value;
  }
};

#endif
