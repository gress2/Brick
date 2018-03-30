#ifndef BRICK_AST_TREE_HPP_
#define BRICK_AST_TREE_HPP_

#include <iostream>
#include <memory>
#include <vector>

namespace Brick::AST
{

class Tree {
private:
  std::string data_; // TODO: not strings
  std::vector<Tree> children_;
public:
  Tree(std::string);
  void print();
  void set_children(std::vector<Tree>);
  const std::string& get_data() const;
  const std::vector<Tree>& get_children() const;
  bool operator==(const Tree&) const;
  ~Tree() = default;
};

Tree::Tree(std::string data) : data_(data) {}

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
