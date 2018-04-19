#ifndef BRICK_AST_BFS_ITERATOR_HPP
#define BRICK_AST_BFS_ITERATOR_HPP

#include "AST/iterator.hpp"

namespace brick::AST
{
  template <class Tree>
  class bfs_iterator : public brick::AST::iterator<Tree> {
    protected:
      using brick::AST::iterator<Tree>::tree_;
      using brick::AST::iterator<Tree>::root_;
    private:
      bool is_last();
      std::size_t position();
    public:
      bfs_iterator(Tree*, Tree*);
      bfs_iterator operator++(int);
      bfs_iterator& operator++();
      bfs_iterator operator--(int);
      bfs_iterator& operator--();
      bool operator==(const bfs_iterator&) const;
      bool operator!=(const bfs_iterator&) const;
  };

  template <class Tree>
  bfs_iterator<Tree>::bfs_iterator(Tree* tree, Tree* root)
    : brick::AST::iterator<Tree>(tree, root)
  {}

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator++(int) {
    return *this;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator++() {
    // if the current node has no children
    if (tree_->children().empty()) {
      // if this is not the last child in a vector of children
      if (!is_last()) {
        tree_ = &(tree_->get_parent()->get_child(position() + 1));
      } else {
        bfs_iterator tmp = *this;
        while (tmp.is_last()) {
          if (tmp.tree_ == this->root_) {
            this->tree_ = nullptr;
            return *this;
          }
          tmp = bfs_iterator(tmp.tree_->get_parent(), this->root_);
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
  bfs_iterator<Tree> bfs_iterator<Tree>::operator--(int) {
    return *this;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator--() {
    return *this;
  }

  template <class Tree>
  std::size_t bfs_iterator<Tree>::position() {
    if (tree_->get_parent()) {
      auto& parent_children = tree_->get_parent()->children();
      return std::distance(&*std::begin(parent_children), tree_);
    } else {
      return 0;
    }
  }

  template <class Tree>
  bool bfs_iterator<Tree>::is_last() {
    return tree_->get_parent() == nullptr ||
      ((position() + 1) == tree_->get_parent()->children().size());
  }

  template <class Tree>
  bool bfs_iterator<Tree>::operator==(const bfs_iterator<Tree>& other) const {
    return root_ == other.root_ && tree_ == other.tree_;
  }

  template <class Tree>
  bool bfs_iterator<Tree>::operator!=(const bfs_iterator<Tree>& other) const {
    return !this->operator==(other);
  }

}

#endif
