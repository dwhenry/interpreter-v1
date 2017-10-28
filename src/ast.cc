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

UniaryAST::UniaryAST(AST * node, TokenType::TOKENS op) {
  this->op = op;
  this->node = node;
}
void UniaryAST::accept(Visiter &i)
{
  i.visit(this);
}

ListAST::ListAST() {}
void ListAST::add(AST * node) {
  if(node != NULL) {
    statements.push_back(node);
  }
}
void ListAST::accept(class Visiter &i) {
  i.visit(this);
}

AssignAST::AssignAST(std::string id, AST * value) {
  this->id = id;
  this->value = value;
}
void AssignAST::accept(class Visiter &i) {
  i.visit(this);
}

ReturnAST::ReturnAST(AST * value) {
  this->value = value;
}
void ReturnAST::accept(class Visiter &i) {
  i.visit(this);
}

VarAST::VarAST(std::string id) {
  this->id = id;
}
void VarAST::accept(class Visiter &i) {
  i.visit(this);
}

