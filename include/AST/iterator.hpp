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
    private:
      Tree* tree_;
    public:
      iterator();
      iterator(Tree*);
      value_type& operator*() const;
  };

  template <class Tree>
  iterator<Tree>::iterator()
    : tree_(nullptr)
  {}

  template <class Tree>
  iterator<Tree>::iterator(Tree* tree)
    : tree_(tree)
  {}

  template <class Tree>
  Tree& iterator<Tree>::operator*() const {
    return *tree_;
  }
}

#endif
