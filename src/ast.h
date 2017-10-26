#ifndef _AST_H_
#define _AST_H_

#include "globals.h"
#include <iostream>

class AST {
public:
  virtual int visit() {
    throw "Call to virtualk funxtion: AST.visit";
  }
};

class BinAST : public AST {
  AST * left;
  TokenType::TOKENS op;
  AST * right;

public:
  BinAST(AST * left, TokenType::TOKENS op, AST * right) {
    this->left = left;
    this->op = op;
    this->right = right;
  };
  int visit() {
    switch(this->op) {
    case TokenType::PLUS:
      return left->visit() + right->visit();
    case TokenType::MINUS:
      return left->visit() - right->visit();
    case TokenType::TIMES:
      return left->visit() * right->visit();
    case TokenType::DIVIDE:
      return left->visit() / right->visit();
    default:
      throw "Umnexpected";
    }
  };
};

class NumAST : public AST {
  int value;

public:
  NumAST(int value) {
    this->value = value;
  };
  int visit() {
    return this->value;
  };
};

#endif
