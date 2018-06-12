#ifndef BRICK_AST_BFS_ITERATOR_HPP_
#define BRICK_AST_BFS_ITERATOR_HPP_

#include "AST/iterator.hpp"

namespace brick::AST
{
  class bfs_iterator : public brick::AST::iterator {
    public:
      bfs_iterator(brick::AST::AST*, brick::AST::AST*);
      bfs_iterator& operator++();
      bfs_iterator operator++(int);
      bfs_iterator& operator--();
      bfs_iterator operator--(int);
    private:
      std::vector<AST*> traversal();
  };
}

#endif