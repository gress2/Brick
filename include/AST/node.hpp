#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

#include <string>

namespace brick::AST
{

class expression_node {
  public:
    virtual std::string to_string() const = 0;
    virtual short num_children() const = 0;
    virtual bool is_terminal() const = 0;
};

class unary_expression_node : public expression_node {
  public:
    short num_children() const override;
    bool is_terminal() const override;
};

short unary_expression_node::num_children() const {
  return 1;
}

bool unary_expression_node::is_terminal() const {
  return false;
}

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
    short num_children() const override;
    bool is_terminal() const override;
};

short infix_expression_node::num_children() const {
  return 2;
}

bool infix_expression_node::is_terminal() const {
  return false;
}

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
  private:
    const std::string name_;
  public:
    function_node(std::string);
    short num_children() const override;
    bool is_terminal() const override;
};

function_node::function_node(std::string name)
  : name_(name) 
{}

short function_node::num_children() const {
  return 1;
}

bool function_node::is_terminal() const {
  return false;
}

class number_node : public expression_node {
  private:
    const float num_;
  public:
    number_node(float);
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
};

number_node::number_node(float num)
  : num_(num)
{}

short number_node::num_children() const {
  return 0;  
}

bool number_node::is_terminal() const {
  return true;
}

std::string number_node::to_string() const {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return "{" + std::to_string(num_) + "}";
}

class id_node : public expression_node {
  private:
    const std::string id_;
  public:
    id_node(std::string);
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
};

id_node::id_node(std::string id) 
  : id_(id)
{}

std::string id_node::to_string() const {
  return id_;
}

short id_node::num_children() const {
  return 0;
}

bool id_node::is_terminal() const {
  return true;
}

}
#endif
