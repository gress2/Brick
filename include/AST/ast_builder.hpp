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
  brick::tree::tree2 tree_;

public:

  ast_builder()
    : tree_(nullptr)
  {}

  void enterInfixExpr(MathParser::InfixExprContext* ctx) override {
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

  void enterUnaryExpr(MathParser::UnaryExprContext* ctx) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if (ctx->OP_ADD()) {
      // skip?
    }

  }

  void enterFuncExpr(MathParser::FuncExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterNumberExpr(MathParser::NumberExprContext* ctx) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << ctx->value->getText() << std::endl;
  }

  void enterIdExpr(MathParser::IdExprContext* ctx) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

}

#endif
