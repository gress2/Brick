#ifndef BRICK_TREE_ITERATOR_HPP
#define BRICK_TREE_ITERATOR_HPP

#include <memory>

namespace brick::tree
{
  template <class Tree>
  class iterator {
    public:
      using difference_type = std::ptrdiff_t;
      using value_type = Tree;
    protected:
      Tree* tree_;
      Tree* root_;
      bool is_first();
      bool is_last();
      std::size_t position();
    public:
      iterator(Tree*, Tree*);
      value_type& operator*() const;
      value_type* operator->() const;
      bool operator==(const iterator&) const;
      bool operator!=(const iterator&) const;
  };

  template <class Tree>
  iterator<Tree>::iterator(Tree* tree, Tree* root)
    : tree_(tree), root_(root)
  {}

  template <class Tree>
  Tree& iterator<Tree>::operator*() const {
    return *tree_;
  }

  template <class Tree>
  Tree* iterator<Tree>::operator->() const {
    return tree_;
  }

  template <class Tree>
  std::size_t iterator<Tree>::position() {
    if (tree_->get_parent()) {
      auto& parent_children = tree_->get_parent()->children();
      return std::distance(&*std::begin(parent_children), tree_);
    } else {
      return 0;
    }
  }

  template <class Tree>
  bool iterator<Tree>::is_first() {
    return tree_->get_parent() == nullptr || position() == 0;
  }

  template <class Tree>
  bool iterator<Tree>::is_last() {
    return tree_->get_parent() == nullptr ||
      ((position() + 1) == tree_->get_parent()->children().size());
  }

  template <class Tree>
  bool iterator<Tree>::operator==(const iterator<Tree>& other) const {
    return root_ == other.root_ && tree_ == other.tree_;
  }

  template <class Tree>
  bool iterator<Tree>::operator!=(const iterator<Tree>& other) const {
    return !this->operator==(other);
  }
}

#endif
