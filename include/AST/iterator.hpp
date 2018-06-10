#ifndef BRICK_AST_ITERATOR_HPP
#define BRICK_AST_ITERATOR_HPP

#include <memory>

namespace brick::AST
{
  using AST = brick::AST::AST;

  class iterator {
    public:
      using difference_type = std::ptrdiff_t;
      using value_type = AST;
    protected:
      AST* tree_;
      AST* root_;
      bool is_first();
      bool is_last();
      std::size_t position();
    public:
      iterator(AST*, AST*);
      value_type& operator*() const;
      value_type* operator->() const;
      bool operator==(const iterator&) const;
      bool operator!=(const iterator&) const;
  };

  iterator::iterator(AST* tree, AST* root)
    : tree_(tree), root_(root)
  {}

  AST& iterator::operator*() const {
    return *tree_;
  }

  AST* iterator::operator->() const {
    return tree_;
  }

  std::size_t iterator::position() {
    if (tree_->get_parent()) {
      auto& parent_children = tree_->get_parent()->children();
      return std::distance(&*std::begin(parent_children), tree_);
    } else {
      return 0;
    }
  }

  bool iterator::is_first() {
    return tree_->get_parent() == nullptr || position() == 0;
  }

  bool iterator::is_last() {
    return tree_->get_parent() == nullptr ||
      ((position() + 1) == tree_->get_parent()->children().size());
  }

  bool iterator::operator==(const iterator& other) const {
    return root_ == other.root_ && tree_ == other.tree_;
  }

  bool iterator::operator!=(const iterator& other) const {
    return !this->operator==(other);
  }
}

#endif
