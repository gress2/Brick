#pragma once

#include <iterator>

namespace brick
{
namespace AST
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
      bool operator==(const iterator& other) const;
      bool operator!=(const iterator& other) const;
  };
}
}
