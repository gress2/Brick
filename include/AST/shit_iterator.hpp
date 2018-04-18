#ifndef BRICK_AST_SHIT_ITERATOR_HPP
#define BRICK_AST_SHIT_ITERATOR_HPP

#include "AST/iterator.hpp"

namespace brick::AST
{
  template <class Tree>
  class shiterator : public brick::AST::iterator<Tree> {
    protected:
      using brick::AST::iterator<Tree>::tree_;
    private:
      bool is_last();
      std::size_t position();
    public:
      shiterator(Tree*);
      shiterator operator++(int);
      shiterator& operator++();
      shiterator operator--(int);
      shiterator& operator--();
  };

  template <class Tree>
  shiterator<Tree>::shiterator(Tree* tree)
    : brick::AST::iterator<Tree>(tree)
  {}

  template <class Tree>
  shiterator<Tree> shiterator<Tree>::operator++(int) {
    return *this;
  }

  template <class Tree>
  shiterator<Tree>& shiterator<Tree>::operator++() {
    // if the current node has no children
    if (tree_->children().empty()) {
      // if this is not the last child in a vector of children
      if (!is_last()) {
        tree_ = &(tree_->get_parent()->children()[position() + 1]); 
      } else {
        shiterator tmp = *this;
        while (tmp.is_last()) {
          tmp = shiterator(tmp.tree_->get_parent());
        } 
        tree_ = &(tmp.tree_->get_parent()->children()[tmp.position() + 1]);
      }
    } else {
      // if the current node has children
      tree_ = &(tree_->children()[0]);
    }

    return *this;
  }

  template <class Tree>
  shiterator<Tree> shiterator<Tree>::operator--(int) {
    return *this;
  }

  template <class Tree>
  shiterator<Tree>& shiterator<Tree>::operator--() {
    return *this;
  }

  template <class Tree>
  std::size_t shiterator<Tree>::position() {
    if (tree_->get_parent()) {
      auto& parent_children = tree_->get_parent()->children();
      return std::distance(&*std::begin(parent_children), tree_);
      // return std::find(std::begin(parent_children), std::end(parent_children), tree_);
    } else {
      return 0;
    }
  }

  template <class Tree>
  bool shiterator<Tree>::is_last() {
    return ((position() + 1) == tree_->get_parent()->children().size());
  }
}

#endif
