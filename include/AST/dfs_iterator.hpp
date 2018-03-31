#ifndef BRICK_AST_DFS_ITERATOR_HPP
#define BRICK_AST_DFS_ITERATOR_HPP

namespace brick::AST
{
  template <class Tree>
  class dfs_iterator {
    private:
      Tree* tree_;
    public:
      dfs_iterator(Tree*);
  };

  template <class Tree>
  dfs_iterator<Tree>::dfs_iterator(Tree* tree)
    : tree_(tree)
  {}

}

#endif
