#include "AST/AST.hpp"
#include "AST/iterator.hpp"

namespace brick::AST
{
  iterator::iterator(AST* cur, AST* root)
    : cur_(cur), root_(root)
  {}

  AST& iterator::operator*() const {
    return *cur_;
  }

  AST* iterator::operator->() const {
    return cur_;
  }

  std::size_t iterator::position() const {
    if (cur_->get_parent()) {
      auto& parent_children = cur_->get_parent()->get_children();
      return 0;
    }
  }

}