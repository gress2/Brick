#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

#include <cmath>
#include <string>

#include "utils.hpp"

namespace brick::AST
{

class node {
  // note to self: these need to be declared virtual in order to dispatch to
  // correct derived class functions when using base class pointers
  private:
    const std::string node_id_;
  public:
    node();
    std::string get_node_id() const;
    virtual std::string to_string() const;
    virtual short num_children() const;
    virtual bool is_terminal() const;
    virtual bool wraps() const;
    virtual std::string wrap_left() const;
    virtual std::string wrap_right() const;
    virtual bool is_parens() const;
    virtual bool is_brackets() const;
    virtual bool is_unary() const;
    virtual bool is_infix() const;
    virtual bool is_posit() const;
    virtual bool is_negate() const;
    virtual bool is_addition() const;
    virtual bool is_subtraction() const;
    virtual bool is_multiplication() const;
    virtual bool is_division() const;
    virtual bool is_function() const;
    virtual bool is_number() const;
    virtual bool is_id() const;
    virtual float get_number() const;
    virtual std::string get_id() const;
    virtual double operator()(double) const;
    virtual std::string get_gv_label() const;
};

node::node() 
  : node_id_(brick::utils::random_string(8)) {}

std::string node::get_node_id() const {
  return node_id_;
}

std::string node::to_string() const {
  return "";
}

short node::num_children() const {
  return 0;
}

bool node::is_terminal() const {
  return false;
}

bool node::wraps() const {
  return false;
}

std::string node::wrap_left() const {
  return "";
}

std::string node::wrap_right() const {
  return "";
}

bool node::is_parens() const {
  return false;
}

bool node::is_brackets() const {
  return false;
}

bool node::is_unary() const {
  return false;
}

bool node::is_infix() const {
  return false;
}

bool node::is_posit() const {
  return false;
}

bool node::is_negate() const {
  return false;
}

bool node::is_addition() const {
  return false;
}

bool node::is_subtraction() const {
  return false;
}

bool node::is_multiplication() const {
  return false;
}

bool node::is_division() const {
  return false;
}

bool node::is_function() const {
  return false;
}

bool node::is_number() const {
  return false;
}

bool node::is_id() const {
  return false;
}

float node::get_number() const {
  return 0;
}

std::string node::get_id() const {
  return "";
}

double node::operator()(double d) const {
  return d;
}

std::string node::get_gv_label() const {
  return "";
}

class parens_node : public node {
  public:
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
    bool wraps() const override;
    std::string wrap_left() const override;
    std::string wrap_right() const override;
    bool is_parens() const override;
    std::string get_gv_label() const override;
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

bool parens_node::is_parens() const {
  return true;
}

std::string parens_node::get_gv_label() const {
  return "( )";
}

class brackets_node : public node {
  public:
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
    bool wraps() const override;
    std::string wrap_left() const override;
    std::string wrap_right() const override;
    bool is_brackets() const override;
    std::string get_gv_label() const override;;
};

std::string brackets_node::to_string() const {
  return "";
}

short brackets_node::num_children() const {
  return 1;
}

bool brackets_node::is_terminal() const {
  return false;
}

bool brackets_node::wraps() const {
  return true;
}

std::string brackets_node::wrap_left() const {
  return "[";
}

std::string brackets_node::wrap_right() const {
  return "]";
}

bool brackets_node::is_brackets() const {
  return true;
}

std::string brackets_node::get_gv_label() const {
  return "[ ]";
}

class unary_node : public node {
  public:
    short num_children() const override;
    bool is_terminal() const override;
    bool is_unary() const override;
};

short unary_node::num_children() const {
  return 1;
}

bool unary_node::is_terminal() const {
  return false;
}

bool unary_node::is_unary() const {
  return true;
}

class posit_node : public unary_node {
  public:
    std::string to_string() const override;
    bool is_posit() const override;
    std::string get_gv_label() const override;
};

std::string posit_node::to_string() const {
  return "+";
}

bool posit_node::is_posit() const {
  return true;
}

std::string posit_node::get_gv_label() const {
  return "+";
}

class negate_node : public unary_node {
  public:
    std::string to_string() const override;
    bool is_negate() const override;
    std::string get_gv_label() const override;
};

std::string negate_node::to_string() const {
  return "-";
}

bool negate_node::is_negate() const {
  return true;
}

std::string negate_node::get_gv_label() const {
  return "-";
}

class infix_node : public node {
  public:
    short num_children() const override;
    bool is_terminal() const override;
    bool is_infix() const override;
};

short infix_node::num_children() const {
  return 2;
}

bool infix_node::is_terminal() const {
  return false;
}

bool infix_node::is_infix() const {
  return true;
}

class addition_node : public infix_node {
  public:
    std::string to_string() const override;
    bool is_addition() const override;
    std::string get_gv_label() const override;
};

std::string addition_node::to_string() const {
  return "+";
}

bool addition_node::is_addition() const {
  return true;
}

std::string addition_node::get_gv_label() const {
  return "+";
}

class subtraction_node : public infix_node {
  public:
    std::string to_string() const override;
    bool is_subtraction() const override;
    std::string get_gv_label() const override;
};

std::string subtraction_node::to_string() const {
  return "-";
}

bool subtraction_node::is_subtraction() const {
  return true;
}

std::string subtraction_node::get_gv_label() const {
  return "-";
}

class multiplication_node : public infix_node {
  public:
    std::string to_string() const override;
    bool is_multiplication() const override;
    std::string get_gv_label() const override;
};

std::string multiplication_node::to_string() const {
  return "*";
}

bool multiplication_node::is_multiplication() const {
  return true;
}

std::string multiplication_node::get_gv_label() const {
  return "*";
}

class division_node : public infix_node {
  public:
    std::string to_string() const override;
    bool is_division() const override;
    std::string get_gv_label() const override;
};

std::string division_node::to_string() const {
  return "/";
}

bool division_node::is_division() const {
  return true;
}

std::string division_node::get_gv_label() const {
  return "/";
}

class function_node : public node {
  private:
    const std::string name_;
  public:
    function_node(std::string);
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
    bool wraps() const override;
    std::string wrap_left() const override;
    std::string wrap_right() const override;
    bool is_function() const override;
    std::string get_gv_label() const override;
};

function_node::function_node(std::string name)
  : name_(name)
{}

std::string function_node::to_string() const {
  return "";
}

short function_node::num_children() const {
  return 1;
}

bool function_node::is_terminal() const {
  return false;
}

bool function_node::wraps() const {
  return true;
}

std::string function_node::wrap_left() const {
  return name_ + "(";
}

std::string function_node::wrap_right() const {
  return ")";
}

bool function_node::is_function() const {
  return true;
}

std::string function_node::get_gv_label() const {
  return name_;
}

class sin_function_node : public function_node {
  private:
    const std::string name_;
  public:
    sin_function_node();
    double operator()(double) const override;
};

sin_function_node::sin_function_node() 
  : function_node("sin"), name_("sin") {}

double sin_function_node::operator()(double d) const {
  return std::sin(d);
}

class cos_function_node : public function_node {
  private:
    const std::string name_;
  public:
    cos_function_node();
    double operator()(double) const override;
};

cos_function_node::cos_function_node() 
  : function_node("cos"), name_("cos") {}

double cos_function_node::operator()(double d) const {
  return std::cos(d);
}

class log_function_node : public function_node {
  private:
    const std::string name_;
  public:
    log_function_node();
    double operator()(double) const override;
};

log_function_node::log_function_node() 
  : function_node("log"), name_("log") {}

double log_function_node::operator()(double d) const {
  return std::log(d);
}

class number_node : public node {
  private:
    const float num_;
  public:
    number_node(float);
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
    bool is_number() const override;
    float get_number() const override;
    std::string get_gv_label() const override;
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

bool number_node::is_number() const {
  return true;
}

float number_node::get_number() const {
  return num_;
}

std::string number_node::get_gv_label() const {
  return std::to_string(num_);
}

class id_node : public node {
  private:
    const std::string id_;
  public:
    id_node(std::string);
    std::string to_string() const override;
    short num_children() const override;
    bool is_terminal() const override;
    bool is_id() const override;
    std::string get_id() const override;
    std::string get_gv_label() const override;
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

bool id_node::is_id() const {
  return true;
}

std::string id_node::get_id() const {
  return id_;
}

std::string id_node::get_gv_label() const {
  return id_;
}

}
#endif
