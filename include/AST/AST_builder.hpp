#ifndef BRICK_AST_AST_builder_
#define BRICK_AST_AST_builder_

#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "brick.hpp"
#include "MathBaseListener.h"

#include "MathParser.h"
namespace brick::AST
{

class AST_builder : public MathBaseListener {
  private:
    brick::AST::AST* root_;
    brick::AST::AST* cur_;
    bool append_node(brick::AST::node*);
  public:
    AST_builder();
    void enterParensExpr(MathParser::ParensExprContext*) override;
    void enterBracketsExpr(MathParser::BracketsExprContext*) override;
    void enterInfixExpr(MathParser::InfixExprContext*) override;
    void enterUnaryExpr(MathParser::UnaryExprContext*) override;
    void enterFuncExpr(MathParser::FuncExprContext*) override;
    void enterNumberExpr(MathParser::NumberExprContext*) override;
    void enterIdExpr(MathParser::IdExprContext*) override;
    brick::AST::AST* build() const;
    void reset();
};

AST_builder::AST_builder()
  : root_(nullptr), cur_(nullptr)
{}

void AST_builder::enterParensExpr(MathParser::ParensExprContext* ctx) {
  brick::AST::node* parens_expr = new brick::AST::parens_node();
  append_node(parens_expr);
}

void AST_builder::enterBracketsExpr(MathParser::BracketsExprContext* ctx) {
  brick::AST::node* brackets_expr = new brick::AST::brackets_node();
  append_node(brackets_expr);
}

void AST_builder::enterInfixExpr(MathParser::InfixExprContext* ctx) {
  brick::AST::node* infix_expr = nullptr;

  if (ctx->OP_ADD()) {
    infix_expr = new brick::AST::addition_node();
  } else if (ctx->OP_SUB()) {
    infix_expr = new brick::AST::subtraction_node();
  } else if (ctx->OP_MUL()) {
    infix_expr = new brick::AST::multiplication_node();
  } else if (ctx->OP_DIV()) {
    infix_expr = new brick::AST::division_node();
  } else {
    // exp
  }
  append_node(infix_expr);
}

void AST_builder::enterUnaryExpr(MathParser::UnaryExprContext* ctx) {
  brick::AST::node* unary_expr = nullptr;
  if (ctx->OP_ADD()) {
    unary_expr = new brick::AST::posit_node();
  } else if (ctx->OP_SUB()) {
    unary_expr = new brick::AST::negate_node();
  }
  append_node(unary_expr);
}

void AST_builder::enterFuncExpr(MathParser::FuncExprContext* ctx) {
  std::string fname = ctx->func->getText();
  brick::AST::node* func_expr = nullptr;
  if (fname == "sin") {
    func_expr = new brick::AST::sin_function_node();
  } else if (fname == "cos") {
    func_expr = new brick::AST::cos_function_node();
  } else if (fname == "log") {
    func_expr = new brick::AST::log_function_node();
  } else {
    func_expr = new brick::AST::function_node(fname);
  } 

  append_node(func_expr);
}

void AST_builder::enterNumberExpr(MathParser::NumberExprContext* ctx) {
  float num = std::stof(ctx->value->getText());
  brick::AST::node* number_expr = new brick::AST::number_node(num);
  append_node(number_expr);
}

void AST_builder::enterIdExpr(MathParser::IdExprContext* ctx) {
  std::string id = ctx->id->getText();
  brick::AST::node* id_expr = new brick::AST::id_node(id);
  append_node(id_expr);
}

brick::AST::AST* AST_builder::build() const {
  return root_;
}

void AST_builder::reset() {
  root_ = nullptr;
  cur_ = nullptr;
}

bool AST_builder::append_node(brick::AST::node* expr) {
  if (!root_) {
    root_ = new brick::AST::AST(expr);
    cur_ = root_;
    return true;
  }

  while (cur_) {
    auto* added_child = cur_->add_child(expr);
    if (added_child) {
      cur_ = added_child;
      return true;
    }
    cur_ = cur_->get_parent();
  }

  return false;
}

}

#endif
