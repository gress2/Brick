#ifndef BRICK_TREE_TREE_HPP_
#define BRICK_TREE_TREE_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "tree/hashed.hpp"
#include "tree/bfs_iterator.hpp"
#include "tree/dfs_iterator.hpp"

namespace brick::tree
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
    // construction
    explicit tree(value_type, tree* = nullptr);
    // access
    constexpr value_type get_value() const;
    constexpr hashed_type get_hashed() const noexcept;
    constexpr tree* get_parent() const noexcept;
    children_type& children();
    const children_type& children() const;
    bool has_children() const;
    tree& get_child(std::size_t);
    const tree& get_child(std::size_t) const;
    std::size_t get_level() const;
    // modifiers
    void set_hashed(hashed_type) noexcept;
    void set_value(const value_type&);
    void set_value(value_type&&);
    void set_parent(tree*) noexcept;
    tree& add_child(tree);
    tree& add_child(const T&);
    tree& add_child(T&&);
    // iterators
    dfs_iterator_type begin_dfs();
    dfs_iterator_type end_dfs();
    bfs_iterator_type begin_bfs();
    bfs_iterator_type end_bfs();
    // operators
    bool operator==(const tree& other) const;
    // misc
    std::string to_string() const;
};

template <class T, template <class...> class C>
tree<T, C>::tree(value_type value, tree<T, C>* parent)
  : parent_(parent), hashed_(hashed_type(value))
{}

template <class T, template <class...> class C>
constexpr typename tree<T, C>::value_type tree<T, C>::get_value() const {
  return static_cast<value_type>(hashed_);
}

template <class T, template <class...> class C>
constexpr typename tree<T, C>::hashed_type tree<T, C>::get_hashed() const noexcept {
  return hashed_;
}

template <class T, template <class...> class C>
constexpr tree<T, C>* tree<T, C>::get_parent() const noexcept {
  return parent_;
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
bool tree<T, C>::has_children() const {
  return children_.size() > 0;
}

template <class T, template <class...> class C>
tree<T, C>& tree<T, C>::get_child(std::size_t idx) {
  return children_[idx];
}

template <class T, template <class...> class C>
const tree<T, C>& tree<T, C>::get_child(std::size_t idx) const {
  return children_[idx];
}

template <class T, template <class...> class C>
std::size_t tree<T, C>::get_level() const {
  std::size_t level = 0;
  auto* tmp = this;
  while(tmp->get_parent() != nullptr) {
    tmp = tmp->get_parent();
    level++;
  }
  return level;
}

template <class T, template <class...> class C>
void tree<T, C>::set_hashed(tree<T, C>::hashed_type hashed) noexcept {
  hashed_ = hashed;
}

template <class T, template <class...> class C>
void tree<T, C>::set_value(tree<T, C>::value_type&& value) {
  hashed_ = std::move(value);
}

template <class T, template <class...> class C>
void tree<T, C>::set_value(const tree<T, C>::value_type& value) {
  hashed_ = value;
}

template <class T, template <class...> class C>
void tree<T, C>::set_parent(tree<T, C>* parent) noexcept {
  parent_ = parent;
}

template <class T, template <class...> class C>
tree<T, C>& tree<T, C>::add_child(tree<T, C> child) {
  child.set_parent(this);
  children_.push_back(child);
  return *this;
}

template <class T, template <class...> class C>
tree<T, C>& tree<T, C>::add_child(const T& child_value) {
  children_.push_back(tree{child_value, this});
  return *this;
}

template <class T, template <class...> class C>
tree<T, C>& tree<T, C>::add_child(T&& child_value) {
  children_.push_back(tree{std::move(child_value), this});
  return *this;
}

template <class T, template <class...> class C>
typename tree<T, C>::dfs_iterator_type tree<T, C>::begin_dfs() {
  return dfs_iterator_type(this, this);
}

template <class T, template <class...> class C>
typename tree<T, C>::dfs_iterator_type tree<T, C>::end_dfs() {
  return dfs_iterator_type(nullptr, this);
}

template <class T, template <class...> class C>
typename tree<T, C>::bfs_iterator_type tree<T, C>::begin_bfs() {
  return bfs_iterator_type(this, this);
}

template <class T, template <class...> class C>
typename tree<T, C>::bfs_iterator_type tree<T, C>::end_bfs() {
  return bfs_iterator_type(nullptr, this);
}

template <class T, template <class...> class C>
bool tree<T, C>::operator==(const tree<T, C>& other) const {
  if (get_value() != other.get_value()) {
    return false;
  }
  return children() == other.children();
}

// TODO: this only works for two children
template <class T, template <class...> class C>
std::string tree<T, C>::to_string() const {
  std::ostringstream stream;
  if (children().size() > 0) {
    stream << children()[0].to_string();
  }
  stream << get_value();
  if (children().size() > 1){
    stream << children()[1].to_string();
  }
  return stream.str();
}

}

#endif
