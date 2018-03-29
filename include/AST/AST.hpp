#ifndef BRICK_AST_AST_HPP_
#define BRICK_AST_AST_HPP_

#include <iostream>
#include <memory>
#include <vector>

namespace Brick::AST
{

class AST {
private:
  std::string data_; // TODO: not strings
  std::vector<std::unique_ptr<AST>> children_;
public:
  AST();
  void print();
};

AST::AST() : data_("") {}

// TODO: not DFS
void AST::print() {
  std::cout << data_ << std::endl;
  for (auto& child : children_) {
    child->print();
  } 
}

}

#endif
