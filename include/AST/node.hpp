#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

#include <cmath>
#include <string>

#include "utils.hpp"

namespace brick::AST
{

enum node_type {
  _node,
  _parens,
  _brackets,
  _unary,
  _infix,
  _posit,
  _negate,
  _addition,
  _subtraction,
  _multiplication,
  _division,
  _function,
  _sin_function,
  _cos_function,
  _log_function,
  _number,
  _id
};

class node {
  private:
    const std::string node_id_;
    const node_type node_type_;
    const short num_children_;
    const std::string string_rep_;
    const bool wraps_;
    const std::string wrap_left_;
    const std::string wrap_right_;
    const std::string gv_label_;
  public:
    node(
      node_type nt = node_type::_node, 
      short num_children = 0,
      std::string string_rep = "",
      bool wraps = false,
      std::string wrap_left = "",
      std::string wrap_right = "",
      std::string gv_label = ""
    );
    std::string get_node_id() const;
    std::string to_string() const;
    node_type get_node_type() const;
    short num_children() const;
    bool is_terminal() const;
    bool wraps() const;
    std::string wrap_left() const;
    std::string wrap_right() const;
    bool is_parens() const;
    bool is_brackets() const;
    bool is_unary() const;
    bool is_infix() const;
    bool is_posit() const;
    bool is_negate() const;
    bool is_addition() const;
    bool is_subtraction() const;
    bool is_multiplication() const;
    bool is_division() const;
    bool is_function() const;
    bool is_number() const;
    bool is_id() const;
    std::string get_gv_label() const;
    bool operator==(const node&);
    virtual ~node();
};

node::node(node_type nt, short num_children, std::string string_rep,
  bool wraps, std::string wrap_left, std::string wrap_right, std::string gv_label)
  : node_id_(brick::utils::random_string(8)),
    node_type_(nt),
    num_children_(num_children),
    string_rep_(string_rep),
    wraps_(wraps),
    wrap_left_(wrap_left),
    wrap_right_(wrap_right),
    gv_label_(gv_label)
{}

node::~node() {}

std::string node::get_node_id() const {
  return node_id_;
}

std::string node::to_string() const {
  return string_rep_;
}

node_type node::get_node_type() const {
  return node_type_;
}

short node::num_children() const {
  return num_children_;
}

bool node::is_terminal() const {
  return num_children_ == 0;
}

bool node::wraps() const {
  return wraps_;
}

std::string node::wrap_left() const {
  return wrap_left_;
}

std::string node::wrap_right() const {
  return wrap_right_;
}

bool node::is_parens() const {
  return node_type_ == node_type::_parens;
}

bool node::is_brackets() const {
  return node_type_ == node_type::_brackets;
}

bool node::is_unary() const {
  return node_type_ == node_type::_unary;
}

bool node::is_infix() const {
  return node_type_ == node_type::_infix;
}

bool node::is_posit() const {
  return node_type_ == node_type::_posit;
}

bool node::is_negate() const {
  return node_type_ == node_type::_negate;
}

bool node::is_addition() const {
  return node_type_ == node_type::_addition;
}

bool node::is_subtraction() const {
  return node_type_ == node_type::_subtraction;
}

bool node::is_multiplication() const {
  return node_type_ == node_type::_multiplication;
}

bool node::is_division() const {
  return node_type_ == node_type::_division;
}

bool node::is_function() const {
  return node_type_ == node_type::_function ||
    node_type_ == node_type::_cos_function ||
    node_type_ == node_type::_sin_function ||
    node_type_ == node_type::_log_function;
}

bool node::is_number() const {
  return node_type_ == node_type::_number;
}

bool node::is_id() const {
  return node_type_ == node_type::_id;
}

std::string node::get_gv_label() const {
  return gv_label_;
}

bool node::operator==(const node& other) {
  return node_type_ == other.get_node_type()
    && string_rep_ == other.to_string();
}

class parens_node : public node {
  public:
    parens_node();
};

parens_node::parens_node() 
  : node(
      node_type::_parens,
      1,
      "",
      true,
      "(",
      ")",
      "( )"
    )
{}

class brackets_node : public node {
  public:
    brackets_node();
};

brackets_node::brackets_node() 
  : node(
      node_type::_brackets,
      1,
      "",
      true,
      "[",
      "]",
      "[ ]"
    )
{}

class unary_node : public node {
  public:
    unary_node(std::string, node_type);
};

unary_node::unary_node(std::string op, node_type nt = node_type::_unary)
  : node(
    nt,
    1,
    op,
    false,
    "",
    "",
    op
  )
{}

class posit_node : public unary_node {
  public:
    posit_node();
};

posit_node::posit_node()
  : unary_node("+", node_type::_posit) 
{}

class negate_node : public unary_node {
  public:
    negate_node();
};

negate_node::negate_node()
  : unary_node("-", node_type::_negate)
{}

class infix_node : public node {
  public:
    infix_node(std::string, node_type);
};

infix_node::infix_node(std::string op, node_type nt = node_type::_infix)
  : node (
    nt,
    2,
    op,
    false,
    "",
    "",
    op
  )
{}

class addition_node : public infix_node {
  public:
    addition_node();
};

addition_node::addition_node() 
  : infix_node("+", node_type::_addition)
{}

class subtraction_node : public infix_node {
  public:
    subtraction_node();
};

subtraction_node::subtraction_node()
  : infix_node("-", node_type::_subtraction)
{}

class multiplication_node : public infix_node {
  public:
    multiplication_node();
};

multiplication_node::multiplication_node()
  : infix_node("*", node_type::_multiplication)
{}

class division_node : public infix_node {
  public:
    division_node();
};

division_node::division_node()
  : infix_node("/", node_type::_division)
{}

class function_node : public node {
  private:
    const std::string name_;
  public:
    function_node(std::string, node_type);
    virtual double operator()(double) const;
};

function_node::function_node(std::string name, node_type nt = node_type::_function)
  : node (
      nt,
      1,
      name,
      true,
      name + "(",
      ")",
      name
    ),
    name_(name)
{}

double function_node::operator()(double d) const {
  return d;
}

class sin_function_node : public function_node {
  public:
    sin_function_node();
    double operator()(double) const override;
};

sin_function_node::sin_function_node() 
  : function_node("sin", node_type::_sin_function)
{}

double sin_function_node::operator()(double d) const {
  return std::sin(d);
}

class cos_function_node : public function_node {
  public:
    cos_function_node();
    double operator()(double) const override;
};

cos_function_node::cos_function_node() 
  : function_node("cos", node_type::_cos_function)
{}

double cos_function_node::operator()(double d) const {
  return std::cos(d);
}

class log_function_node : public function_node {
  public:
    log_function_node();
    double operator()(double) const override;
};

log_function_node::log_function_node() 
  : function_node("log", node_type::_log_function)
{}

double log_function_node::operator()(double d) const {
  return std::log(d);
}

class number_node : public node {
  private:
    const float num_;
  public:
    number_node(float);
    float get_number() const;
};

number_node::number_node(float num)
  : node (
      node_type::_number,
      0,
      std::to_string(num),
      false,
      "",
      "",
      std::to_string(num)
    ),
    num_(num)
{}

float number_node::get_number() const {
  return num_;
}

class id_node : public node {
  private:
    const std::string id_;
  public:
    id_node(std::string);
    std::string get_id() const;
};

id_node::id_node(std::string id)
  : node (
      node_type::_id,
      0,
      id,
      false,
      "",
      "",
      id
    ),
    id_(id)
{}

std::string id_node::get_id() const {
  return id_;
}

}
#endif
