#include "parser.h"
#include <sstream>

AST * Parser::factor() {
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

void Parser::eat(TokenType::TOKENS tokenType) {
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

void Parser::error(std::string msg) {
  std::stringstream result;
  result << msg << this->nextToken->str << " at:" << this->nextToken->lineNumber << ":" << this->nextToken->startPosition;
  throw result.str();
}

AST * Parser::term() {
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

AST * Parser::exp() {
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


std::string Parser::process(std::string command) {
  std::stringstream result;

  this->scanner = new Scan(command);
  this->nextToken = this->scanner->next();
  AST * node;

  node = this->exp();

  this->eat(TokenType::ENDFILE);

  Visiter v;
  node->accept(v);
  result << v.value();
  return result.str();
}

