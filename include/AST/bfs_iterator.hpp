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
    public:
      bfs_iterator(Tree*, Tree*);
      bfs_iterator operator++(int);
      bfs_iterator& operator++();
      bfs_iterator operator--(int);
      bfs_iterator& operator--();
  };

  template <class Tree>
  bfs_iterator<Tree>::bfs_iterator(Tree* tree, Tree* root)
    : brick::AST::iterator<Tree>(tree, root)
  {}

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator++(int) {
    bfs_iterator<Tree> copy = *this;
    ++(*this);
    return copy;
  }

  template <class Tree>
  Tree* bfs_iterator<Tree>::probe() {
    // if possible probe right
    
    // start from lhs 
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator++() {
    if (tree_ == root_) {
      tree_ = &(tree_->children()[0]);
      return *this;
    }
    if (!is_last()) {
      tree_ = &(tree_->get_parent()->children()[position() + 1]);
      return *this;
    } else {
      bfs_iterator tmp = *this;
      std::size_t levels_up = 0;
      std::size_t cur_pos = tmp.position();
      while (tmp.is_last() && tmp.get_parent() != root_) {
        cur_pos = tmp.position();
        tmp = bfs_iterator(tmp.get_parent(), root_); 
        levels_up++;
      }
      std::size_t target_depth = levels_up;
      // we either hit root or we can go right
      // if we're root, check if we came up from its right most child
      if (cur_pos == tmp.children().size() - 1) {
        // right-most, so we're searching for something deeper
        target_depth++;
      }
      
       
    }
  }

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator--(int) {
    bfs_iterator<Tree> copy = *this;
    --(*this);
    return copy;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator--() {
    // first, handle the case where the end iterator is being decremented
    if (tree_ == nullptr) {
      tree_ = root_;
      while (!tree_->children().empty()) {
        tree_ = &tree_->children()[tree_->children().size() - 1];
      } 
      return *this;
    }
    return *this;
  }
}

#endif
