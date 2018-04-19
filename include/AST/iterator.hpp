#ifndef BRICK_AST_ITERATOR_HPP
#define BRICK_AST_ITERATOR_HPP

#include <memory>

namespace brick::AST
{
  template <class Tree>
  class iterator {
    public:
      // TODO: typedefs
      using difference_type = std::ptrdiff_t;
      using value_type = Tree;
    protected:
      Tree* tree_;
      Tree* root_;
    public:
      iterator(Tree*, Tree*);
      value_type& operator*() const;
      value_type* operator->() const;
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

}

#endif
