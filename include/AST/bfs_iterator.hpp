#pragma once

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