#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

#include <string>

namespace brick::AST
{

class expression_node {
  // note to self: these need to be declared virtual in order to dispatch to
  // correct derived class functions when using base class pointers
  public:
    virtual std::string to_string() const;
    virtual short num_children() const;
    virtual bool is_terminal() const;
    virtual bool wraps() const;
    virtual std::string wrap_left() const;
    virtual std::string wrap_right() const;
};

std::string expression_node::to_string() const {
  return "";
}

short expression_node::num_children() const {
  return 0;
}

bool expression_node::is_terminal() const {
  return false;
}

bool expression_node::wraps() const {
  return false;
}

std::string expression_node::wrap_left() const {
  return "";
}

std::string expression_node::wrap_right() const {
  return "";
}

class parens_node : public expression_node {
  public:
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
    bool wraps() const override;
    std::string wrap_left() const override;
    std::string wrap_right() const override;
};

std::string parens_node::to_string() const {
  return "";
}

short parens_node::num_children() const {
  return 1;
}

bool parens_node::is_terminal() const {
  return false;
}

bool parens_node::wraps() const {
  return true;
}

std::string parens_node::wrap_left() const {
  return "(";
}

std::string parens_node::wrap_right() const {
  return ")";
}

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
  return "+";
}

class negate_node : public unary_expression_node {
  public:
    std::string to_string() const override;
};

std::string negate_node::to_string() const {
  return "-";
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
  return "+";
}

class subtraction_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string subtraction_node::to_string() const {
  return "-";
}

class multiplication_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string multiplication_node::to_string() const {
  return "*";
}

class division_node : public infix_expression_node {
  public:
    std::string to_string() const override;
};

std::string division_node::to_string() const {
  return "/";
}

class function_node : public expression_node {
  private:
    const std::string name_;
  public:
    function_node(std::string);
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
};

function_node::function_node(std::string name)
  : name_(name)
{}

std::string function_node::to_string() const {
  return name_;
}

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
  return std::to_string(num_);
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
