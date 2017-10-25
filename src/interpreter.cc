#include "interpreter.h"
#include <sstream>

void check(TokenDetails * token, TokenType::TOKENS expectedType) {
    // std::cout << "here";
  if(token->type != expectedType) {
    // std::stringstream result;
    // result << "Invalid token " << token->str << " at:" << token->lineNumber << ":" << token.startPosition;

    throw "apples"; //result.str();
  }
}

void checkAny(TokenDetails * token, TokenType::TOKENS allowedTypes[], int allowedTypeCount) {
  for(int i = 0; i < allowedTypeCount; i++) {
    if(token->type == allowedTypes[i]) {
      return;
    }
  }

  // std::stringstream result;
  // result << "Invalid token " << token->str << " at:" << token->lineNumber << ":" << token.startPosition;

  // throw result.str();
}

std::string Interpreter::process(std::string command) {
  Scan * scanner = new Scan(command);

  TokenDetails * left;
  TokenDetails * action;
  TokenDetails * right;

  left = scanner->next();
  check(left, TokenType::NUM);

  action = scanner->next();
  TokenType::TOKENS allowedActions[3];
  allowedActions[0] = TokenType::PLUS;
  allowedActions[1] = TokenType::MINUS;
  allowedActions[1] = TokenType::TIMES;
  checkAny(action, allowedActions, 3);

  right = scanner->next();
  check(right, TokenType::NUM);

  int value = 0, temp;
  std::stringstream(left->str) >> temp;
  value = value + temp;
  std::stringstream(right->str) >> temp;
  switch(action->type) {
  case TokenType::PLUS:
    value = value + temp;
    break;
  case TokenType::MINUS:
    value = value - temp;
    break;
  case TokenType::TIMES:
    value = value * temp;
    break;
  default:
    throw "Invalid state";
  }


  std::stringstream result;
  result << "Result of " << command << " is: " << value;
  return result.str();
}
