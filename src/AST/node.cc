#include <sstream>

#include "AST/node.hpp"

namespace brick::AST
{

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
    && string_rep_ == other.string_rep_;
}

parens_node::parens_node() 
  : node(
      node_type::_parens,
      1,
      "( )",
      true,
      "(",
      ")",
      "( )"
    )
{}

brackets_node::brackets_node() 
  : node(
      node_type::_brackets,
      1,
      "[ ]",
      true,
      "[",
      "]",
      "[ ]"
    )
{}

unary_node::unary_node(std::string op, node_type nt)
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

posit_node::posit_node()
  : unary_node("+", node_type::_posit) 
{}

negate_node::negate_node()
  : unary_node("-", node_type::_negate)
{}

infix_node::infix_node(std::string op, node_type nt)
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

addition_node::addition_node() 
  : infix_node("+", node_type::_addition)
{}

subtraction_node::subtraction_node()
  : infix_node("-", node_type::_subtraction)
{}

multiplication_node::multiplication_node()
  : infix_node("*", node_type::_multiplication)
{}

division_node::division_node()
  : infix_node("/", node_type::_division)
{}

function_node::function_node(std::string name, node_type nt)
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

sin_function_node::sin_function_node() 
  : function_node("sin", node_type::_sin_function)
{}

double sin_function_node::operator()(double d) const {
  return std::sin(d);
}

cos_function_node::cos_function_node() 
  : function_node("cos", node_type::_cos_function)
{}

double cos_function_node::operator()(double d) const {
  return std::cos(d);
}

log_function_node::log_function_node() 
  : function_node("log", node_type::_log_function)
{}

double log_function_node::operator()(double d) const {
  return std::log(d);
}

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

std::string number_node::to_string() const {
  std::stringstream ss;
  ss << num_;
  return ss.str();
}

std::string number_node::get_gv_label() const {
  return to_string();
}

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