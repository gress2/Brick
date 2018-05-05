#ifndef BRICK_AST_BFS_ITERATOR_HPP
#define BRICK_AST_BFS_ITERATOR_HPP

#include <queue>

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
    private:
      std::vector<Tree*> traversal();
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

  /*
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
    } if (!is_last()) {
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
    */

  template <class Tree>
  std::vector<Tree*> bfs_iterator<Tree>::traversal() {
    std::vector<Tree*> ordering;
    std::queue<Tree*> q;
    Tree* traverse;
    
    q.push(this->root_);

    while (!q.empty()) {
      traverse = q.front();
      ordering.push_back(traverse);
      q.pop();
     
      auto& children = traverse->children();
      for (auto it = children.begin(); it != children.end(); ++it) {
        auto& child = *it;
        q.push(&child);
      }
    }
    return ordering;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator++() {
    auto trav = this->traversal(); 
    Tree* next = nullptr;
    bool upNext = false;
    for (auto it = trav.begin(); it != trav.end(); ++it) {
      if (upNext) {
        next = *it;
        break;
      }
      if (*it == this->tree_) {
        upNext = true; 
      }
    }
    
    this->tree_ = next;
    return *this;
  }
  

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator--(int) {
    bfs_iterator<Tree> copy = *this;
    --(*this);
    return copy;
  }

  template <class Tree>
  bfs_iterator<Tree>& bfs_iterator<Tree>::operator--() {
    auto trav = this->traversal(); 

    if (this->tree_ == nullptr) {
      this->tree_ = trav[trav.size() - 1];
      return *this; 
    }

    Tree* next = this->root_;
    bool upNext = false;
    for (auto it = trav.rbegin(); it != trav.rend(); ++it) {
      if (upNext) {
        next = *it;
        break;
      }
      if (*it == this->tree_) {
        upNext = true; 
      }
    }
  
    this->tree_ = next;
    return *this;
  }

}

#endif
