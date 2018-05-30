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
      bool add_child(tree2*);
      void set_parent(tree2*);
  };

  tree2::tree2(expr_node* expr)
    : expr_(expr)
  {}

  void tree2::set_expr(expr_node* expr) {
    expr_ = expr;
  }

  bool tree2::is_full() const {
    return expr_->num_children == children_.size();
  }

  bool tree2::add_child(tree2* child) {
    if (is_full()) {
      return false;
    }
    children_.push_back(child);
    child->set_parent(this);
    return true;
  }

  void tree2::set_parent(tree2* parent) {
    parent_ = parent;
  }


}

#endif
