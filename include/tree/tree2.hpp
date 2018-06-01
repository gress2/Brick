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
      bool add_child(tree2*);
      bool add_child(expr_node*);
      void set_parent(tree2*);
      tree2* get_parent() const;
      void print() const;
  };

  tree2::tree2(expr_node* expr)
    : expr_(expr)
  {}

  void tree2::set_expr(expr_node* expr) {
    expr_ = expr;
  }

  bool tree2::is_full() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << expr_->num_children() << std::endl;
    return expr_->num_children() == children_.size();
  }

  bool tree2::is_terminal() const {
    return expr_->is_terminal();
  }

  bool tree2::add_child(tree2* child) {
    if (is_full() || is_terminal()) {
      return false;
    }
    children_.push_back(child);
    child->set_parent(this);
    return true;
  }

  bool tree2::add_child(expr_node* expr) {
    if (is_full() || is_terminal()) {
      return false;
    }
    tree2* child = new tree2(expr);
    children_.push_back(child);
    child->set_parent(this);
    return true;
  }

  void tree2::set_parent(tree2* parent) {
    parent_ = parent;
  }

  tree2* tree2::get_parent() const {
    return parent_;
  }

  void tree2::print() const {
    std::cout << children_.size() << std::endl;
    if (children_.size() == 0) {
      std::cout << expr_->to_string() << std::endl;
    } else if (children_.size() == 1) {
      std::cout << expr_->to_string() << std::endl;
      children_[0]->print();
    } else {
      children_[0]->print();
      std::cout << expr_->to_string() << std::endl;
      children_[1]->print();
    }
  }

}

#endif
