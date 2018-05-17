#ifndef BRICK_TREE_DFS_ITERATOR_HPP
#define BRICK_TREE_DFS_ITERATOR_HPP

#include "tree/iterator.hpp"

namespace brick::tree
{
  template <class Tree>
  class dfs_iterator : public brick::tree::iterator<Tree> {
    protected:
      using brick::tree::iterator<Tree>::tree_;
      using brick::tree::iterator<Tree>::root_;
    public:
      dfs_iterator(Tree*, Tree*);
      dfs_iterator operator++(int);
      dfs_iterator& operator++();
      dfs_iterator operator--(int);
      dfs_iterator& operator--();
  };

  template <class Tree>
  dfs_iterator<Tree>::dfs_iterator(Tree* tree, Tree* root)
    : brick::tree::iterator<Tree>(tree, root)
  {}

  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator++(int) {
    dfs_iterator<Tree> copy = *this;
    ++(*this);
    return copy;
  }

  template <class Tree>
  dfs_iterator<Tree>& dfs_iterator<Tree>::operator++() {
    // if the current node has no children
    if (tree_->children().empty()) {
      // if this is not the last child in a vector of children
      if (!this->is_last()) {
        tree_ = &(tree_->get_parent()->get_child(this->position() + 1));
      } else {
        dfs_iterator tmp = *this;
        while (tmp.is_last()) {
          if (tmp.tree_ == this->root_) {
            this->tree_ = nullptr;
            return *this;
          }
          tmp = dfs_iterator(tmp.tree_->get_parent(), this->root_);
        }
        tree_ = &(tmp.tree_->get_parent()->get_child(tmp.position() + 1));
      }
    } else {
      // if the current node has children
      tree_ = &(tree_->children()[0]);
    }

    return *this;
  }

  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator--(int) {
    dfs_iterator<Tree> copy = *this;
    --(*this);
    return copy;
  }

  template <class Tree>
  dfs_iterator<Tree>& dfs_iterator<Tree>::operator--() {
    // first, handle the case where the end iterator is being decremented
    if (tree_ == nullptr) {
      tree_ = root_;
      while (!tree_->children().empty()) {
        tree_ = &tree_->children()[tree_->children().size() - 1];
      } 
      return *this;
    }

    if (tree_->get_parent() != nullptr) {
      if (!this->is_first()) {
        tree_ = &(tree_->get_parent()->get_child(this->position() - 1)); 
        while (!tree_->children().empty()) {
          tree_ = &(tree_->children()[tree_->children().size() - 1]);
        }
      } else {
        tree_ = tree_->get_parent();
      } 
    }

    return *this;
  }
}

#endif
