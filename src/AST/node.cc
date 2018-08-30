#include <sstream>

#include "AST/node.hpp"

namespace brick
{
namespace AST
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

node* node::clone() const {
  return new node(*this);
}

std::string node::get_node_id() const {
  return node_id_;
}

void node::set_node_id(std::string id) {
  node_id_ = id;
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

bool node::is_exponentiation() const {
  return node_type_ == node_type::_exponentiation;
}

bool node::is_function() const {
  return node_type_ == node_type::_function ||
    node_type_ == node_type::_cos_function ||
    node_type_ == node_type::_sin_function ||
    node_type_ == node_type::_log_function ||
    node_type_ == node_type::_sqrt_function; 
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

node* node::copy() const {
  node* cpy = this->clone();
  cpy->set_node_id(brick::utils::random_string(8));
  return cpy;
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

node* parens_node::clone() const {
  return new parens_node(*this);
}

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

node* brackets_node::clone() const {
  return new brackets_node(*this);
}

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

node* unary_node::clone() const {
  return new unary_node(*this);
}

posit_node::posit_node()
  : unary_node("+", node_type::_posit) 
{}

node* posit_node::clone() const {
  return new posit_node(*this);
}

negate_node::negate_node()
  : unary_node("-", node_type::_negate)
{}

node* negate_node::clone() const {
  return new negate_node(*this);
}

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

node* infix_node::clone() const {
  return new infix_node(*this);
}

addition_node::addition_node() 
  : infix_node("+", node_type::_addition)
{}

node* addition_node::clone() const {
  return new addition_node(*this);
}

subtraction_node::subtraction_node()
  : infix_node("-", node_type::_subtraction)
{}

node* subtraction_node::clone() const {
  return new subtraction_node(*this);
}

multiplication_node::multiplication_node()
  : infix_node("*", node_type::_multiplication)
{}

node* multiplication_node::clone() const {
  return new multiplication_node(*this);
}

division_node::division_node()
  : infix_node("/", node_type::_division)
{}

node* division_node::clone() const {
  return new division_node(*this);
}

exponentiation_node::exponentiation_node()
  : infix_node("^", node_type::_exponentiation)
{}

node* exponentiation_node::clone() const {
  return new exponentiation_node(*this);
}

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

node* function_node::clone() const {
  return new function_node(*this);
}

double function_node::operator()(double d) const {
  return d;
}

sin_function_node::sin_function_node() 
  : function_node("sin", node_type::_sin_function)
{}

node* sin_function_node::clone() const {
  return new sin_function_node(*this);
}

double sin_function_node::operator()(double d) const {
  return std::sin(d);
}

cos_function_node::cos_function_node() 
  : function_node("cos", node_type::_cos_function)
{}

node* cos_function_node::clone() const {
  return new cos_function_node(*this);
}

double cos_function_node::operator()(double d) const {
  return std::cos(d);
}

log_function_node::log_function_node() 
  : function_node("log", node_type::_log_function)
{}

node* log_function_node::clone() const {
  return new log_function_node(*this);
}

double log_function_node::operator()(double d) const {
  return std::log(d);
}

sqrt_function_node::sqrt_function_node()
  : function_node("sqrt", node_type::_sqrt_function)
{}

node* sqrt_function_node::clone() const {
  return new sqrt_function_node(*this);
}

double sqrt_function_node::operator()(double d) const {
  return std::sqrt(d);
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

node* number_node::clone() const {
  return new number_node(*this);
}

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

node* id_node::clone() const {
  return new id_node(*this);
}

std::string id_node::get_id() const {
  return id_;
}
}
}
