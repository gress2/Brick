#ifndef BRICK_AST_NODE_HPP_
#define BRICK_AST_NODE_HPP_

namespace brick::AST
{

class expression_node {};

class infix_expression_node : public expression_node {};

class addition_node : public infix_expression_node {};

class subtraction_node : public infix_expression_node {};

class multiplication_node : public infix_expression_node {};

class division_node : public infix_expression_node {};

class negate_node : public expression_node {};

class function_node : public expression_node {};

class number_node : public expression_node {};

class id_node : public expression_node {};

}

#endif
