#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

#include <cmath>
#include <string>

#include "utils/utils.hpp"

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
    virtual std::string to_string() const;
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
    virtual std::string get_gv_label() const;
    bool operator==(const node&);
    virtual node* clone() const;
    virtual ~node();
};

class parens_node : public node {
  public:
    parens_node();
    node* clone() const override;
};

class brackets_node : public node {
  public:
    brackets_node();
    node* clone() const override;
};

class unary_node : public node {
  public:
    unary_node(std::string, node_type = node_type::_unary);
    node* clone() const override;
};

class posit_node : public unary_node {
  public:
    posit_node();
    node* clone() const override;
};

class negate_node : public unary_node {
  public:
    negate_node();
    node* clone() const override;
};

class infix_node : public node {
  public:
    infix_node(std::string, node_type = node_type::_infix);
    node* clone() const override;
};

class addition_node : public infix_node {
  public:
    addition_node();
    node* clone() const override;
};

class subtraction_node : public infix_node {
  public:
    subtraction_node();
    node* clone() const override;
};

class multiplication_node : public infix_node {
  public:
    multiplication_node();
    node* clone() const override;
};

class division_node : public infix_node {
  public:
    division_node();
    node* clone() const override;
};

class function_node : public node {
  private:
    const std::string name_;
  public:
    function_node(std::string, node_type = node_type::_function);
    virtual double operator()(double) const;
    node* clone() const override;
};

class sin_function_node : public function_node {
  public:
    sin_function_node();
    double operator()(double) const override;
    node* clone() const override;
};

class cos_function_node : public function_node {
  public:
    cos_function_node();
    double operator()(double) const override;
    node* clone() const override;
};

class log_function_node : public function_node {
  public:
    log_function_node();
    double operator()(double) const override;
    node* clone() const override;
};

class number_node : public node {
  private:
    const float num_;
  public:
    number_node(float);
    float get_number() const;
    std::string to_string() const override;
    std::string get_gv_label() const override;
    node* clone() const override;
};

class id_node : public node {
  private:
    const std::string id_;
  public:
    id_node(std::string);
    std::string get_id() const;
    node* clone() const override;
};

}
#endif
