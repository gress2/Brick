#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "antlr4-runtime.h"
#include "brick.hpp"
#include "MathBaseListener.h"
#include "MathParser.h"

namespace brick::AST
{

class AST_builder : public MathBaseListener {
  private:
    std::unique_ptr<brick::AST::AST> root_;
    brick::AST::AST* cur_;
    bool append_node(std::unique_ptr<brick::AST::node>&&);
  public:
    AST_builder();
    void enterParensExpr(MathParser::ParensExprContext*) override;
    void enterBracketsExpr(MathParser::BracketsExprContext*) override;
    void enterInfixExpr(MathParser::InfixExprContext*) override;
    void enterUnaryExpr(MathParser::UnaryExprContext*) override;
    void enterFuncExpr(MathParser::FuncExprContext*) override;
    void enterNumberExpr(MathParser::NumberExprContext*) override;
    void enterIdExpr(MathParser::IdExprContext*) override;
    std::unique_ptr<brick::AST::AST>&& build();
    void reset();
};

}
