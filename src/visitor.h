#ifndef _VISITOR_H_
#define _VISITOR_H_

#include "globals.h"
#include <sstream>
#include <stack>
#include <map>

class Visiter {
  std::stack<int> stack;
  std::map<std::string, int> memory;
  bool exit = false;
  int lastValue;

public:
  int value() {
    return lastValue;
  }

  void visit(BinAST * node) {
    if(this->exit) return;
    node->left->accept(*this);
    if(this->exit) return;
    node->right->accept(*this);

    int right = this->stack.top();
    this->stack.pop();
    int left = this->stack.top();
    this->stack.pop();

    switch(node->op) {
    case TokenType::PLUS:
      this->stack.push(left + right);
      break;
    case TokenType::MINUS:
      this->stack.push(left - right);
      break;
    case TokenType::TIMES:
      this->stack.push(left * right);
      break;
    case TokenType::DIVIDE:
      this->stack.push(left / right);
      break;
    default:
      std::stringstream result;
      result << "Unexpected operation: " << node->op << "valid '+' = " << TokenType::PLUS;
      throw result.str();
    }
  }

  void visit(NumAST * node) {
    this->stack.push(node->value);
  }

  void visit(UniaryAST * node) {
    if(this->exit) return;
    node->node->accept(*this);

    if(node->op == TokenType::MINUS) {
      int value = this->stack.top();
      this->stack.pop();
      this->stack.push(-1 * value);
    }
  }

  void visit(ListAST * node) {
    for(AST * n : node->statements) {
      if(this->exit) return;
      n->accept(*this);
      if(this->stack.size() == 1) {
        this->lastValue = this->stack.top();
        this->stack.pop();
      } else if(this->stack.size() > 1) {
        std::stringstream result;
        result << "Elements left on the stack: " << this->stack.size();
        throw result.str();
      }
    }
  }

  void visit(AssignAST * node) {
    if(this->exit) return;
    node->value->accept(*this);

    this->memory[node->id] = this->stack.top();
    this->stack.pop();
  }

  void visit(ReturnAST * node) {
    if(this->exit) return;
    node->value->accept(*this);
    this->exit = true;
    // TODO: need to break out of the call chain
  }

  void visit(VarAST * node) {
    if(this->memory.count(node->id) == 0) {
      std::stringstream result;
      result << "Uninitialised variable: " << node->id;
      throw result.str();
    }
    this->stack.push(this->memory[node->id]);
  }
};

#endif
