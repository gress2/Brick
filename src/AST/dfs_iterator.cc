#include "AST/AST.hpp"
#include "AST/dfs_iterator.hpp"

namespace brick
{
namespace AST
{
  dfs_iterator::dfs_iterator(brick::AST::AST* cur, brick::AST::AST* root) 
    : brick::AST::iterator(cur, root)
  {}

  dfs_iterator& dfs_iterator::operator++() {
    if (cur_->get_children().empty()) {
      if (!this->is_last()) {
        cur_ = cur_->get_parent()->get_child(this->position() + 1).get();
      } else {
        dfs_iterator tmp = *this;
        while (tmp.is_last()) {
          if (tmp.cur_ == this->root_) {
            this->cur_ = nullptr;
            return *this;
          }
          tmp = dfs_iterator(tmp.cur_->get_parent(), this->root_);
        }
        cur_ = tmp.cur_->get_parent()->get_child(tmp.position() + 1).get();
      }
    } else {
      cur_ = cur_->get_child(0).get();
    }
    return *this;
  }

  dfs_iterator dfs_iterator::operator++(int) {
    dfs_iterator copy = *this;
    ++(*this);
    return copy;
  }

  dfs_iterator& dfs_iterator::operator--() {
    if (cur_ == nullptr) {
      cur_ = root_;
      while (!cur_->get_children().empty()) {
        cur_ = cur_->get_child(cur_->get_children().size() - 1).get();
      }
      return *this;
    }
    if (cur_->get_parent() != nullptr) {
      if (!this->is_first()) {
        cur_ = cur_->get_parent()->get_child(this->position() - 1).get();
        while (!cur_->get_children().empty()) {
          cur_ = cur_->get_child(cur_->get_children().size() - 1).get();
        }
      } else {
        cur_ = cur_->get_parent();
      }
    }
    return *this;
  }

  dfs_iterator dfs_iterator::operator--(int) {
    dfs_iterator copy = *this;
    --(*this);
    return copy;
  }
}
}
