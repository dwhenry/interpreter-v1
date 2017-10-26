#include "interpreter.h"
#include <sstream>

AST * Interpreter::factor() {
  AST * node;

  switch(this->nextToken->type) {
  case TokenType::NUM:
    int value;
    std::stringstream(this->nextToken->str) >> value;
    this->eat(TokenType::NUM);
    return new NumAST(value);
  case TokenType::L_BR:
    this->eat(TokenType::L_BR);
    node = this->exp();
    this->eat(TokenType::R_BR);
    return node;
  default:
    this->error("Invalid token: ");
    return NULL;
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

AST * Interpreter::term() {
  AST * node;
  bool process = true;
  std::stringstream result;

  node = this->factor();

  while(process) {

    switch(this->nextToken->type) {
    case TokenType::TIMES:
      this->eat(TokenType::TIMES);
      node = new BinAST(node, TokenType::TIMES, this->factor());
      break;
    case TokenType::DIVIDE:
      this->eat(TokenType::DIVIDE);
      node = new BinAST(node, TokenType::DIVIDE, this->factor());
      break;
    default:
      process = false;
      break;
    };
  }

  return node;
}

AST * Interpreter::exp() {
  AST * node;
  bool process = true;
  std::stringstream result;

  node = this->term();

  while(process) {
    switch(this->nextToken->type) {
    case TokenType::PLUS:
      this->eat(TokenType::PLUS);
      node = new BinAST(node, TokenType::PLUS, this->term());
      break;
    case TokenType::MINUS:
      this->eat(TokenType::MINUS);
      node = new BinAST(node, TokenType::MINUS, this->term());
      break;
    default:
      process = false;
      break;
    };
  }

  return node;
}


std::string Interpreter::process(std::string command) {
  std::stringstream result;

  this->scanner = new Scan(command);
  this->nextToken = this->scanner->next();
  AST * node;

  node = this->exp();

  this->eat(TokenType::ENDFILE);

  result << this->visit(node);
  return result.str();
}

int Interpreter::visit(AST * node) {
  std::cout << "Failed" << std::endl;
  return 0;
}

int Interpreter::visit(BinAST * node) {
  switch(node->op) {
  case TokenType::PLUS:
    return this->visit(node->left) + this->visit(node->right);
  case TokenType::MINUS:
    return this->visit(node->left) - this->visit(node->right);
  case TokenType::TIMES:
    return this->visit(node->left) * this->visit(node->right);
  case TokenType::DIVIDE:
    return this->visit(node->left) / this->visit(node->right);
  default:
    throw "Umnexpected";
  }
}

int Interpreter::visit(NumAST * node) {
  return node->value;
}
