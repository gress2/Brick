#ifndef BRICK_AST_DFS_ITERATOR_HPP_
#define BRICK_AST_DFS_ITERATOR_HPP_

#include "AST/iterator.hpp"

namespace brick::AST
{
  class dfs_iterator : public brick::AST::iterator {
    private:

    public:
      dfs_iterator(brick::AST::AST*, brick::AST::AST*);
      dfs_iterator& operator++();
      dfs_iterator operator++(int);
      dfs_iterator& operator--();
      dfs_iterator operator--(int);
  };
}

#endif