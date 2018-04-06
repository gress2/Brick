#ifndef BRICK_AST_DFS_ITERATOR_HPP
#define BRICK_AST_DFS_ITERATOR_HPP

namespace brick::AST
{
  template <class Tree>
  class dfs_iterator {
    public:
      // TODO: typedefs
      using difference_type = std::ptrdiff_t;
      using value_type = Tree;
    private:
      Tree* tree_;
    public:
      dfs_iterator();
      dfs_iterator(Tree*);
      value_type& operator*() const;
      dfs_iterator operator++(int);
      dfs_iterator& operator++();
      dfs_iterator operator--(int);
      dfs_iterator& operator--();
      dfs_iterator operator+(difference_type);
  };

  template <class Tree>
  dfs_iterator<Tree>::dfs_iterator()
    : tree_(nullptr)
  {}

  template <class Tree>
  dfs_iterator<Tree>::dfs_iterator(Tree* tree)
    : tree_(tree)
  {}

  template <class Tree>
  Tree& dfs_iterator<Tree>::operator*() const {
    return *tree_;  
  }

  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator++(int) {
    return *this; 
  }

  template <class Tree>
  dfs_iterator<Tree>& dfs_iterator<Tree>::operator++() {
    return *this;
  }
  
  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator--(int) {
    return *this;
  }

  template <class Tree>
  dfs_iterator<Tree>& dfs_iterator<Tree>::operator--() {
    return *this;
  }

  template <class Tree>
  dfs_iterator<Tree> dfs_iterator<Tree>::operator+(dfs_iterator<Tree>::difference_type diff) {
    return *this;
  } 
}

#endif
