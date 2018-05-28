#ifndef BRICK_AST_BUILD_AST_VISITOR_HPP_
#define BRICK_AST_BUILD_AST_VISITOR_HPP_

#include <iostream>

#include "MathBaseVisitor.h"

class build_ast_visitor : public brick::MathBaseVisitor {
  antlrcpp::Any visitMath(brick::MathParser::MathContext *ctx) override {
    std::cout << "FUCK" << std::endl;
    return visitChildren(ctx);
  }
};

#endif
