#ifndef BRICK_AST_TREE_SHAPE_LISTENER_
#define BRICK_AST_TREE_SHAPE_LISTENER_

#include <iostream>

#include "antlr4-runtime.h"
#include "MathBaseListener.h"
#include "MathParser.h"

namespace brick::AST
{

class tree_shape_listener : public MathBaseListener {
public:
  void enterMath(brick::MathParser::MathContext *) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterInfixExpr(MathParser::InfixExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterUnaryExpr(MathParser::UnaryExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterFuncExpr(MathParser::FuncExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterNumberExp(MathParser::NumberExpContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void enterParensExpr(MathParser::ParensExprContext * /*ctx*/) override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

}

#endif
