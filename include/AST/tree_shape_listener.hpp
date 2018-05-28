#ifndef BRICK_AST_TREE_SHAPE_LISTENER_
#define BRICK_AST_TREE_SHAPE_LISTENER_

#include <iostream>

#include "antlr4-runtime.h"
#include "brick.hpp"
#include "MathBaseListener.h"
#include "MathParser.h"

namespace brick::AST
{

class tree_shape_listener : public MathBaseListener {
public:
  void enterMath(brick::MathParser::MathContext *) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterInfixExpr(MathParser::InfixExprContext* ctx) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if (ctx->OP_ADD()) {

    } else if (ctx->OP_SUB()) {

    } else if (ctx->OP_MUL()) {

    } else if (ctx->OP_DIV()) {

    } else {

    }
  }

  void enterUnaryExpr(MathParser::UnaryExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterFuncExpr(MathParser::FuncExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterNumberExp(MathParser::NumberExpContext* ctx) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << ctx->value->getText() << std::endl;
  }

  void enterParensExpr(MathParser::ParensExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

}

#endif
