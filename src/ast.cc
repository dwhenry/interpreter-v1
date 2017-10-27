#include "ast.h"
#include "visitor.h"


BinAST::BinAST(AST * left, TokenType::TOKENS op, AST * right) {
  this->left = left;
  this->op = op;
  this->right = right;
}
void BinAST::accept(Visiter &i)
{
  i.visit(this);
}

NumAST::NumAST(int value) {
  this->value = value;
}
void NumAST::accept(Visiter &i)
{
  i.visit(this);
}
