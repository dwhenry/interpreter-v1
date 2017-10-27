#ifndef _VISITOR_H_
#define _VISITOR_H_

#include "globals.h"
#include <sstream>
#include <stack>

class Visiter {
  std::stack<int> values;

public:
  int value() {
    if(this->values.size() == 1) {
      return this->values.top();
    } else {
      std::stringstream result;
      result << "Elements left on the stack: " << this->values.size();
      throw  result.str();
    }
  }

  void visit(BinAST * node) {
    node->left->accept(*this);
    node->right->accept(*this);

    int right = this->values.top();
    this->values.pop();
    int left = this->values.top();
    this->values.pop();

    switch(node->op) {
    case TokenType::PLUS:
      this->values.push(left + right);
      break;
    case TokenType::MINUS:
      this->values.push(left - right);
      break;
    case TokenType::TIMES:
      this->values.push(left * right);
      break;
    case TokenType::DIVIDE:
      this->values.push(left / right);
      break;
    default:
      std::stringstream result;
      result << "Umnexpected operation: " << node->op << "valid '+' = " << TokenType::PLUS;
      throw result.str();
    }
  }

  void visit(NumAST * node) {
    this->values.push(node->value);
  }
};

#endif
