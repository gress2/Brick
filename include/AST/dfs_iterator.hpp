#ifndef BRICK_AST_DFS_ITERATOR_HPP
#define BRICK_AST_DFS_ITERATOR_HPP

#include "AST/iterator.hpp"

namespace brick::AST
{
  template <class Tree>
  class dfs_iterator : public brick::AST::iterator<Tree> {
    public:
      dfs_iterator(Tree*);
      dfs_iterator operator++(int);
      dfs_iterator& operator++();
      dfs_iterator operator--(int);
      dfs_iterator& operator--();
  };

  template <class Tree>
  dfs_iterator<Tree>::dfs_iterator(Tree* tree)
    : brick::AST::iterator<Tree>(tree)
  {}

  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator++(int) {
    return *this;
  }

  template <class Tree>
  dfs_iterator<Tree>& dfs_iterator<Tree>::operator++() {
    return *this;
  }

  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator--(int) {
    return *this;
  }

  template <class Tree>
  dfs_iterator<Tree>& dfs_iterator<Tree>::operator--() {
    return *this;
  }
}

#endif
