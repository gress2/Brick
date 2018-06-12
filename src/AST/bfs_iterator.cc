#include <queue>

#include "AST/AST.hpp"
#include "AST/bfs_iterator.hpp"

namespace brick::AST
{
  bfs_iterator::bfs_iterator(brick::AST::AST* cur, brick::AST::AST* root)
    : brick::AST::iterator(cur, root)
  {}

  bfs_iterator& bfs_iterator::operator++() {
    auto trav = this->traversal();
    AST* next = nullptr;
    bool up_next = false;

    for (auto it = trav.begin(); it != trav.end(); ++it) {
      if (up_next) {
        next = *it;
        break;
      }
      if (*it == this->cur_) {
        up_next = true;
      }
    }
    this->cur_ = next;
    return *this;
  }

  bfs_iterator bfs_iterator::operator++(int) {
    bfs_iterator copy = *this;
    ++(*this);
    return copy;
  }

  bfs_iterator& bfs_iterator::operator--() {
    auto trav = this->traversal();

    if (this->cur_ == nullptr) {
      this->cur_ = trav[trav.size() - 1];
      return *this;
    }

    AST* next = this->root_;
    bool up_next = false;
    for (auto it = trav.rbegin(); it != trav.rend(); ++it) {
      if (up_next) {
        next = *it;
        break;
      }
      if (*it == this->cur_) {
        up_next = true;
      }
    }

    this->cur_ = next;
    return *this;
  }

  bfs_iterator bfs_iterator::operator--(int) {
    bfs_iterator copy = *this;
    --(*this);
    return copy;
  }

  std::vector<AST*> bfs_iterator::traversal() {
    std::vector<AST*> ordering;
    std::queue<AST*> q;
    AST* traverse;

    q.push(this->root_);

    while (!q.empty()) {
      traverse = q.front();
      ordering.push_back(traverse);
      q.pop();

      auto& children = traverse->get_children();
      for (auto it = children.begin(); it != children.end(); ++it) {
        q.push(it->get());
      }
    }
    return ordering;
  }
}