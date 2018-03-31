#ifndef BRICK_AST_BFS_ITERATOR_HPP
#define BRICK_AST_BFS_ITERATOR_HPP

namespace brick::AST
{
  template <class Tree>
  class bfs_iterator {
    private:
      Tree* tree_;
    public:
      bfs_iterator(Tree*);
  };

  template <class Tree>
  bfs_iterator<Tree>::bfs_iterator(Tree* tree)
    : tree_(tree)
  {}

}

#endif
