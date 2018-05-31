#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

#include <string>

namespace brick::AST
{

class expression_node {
  public:
    constexpr short num_children = 0;
    constexpr bool is_terminal = false;
    virtual std::string to_string() const = 0;
};

class unary_expression_node : public expression_node {
  public:
    constexpr short num_children = 1;
};

class posit_node : public unary_expression_node {
  public:
    std::string to_string() const override;
};

std::string posit_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{unary +}";
}

class negate_node : public expression_node {
  public:
    std::string to_string() const override;
};

std::string negate_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{unary -}";
}

class infix_expression_node : public expression_node {
  public:
    constexpr short num_children = 2;
};

class addition_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string addition_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{infix +}";
}

class subtraction_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string subtraction_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{infix -}";
}

class multiplication_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string multiplication_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{infix *}";
}

class division_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string division_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{infix /}";
}
class function_node : public expression_node {

  public:
    constexpr short num_children = 1;
};

class number_node : public expression_node {
  private:
    const float num_;
  public:
    constexpr bool is_terminal = true;
    number_node(float num);
    std::string to_string() const override;
};

number_node::number_node(float num)
  : num_(num)
{}

std::string number_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{" + std::to_string(num_) + "}";
}

class id_node : public expression_node {
  public:
    constexpr bool is_terminal = true;
};

}
#endif
