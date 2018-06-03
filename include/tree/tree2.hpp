#ifndef BRICK_TREE_TREE2_HPP_
#define BRICK_TREE_TREE2_HPP_

#include <vector>

#include "AST/node.hpp"

namespace brick::tree
{
  using expr_node = brick::AST::expression_node;

  class tree2 {
    private:
      expr_node* expr_;
      std::vector<tree2*> children_; // TODO: unnecessary?
      tree2* parent_ = nullptr;
    public:
      tree2(expr_node*);
      void set_expr(expr_node*);
      bool is_full() const;
      bool is_terminal() const;
      tree2* add_child(tree2*);
      tree2* add_child(expr_node*);
      void set_parent(tree2*);
      tree2* get_parent() const;
      void print_helper() const;
      void print() const;
  };

  tree2::tree2(expr_node* expr)
    : expr_(expr)
  {}

  void tree2::set_expr(expr_node* expr) {
    expr_ = expr;
  }

  bool tree2::is_full() const {
    return expr_->num_children() == children_.size();
  }

  bool tree2::is_terminal() const {
    return expr_->is_terminal();
  }

  tree2* tree2::add_child(tree2* child) {
    if (is_full() || is_terminal()) {
      return nullptr;
    }
    children_.push_back(child);
    child->set_parent(this);
    return child;
  }

  tree2* tree2::add_child(expr_node* expr) {
    if (is_full() || is_terminal()) {
      return nullptr;
    }
    tree2* child = new tree2(expr);
    children_.push_back(child);

    child->set_parent(this);
    return child;
  }

  void tree2::set_parent(tree2* parent) {
    parent_ = parent;
  }

  tree2* tree2::get_parent() const {
    return parent_;
  }

  void tree2::print_helper() const {
    if (children_.size() == 0) {
      std::cout << expr_->to_string();
    } else if (children_.size() == 1) {
      std::cout << expr_->to_string();
      children_[0]->print_helper();
    } else {
      children_[0]->print_helper();
      std::cout << expr_->to_string();
      children_[1]->print_helper();
    }
  }

  void tree2::print() const {
    print_helper();
    std::cout << std::endl;
  }

}

#endif
