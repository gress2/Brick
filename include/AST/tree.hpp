#ifndef BRICK_AST_TREE_HPP_
#define BRICK_AST_TREE_HPP_

#include <iostream>
#include <memory>
#include <vector>

#include "AST/hashed.hpp"
#include "AST/bfs_iterator.hpp"
#include "AST/dfs_iterator.hpp"

namespace brick::AST
{

template <class T, template <class...> class Children = std::vector>
class tree {
  public:
    using children_type = Children<tree<T, Children>>;
    using value_type = T;
    using hashed_type = hashed<T>;
    using dfs_iterator_type = dfs_iterator<tree>;
    using bfs_iterator_type = bfs_iterator<tree>;
  private:
    children_type children_;
    tree* parent_;
    hashed_type hashed_;
  public:
    explicit tree(tree*, value_type);
    tree(tree&&) = default;
    tree& operator=(tree&&) = default;
    constexpr hashed_type get_hashed() const noexcept;
    void set_hashed(hashed_type) noexcept;
    constexpr value_type get_value() const;
    void set_value(const value_type&);
    constexpr tree* get_parent() const noexcept;
    void set_parent(tree*) noexcept;
    children_type& children();
    const children_type& children() const;
    dfs_iterator_type begin_dfs();
    dfs_iterator_type end_dfs();
    bfs_iterator_type begin_bfs();
    bfs_iterator_type end_bfs();
    bool operator==(const tree& other) const;
};

template <class T, template <class...> class C>
tree<T, C>::tree(tree<T, C>* parent, value_type value)
  : parent_(parent), hashed_(hashed_type(value))
{}

template <class T, template <class...> class C>
constexpr typename tree<T, C>::hashed_type tree<T, C>::get_hashed() const noexcept {
  return hashed_;
}

template <class T, template <class...> class C>
void tree<T, C>::set_hashed(tree<T, C>::hashed_type hashed) noexcept {
  hashed_ = hashed;
}

template <class T, template <class...> class C>
constexpr typename tree<T, C>::value_type tree<T, C>::get_value() const {
  return static_cast<value_type>(hashed_);
}

template <class T, template <class...> class C>
void tree<T, C>::set_value(const tree<T, C>::value_type& value) {
  hashed_ = value;
}

template <class T, template <class...> class C>
constexpr tree<T, C>* tree<T, C>::get_parent() const noexcept {
  return parent_;
}

template <class T, template <class...> class C>
void tree<T, C>::set_parent(tree<T, C>* parent) noexcept {
  parent_ = parent;
}

template <class T, template <class...> class C>
typename tree<T, C>::children_type& tree<T, C>::children() {
  return children_;
}

template <class T, template <class...> class C>
const typename tree<T, C>::children_type& tree<T, C>::children() const {
  return children_;
}

template <class T, template <class...> class C>
typename tree<T, C>::dfs_iterator_type tree<T, C>::begin_dfs() {
  return dfs_iterator_type(this);
}

template <class T, template <class...> class C>
typename tree<T, C>::dfs_iterator_type tree<T, C>::end_dfs() {
  return dfs_iterator_type(this);
}

template <class T, template <class...> class C>
typename tree<T, C>::bfs_iterator_type tree<T, C>::begin_bfs() {
  return bfs_iterator_type(this);
}

template <class T, template <class...> class C>
typename tree<T, C>::bfs_iterator_type tree<T, C>::end_bfs() {
  return bfs_iterator_type(this);
}

template <class T, template <class...> class C>
bool tree<T, C>::operator==(const tree<T, C>& other) const {
  if (get_value() != other.get_value()) {
    return false;
  }
  return children() == other.children();
}

}

#endif
