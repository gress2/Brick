#ifndef BRICK_TREE_BFS_ITERATOR_HPP
#define BRICK_TREE_BFS_ITERATOR_HPP

#include <queue>

#include "tree/iterator.hpp"

namespace brick::tree
{
  template <class Tree>
  class bfs_iterator : public brick::tree::iterator<Tree> {
    protected:
      using brick::tree::iterator<Tree>::tree_;
      using brick::tree::iterator<Tree>::root_;
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
    : brick::tree::iterator<Tree>(tree, root)
  {}

  template <class Tree>
  bfs_iterator<Tree> bfs_iterator<Tree>::operator++(int) {
    bfs_iterator<Tree> copy = *this;
    ++(*this);
    return copy;
  }

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
