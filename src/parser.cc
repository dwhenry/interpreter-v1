#include "parser.h"
#include <sstream>

AST * Parser::factor() {
  AST * node;

  switch(this->nextToken->type) {
  case TokenType::PLUS:
    // this can be ignored as it doesn't do anything
    this->eat();
    return this->factor();
  case TokenType::MINUS:
    this->eat();
    return new UniaryAST(this->factor(), TokenType::MINUS);
  case TokenType::NUM:
    int value;
    std::stringstream(this->nextToken->str) >> value;
    this->eat();
    return new NumAST(value);
  case TokenType::ID:
    node = new VarAST(this->nextToken->str);
    this->eat();
    return node;
  case TokenType::L_BR:
    this->eat();
    node = this->exp();
    this->eat(TokenType::R_BR);
    return node;
  default:
    this->error("Invalid token: ");
    return NULL;
  }
}

void Parser::eat() {
  this->nextToken = this->scanner->next();
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
      this->eat();
      node = new BinAST(node, TokenType::TIMES, this->factor());
      break;
    case TokenType::DIVIDE:
      this->eat();
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
  AST * node = this->term();

  while(true) {
    switch(this->nextToken->type) {
    case TokenType::PLUS:
      this->eat();
      node = new BinAST(node, TokenType::PLUS, this->term());
      break;
    case TokenType::MINUS:
      this->eat();
      node = new BinAST(node, TokenType::MINUS, this->term());
      break;
    default:
      return node;
    };
  }
}

AST * Parser::assignmentStatement() {
  std::string tokenStr = this->nextToken->str;
  this->eat();
  if(this->nextToken->type == TokenType::ASSIGN) {
    this->eat();
    return new AssignAST(tokenStr, this->exp());
  } else {
    return new VarAST(tokenStr);
  }
}

AST * Parser::returnStatement() {
  this->eat();
  return new ReturnAST(this->exp());
}

AST * Parser::statement() {
  switch(this->nextToken->type) {
  case TokenType::ID:
    return this->assignmentStatement();
    break;
  case TokenType::RETURN:
    return this->returnStatement();
    break;
  default:
    return NULL;
  }
}

AST * Parser::statementList() {
  ListAST * list = new ListAST();

  list->add(this->statement());

  while(true) {
    switch(this->nextToken->type) {
    case TokenType::SEMI:
      this->eat();
      list->add(this->statement());
      break;
    default:
      return list;
    };
  }

}

std::string Parser::process(std::string command) {
  std::stringstream result;

  this->scanner = new Scan(command);
  this->nextToken = this->scanner->next();
  AST * node;

  node = this->statementList();

  this->eat(TokenType::ENDFILE);

  Visiter v;
  node->accept(v);
  result << v.value();
  return result.str();
}

