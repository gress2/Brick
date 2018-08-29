#include "AST/AST_builder.hpp"

namespace brick
{
namespace AST
{

AST_builder::AST_builder()
  : root_(nullptr), cur_(nullptr)
{}

void AST_builder::enterParensExpr(MathParser::ParensExprContext* ctx) {
  append_node(std::make_unique<brick::AST::parens_node>());
}

void AST_builder::enterBracketsExpr(MathParser::BracketsExprContext* ctx) {
  append_node(std::make_unique<brick::AST::brackets_node>());
}

void AST_builder::enterInfixExpr(MathParser::InfixExprContext* ctx) {
  std::unique_ptr<brick::AST::node> infix_expr = nullptr;

  if (ctx->OP_ADD()) {
    infix_expr = std::make_unique<brick::AST::addition_node>();
  } else if (ctx->OP_SUB()) {
    infix_expr = std::make_unique<brick::AST::subtraction_node>();
  } else if (ctx->OP_MUL()) {
    infix_expr = std::make_unique<brick::AST::multiplication_node>();
  } else if (ctx->OP_DIV()) {
    infix_expr = std::make_unique<brick::AST::division_node>();
  } else if (ctx->OP_EXP()) {
    infix_expr = std::make_unique<brick::AST::exponentiation_node>();
  }
  append_node(std::move(infix_expr));
}

void AST_builder::enterUnaryExpr(MathParser::UnaryExprContext* ctx) {
  std::unique_ptr<brick::AST::node> unary_expr = nullptr;
  if (ctx->OP_ADD()) {
    unary_expr = std::make_unique<brick::AST::posit_node>();
  } else if (ctx->OP_SUB()) {
    unary_expr = std::make_unique<brick::AST::negate_node>();
  }
  append_node(std::move(unary_expr));
}

void AST_builder::enterFuncExpr(MathParser::FuncExprContext* ctx) {
  std::string fname = ctx->func->getText();
  std::unique_ptr<brick::AST::node> func_expr = nullptr;
  if (fname == "sin") {
    func_expr = std::make_unique<brick::AST::sin_function_node>();
  } else if (fname == "cos") {
    func_expr = std::make_unique<brick::AST::cos_function_node>();
  } else if (fname == "log") {
    func_expr = std::make_unique<brick::AST::log_function_node>();
  } else {
    func_expr = std::make_unique<brick::AST::function_node>(fname);
  } 

  append_node(std::move(func_expr));
}

void AST_builder::enterNumberExpr(MathParser::NumberExprContext* ctx) {
  float num = std::stof(ctx->value->getText());
  append_node(std::make_unique<brick::AST::number_node>(num));
}

void AST_builder::enterIdExpr(MathParser::IdExprContext* ctx) {
  std::string id = ctx->id->getText();
  append_node(std::make_unique<brick::AST::id_node>(id));
}

std::unique_ptr<brick::AST::AST>&& AST_builder::build() {
  return std::move(root_);
}

void AST_builder::reset() {
  root_ = nullptr;
  cur_ = nullptr;
}

bool AST_builder::append_node(std::unique_ptr<brick::AST::node>&& expr) {
  if (!root_) {
    root_ = std::make_unique<brick::AST::AST>(std::move(expr));
    cur_ = root_.get();
    return true;
  }

  while (cur_) {
    std::shared_ptr<brick::AST::AST> added_child = cur_->add_child(std::move(expr));
    if (added_child) {
      cur_ = added_child.get();
      return true;
    }
    cur_ = cur_->get_parent();
  }

  return false;
}
}
}
