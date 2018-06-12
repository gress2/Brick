#ifndef BRICK_AST_ITERATOR_HPP_
#define BRICK_AST_ITERATOR_HPP_

#include <iterator>

namespace brick::AST
{
  class AST;

  class iterator {
    protected:
      AST* cur_;
      AST* root_;
    public:
      iterator(AST*, AST*);
      AST& operator*() const;
      AST* operator->() const;
      std::size_t position() const;
      bool is_first() const;
      bool is_last() const;
  };
}

#endif
