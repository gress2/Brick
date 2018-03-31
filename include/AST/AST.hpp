#ifndef BRICK_AST_TREE_HPP_
#define BRICK_AST_TREE_HPP_

#include <iostream>
#include <memory>
#include <vector>

namespace brick::AST
{

class tree {
  private:
    std::string data_; // TODO: not strings
    std::vector<tree> children_;
  public:
    tree(std::string);
    void print();
    void set_children(std::vector<Tree>);
    const std::string& get_data() const;
    const std::vector<Tree>& get_children() const;
    bool operator==(const Tree&) const;
    ~Tree() = default;
};

template <class T, template <class...> class children = std::vector>
class tree {
  private:
    tree* parent_;
    children_type children_;
    key_type key_;
  public:
    using children_type = children<tree<T, children>>;
    using value_type = T;
    using key_type = key<T>;
    using dfs_iterator_type = dfs_iterator<tree>; 
    using bfs_iterator_type = bfs_iterator<tree>;
    explicit tree(tree*, value_type);
    tree(tree&&) = default;
    tree& operator=(tree&&) = default;
    constexpr key_type get_key() const noexcept;
    void set_key(key_type) noexcept;
    constexpr value_type get_value() const;
    void set_value(const value_type&);
    constexpr tree* get_parent() const noexcept;
    void set_parent(tree*) noexcept;
    children_type& children();
    const children_type& children() const;
    dfs_iterator_type begin_dfs();
    dfs_iterator_type end_dfs();
    bfs_iterator_type begin_dfs();
    bfs_iterator_type end_dfs();
};

template <class T, template <class...> class C>
typename tree::tree(tree* parent, value_type value)
  : parent_(parent), key_(key_type(value)) 
{}

template <class T, template <class...> class C>
constexpr tree::key_type tree::get_key() const noexcept {
  return key_; 
}

template <class T, template <class...> class C>
void tree::set_key(tree::key_type key) noexcept {
  key_ = key;
}

template <class T, template <class...> class C>
constexpr tree::value_type tree::get_value() const {
  return static_cast<value_type>(key_);
}

template <class T, template <class...> class C>
void tree::set_value(const tree::value_type& value) {
  key_ = tree::key_type(value);
}

template <class T, template <class...> class C>
constexpr tree* tree::get_parent() const noexcept {
  return parent_;
}

template <class T, template <class...> class C>
void tree::set_parent(tree* parent) noexcept {
  parent_ = parent;
} 

template <class T, template <class...> class C>
tree::children_type& tree::children() {
  return children_;
}

template <class T, template <class...> class C>
const tree::children_type& children() const {
  return children_;
}

template <class T, template <class...> class C>
tree::dfs_iterator_type tree::begin_dfs() {

}

template <class T, template <class...> class C>
tree::dfs_iterator_type tree::end_dfs() {

}

template <class T, template <class...> class C>
tree::bfs_iterator_type tree::begin_bfs() {

}

template <class T, template <class...> class C>
tree::bfs_iterator_type tree::end_bfs() {

}

// TODO: make good
void Tree::print() {
  std::cout << data_ << std::endl;
  for (auto& child : children_) {
    child.print();
  } 
}

void Tree::set_children(std::vector<Tree> children) {
  children_ = children;
}

const std::string& Tree::get_data() const {
  return data_;
}

const std::vector<Tree>& Tree::get_children() const {
  return children_;
}

bool Tree::operator==(const Tree& other) const {
  if (get_data() != other.get_data()) {
    return false;
  }

  return get_children() == other.get_children();  
}

}

#endif
