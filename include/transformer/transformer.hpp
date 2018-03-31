#ifndef BRICK_TRANSFORMER_TRANSFORMER_HPP_
#define BRICK_TRANSFORMER_TRANSFORMER_HPP_

namespace brick::transformer
{

template <class Tree, class TreeBase>
class transformer {
  private:
    Tree& tree_;
    TreeBase& tree_base_;
  public:
    transformer(Tree&, TreeBase&);
};

template <class T, class B>
transformer<T, B>::transformer(T& tree, B& tbase)
  : tree_(tree), tree_base_(tbase)
{}

}

#endif
