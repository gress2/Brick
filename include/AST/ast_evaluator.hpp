#ifndef BRICK_AST_AST_EVALUATOR_HPP_
#define BRICK_AST_AST_EVALUATOR_HPP_

#include <iostream>

#include "MathBaseVisitor.h"

class ast_evalutator : public brick::MathBaseVisitor {
  antlrcpp::Any visitMath(brick::MathParser::MathContext *ctx) override {
    std::cout << "FUCK" << std::endl;
    return visitChildren(ctx);
  }
};

#endif
