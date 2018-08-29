#include "AST/AST.hpp"
#include "AST/iterator.hpp"

namespace brick
{
namespace AST
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
      std::size_t dist = 0;
      for (auto& sp : parent_children) {
        if (sp.get() == cur_) {
          break;
        }
        dist++;
      }
      return dist;
    } else {
      return 0;
    }
  }

  bool iterator::is_first() const {
    return cur_->get_parent() == nullptr || position() == 0;
  }

  bool iterator::is_last() const {
    return cur_->get_parent() == nullptr ||
      ((position() + 1) == cur_->get_parent()->get_children().size());
  }

  bool iterator::operator==(const iterator& other) const {
    return root_ == other.root_ && cur_ == other.cur_;
  }

  bool iterator::operator!=(const iterator& other) const {
    return !this->operator==(other);
  }

}
}
