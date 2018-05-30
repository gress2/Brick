#ifndef BRICK_TREE_TREE2_HPP_
#define BRICK_TREE_TREE2_HPP_

#include "AST/node.hpp"

namespace brick::tree
{
  using expr_node = brick::AST::expression_node;

  class tree2 {
    private:
      expr_node* expr_;
    public:
      tree2(expr_node*);
  };

  tree2::tree2(expr_node* expr)
    : expr_(expr)
  {}
}

#endif
