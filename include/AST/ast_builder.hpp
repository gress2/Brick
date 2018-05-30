#ifndef BRICK_AST_AST_BUILDER_
#define BRICK_AST_AST_BUILDER_

#include <iostream>

#include "antlr4-runtime.h"
#include "brick.hpp"
#include "MathBaseListener.h"
#include "MathParser.h"

namespace brick::AST
{

class ast_builder : public MathBaseListener {
  private:
    brick::tree::tree2* root_;
    brick::tree::tree2* cur_;
  public:
    ast_builder();
    void enterInfixExpr(MathParser::InfixExprContext*) override;
    void enterUnaryExpr(MathParser::UnaryExprContext*) override;
    void enterFuncExpr(MathParser::FuncExprContext*) override;
    void enterNumberExpr(MathParser::NumberExprContext*) override;
    void enterIdExpr(MathParser::IdExprContext*) override;
    brick::tree::tree2* build() const;
    void reset();
};

ast_builder::ast_builder()
  : tree_(nullptr)
{}

void ast_builder::enterInfixExpr(MathParser::InfixExprContext* ctx) override {
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  brick::AST::infix_expression_node* infix_expr = nullptr;

  if (ctx->OP_ADD()) {
    infix_expr = new brick::AST::addition_node();
  } else if (ctx->OP_SUB()) {
    infix_expr = new brick::AST::subtraction_node();
  } else if (ctx->OP_MUL()) {
    infix_expr = new brick::AST::subtraction_node();
  } else if (ctx->OP_DIV()) {
    infix_expr = new brick::AST::division_node();
  } else {
    // exp
  }
}

void ast_builder::enterUnaryExpr(MathParser::UnaryExprContext* ctx) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void ast_builder::enterFuncExpr(MathParser::FuncExprContext * /*ctx*/) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void ast_builder::enterNumberExpr(MathParser::NumberExprContext* ctx) override {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ctx->value->getText() << std::endl;
}

void ast_builder::enterIdExpr(MathParser::IdExprContext* ctx) override {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

brick::tree::tree2* ast_builder::build() const {
  return root_;
}

void ast_builder::reset() {
  root_ = nullptr;
  cur_ = nullptr;
}

};

}

#endif
