#include "interpreter.h"
#include <sstream>

int Interpreter::factor() {
  int value;

  switch(this->nextToken->type) {
  case TokenType::NUM:
    std::stringstream(this->nextToken->str) >> value;
    this->eat(TokenType::NUM);
    return value;
  case TokenType::L_BR:
    this->eat(TokenType::L_BR);
    value = this->exp();
    this->eat(TokenType::R_BR);
    return value;
  default:
    this->error("Invalid token: ");
    return 0;
  }
}

void Interpreter::eat(TokenType::TOKENS tokenType) {
  if(this->nextToken->type == tokenType) {
    this->nextToken = this->scanner->next();
  } else {
    std::stringstream token, msg;
    switch(tokenType) {
    case TokenType::ENDFILE:
      token << "EOF";
      break;
    default:
      for(int i=0; i < TOKENS_MAPS; i++) {
        if(tokenMap[i].token == tokenType) {
          token << std::string(1, tokenMap[i].current);
          if(tokenMap[i].preview != '\0') {
            token << std::string(1, tokenMap[i].preview);
          }
        }
      }
    }
    msg << "Expected '" << token.str() << "' got: ";
    this->error(msg.str());
  }
}

void Interpreter::error(std::string msg) {
  std::stringstream result;
  result << msg << this->nextToken->str << " at:" << this->nextToken->lineNumber << ":" << this->nextToken->startPosition;
  throw result.str();
}

int Interpreter::term() {
  int value;
  bool process = true;
  std::stringstream result;

  value = this->factor();

  while(process) {

    switch(this->nextToken->type) {
    case TokenType::TIMES:
      this->eat(TokenType::TIMES);
      value = value * this->factor();
      break;
    case TokenType::DIVIDE:
      this->eat(TokenType::DIVIDE);
      value = value / this->factor();
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

  value = this->term();

  while(process) {
    switch(this->nextToken->type) {
    case TokenType::PLUS:
      this->eat(TokenType::PLUS);
      value = value + this->term();
      break;
    case TokenType::MINUS:
      this->eat(TokenType::MINUS);
      value = value - this->term();
      break;
    default:
      process = false;
      break;
    };
  }

  return value;
}


std::string Interpreter::process(std::string command) {
  std::stringstream result;

  this->scanner = new Scan(command);
  this->nextToken = this->scanner->next();
  int value;

  value = this->exp();

  this->eat(TokenType::ENDFILE);

  result << value;
  return result.str();
}
