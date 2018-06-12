#include "AST/dfs_iterator.hpp"

namespace brick::AST
{
  dfs_iterator::dfs_iterator(brick::AST::AST* cur, brick::AST::AST* root) 
    : brick::AST::iterator(cur, root)
  {}

  dfs_iterator& dfs_iterator::operator++() {
    return *this;
  }

  dfs_iterator dfs_iterator::operator++(int) {
    dfs_iterator copy = *this;
    ++(*this);
    return copy;
  }

}