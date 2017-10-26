#include "interpreter.h"
#include <sstream>

int Interpreter::factor(TokenType::TOKENS expectedType) {
  if(this->nextToken->type != expectedType) {
    std::stringstream result;
    result << "Invalid token " << this->nextToken->str << " at:" << this->nextToken->lineNumber << ":" << this->nextToken->startPosition;
    throw result.str();
  }

  int value;
  std::stringstream(this->nextToken->str) >> value;
  this->nextToken = this->scanner->next();
  return value;
}

int Interpreter::term() {
  int value;
  bool process = true;
  std::stringstream result;

  value = this->factor(TokenType::NUM);

  while(process) {

    switch(this->nextToken->type) {
    case TokenType::TIMES:
      this->nextToken = this->scanner->next();
      value = value * this->factor(TokenType::NUM);
      break;
    case TokenType::DIVIDE:
      this->nextToken = this->scanner->next();
      value = value / this->factor(TokenType::NUM);
      break;
    default:
      process = false;
      break;
    };
  }

  return value;
}

int Interpreter::exp() {
  int value;
  bool process = true;
  std::stringstream result;

  this->nextToken = this->scanner->next();
  value = this->term();

  while(process) {
    switch(this->nextToken->type) {
    case TokenType::ENDFILE:
      // std::cout << "EOF reached" << std::endl;
      process = false;
      break;
    case TokenType::PLUS:
      this->nextToken = this->scanner->next();
      value = value + this->term();
      break;
    case TokenType::MINUS:
      this->nextToken = this->scanner->next();
      value = value - this->term();
      break;
    default:
      result << "Invalid token " << this->nextToken->str << " at:" << this->nextToken->lineNumber << ":" << this->nextToken->startPosition;
      throw result.str();
    };
  }

  return value;
}

std::string Interpreter::process(std::string command) {
  std::stringstream result;

  this->scanner = new Scan(command);
  result << "Result of " << command << " is: " << exp();
  return result.str();
}
