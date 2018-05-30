#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

namespace brick::AST
{

class expression_node {
  public:
    static constexpr short num_children = 0;
    static constexpr bool is_terminal = false;
};

class unary_expression_node : public expression_node {
  public:
    static constexpr short num_children = 1;
};
class posit_node : public unary_expression_node {};
class negate_node : public expression_node {};

class infix_expression_node : public expression_node {
  public:
    static constexpr short num_children = 2;
};
class addition_node : public infix_expression_node {};
class subtraction_node : public infix_expression_node {};
class multiplication_node : public infix_expression_node {};
class division_node : public infix_expression_node {};

class function_node : public expression_node {
  public:
    static constexpr short num_children = 1;
};

class number_node : public expression_node {
  public:
    static constexpr bool is_terminal = true;
};

class id_node : public expression_node {
  public:
    static constexpr bool is_terminal = true;
};

}
#endif
