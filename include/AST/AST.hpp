#ifndef BRICK_AST_AST_HPP_
#define BRICK_AST_AST_HPP_

#include <map>
#include <vector>

#include "AST/node.hpp"

namespace brick::AST
{
  using expr_node = brick::AST::expression_node;

  class AST {
    private:
      expr_node* expr_;
      std::vector<AST*> children_; // TODO: unnecessary?
      AST* parent_ = nullptr;
    public:
      AST(expr_node*);
      void set_expr(expr_node*);
      bool is_full() const;
      bool is_terminal() const;
      AST* add_child(AST*);
      AST* add_child(expr_node*);
      void set_parent(AST*);
      AST* get_parent() const;
      std::string to_string() const;
      void print() const;
      double eval(std::map<std::string, double>* = nullptr) const;
  };

  AST::AST(expr_node* expr)
    : expr_(expr)
  {}

  void AST::set_expr(expr_node* expr) {
    expr_ = expr;
  }

  bool AST::is_full() const {
    return expr_->num_children() == children_.size();
  }

  bool AST::is_terminal() const {
    return expr_->is_terminal();
  }

  AST* AST::add_child(AST* child) {
    if (is_full() || is_terminal()) {
      return nullptr;
    }
    children_.push_back(child);
    child->set_parent(this);
    return child;
  }

  AST* AST::add_child(expr_node* expr) {
    if (is_full() || is_terminal()) {
      return nullptr;
    }
    AST* child = new AST(expr);
    children_.push_back(child);

    child->set_parent(this);
    return child;
  }

  void AST::set_parent(AST* parent) {
    parent_ = parent;
  }

  AST* AST::get_parent() const {
    return parent_;
  }

  std::string AST::to_string() const {
    if (children_.size() == 0) {
      return expr_->to_string();
    } else if (children_.size() == 1) {
      if (expr_->wraps()) {
        return expr_->wrap_left() +
          children_[0]->to_string() +
          expr_->wrap_right();
      } else {
        return expr_->to_string() +
          children_[0]->to_string();
      }
    } else {
      return children_[0]->to_string() +
        expr_->to_string() + 
        children_[1]->to_string();
    } 
  }

  void AST::print() const {
    std::cout << to_string() << std::endl;
  }

  double AST::eval(std::map<std::string, double>* symbol_table) const {
    return 0;
  }

}

#endif
