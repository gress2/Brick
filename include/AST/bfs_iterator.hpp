#ifndef BRICK_AST_BFS_ITERATOR_HPP
#define BRICK_AST_BFS_ITERATOR_HPP

#include "AST/iterator.hpp"

namespace brick::AST
{
  template <class Tree>
  class bfs_iterator : public brick::AST::iterator<Tree> {
    public:
      bfs_iterator(Tree*);
      bfs_iterator operator++(int);
      bfs_iterator& operator++();
      bfs_iterator operator--(int);
      bfs_iterator& operator--();
  };

  template <class Tree>
  bfs_iterator<Tree>::bfs_iterator(Tree* tree)
    : brick::AST::iterator<Tree>(tree)
  {}

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator++(int) {
    return *this;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator++() {
    return *this;
  }

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator--(int) {
    return *this;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator--() {
    return *this;
  }
}

#endif
