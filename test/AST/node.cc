#include "brick.hpp"
#include "gtest/gtest.h"

TEST(Node, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_node);
  ASSERT_TRUE(node->num_children() == 0);
  ASSERT_TRUE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "");
}

TEST(ParensNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::parens_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "( )");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_parens);
  ASSERT_TRUE(node->num_children() == 1);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_TRUE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "(");
  ASSERT_TRUE(node->wrap_right() == ")");
  ASSERT_TRUE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "( )");
}

TEST(BracketsNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::brackets_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "[ ]");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_brackets);
  ASSERT_TRUE(node->num_children() == 1);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_TRUE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "[");
  ASSERT_TRUE(node->wrap_right() == "]");
  ASSERT_FALSE(node->is_parens());
  ASSERT_TRUE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "[ ]");  
}

TEST(UnaryNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::unary_node>("~");
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "~");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_unary);
  ASSERT_TRUE(node->num_children() == 1);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_TRUE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "~");
}

TEST(PositNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::posit_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "+");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_posit);
  ASSERT_TRUE(node->num_children() == 1);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_TRUE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "+");
}

TEST(NegateNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::negate_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "-");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_negate);
  ASSERT_TRUE(node->num_children() == 1);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_TRUE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "-");
}

TEST(InfixNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::infix_node>("?");
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "?");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_infix);
  ASSERT_TRUE(node->num_children() == 2);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_TRUE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "?");
}

TEST(AdditionNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::addition_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "+");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_addition);
  ASSERT_TRUE(node->num_children() == 2);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_TRUE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "+");
}

TEST(SubtractionNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::subtraction_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "-");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_subtraction);
  ASSERT_TRUE(node->num_children() == 2);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_TRUE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "-");
}

TEST(MultiplicationNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::multiplication_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "*");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_multiplication);
  ASSERT_TRUE(node->num_children() == 2);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_TRUE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "*");
}

TEST(DivisionNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::division_node>();
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "/");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_division);
  ASSERT_TRUE(node->num_children() == 2);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_TRUE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "/");
}

TEST(FunctionNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::function_node>("csc");
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "csc");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_function);
  ASSERT_TRUE(node->num_children() == 1);
  ASSERT_FALSE(node->is_terminal());
  ASSERT_TRUE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "csc(");
  ASSERT_TRUE(node->wrap_right() == ")");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_TRUE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "csc");
}

TEST(NumberNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::number_node>(4);
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "4");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_number);
  ASSERT_TRUE(node->num_children() == 0);
  ASSERT_TRUE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_TRUE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_FALSE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "4");
}

TEST(IDNode, AllFunctions) {
  std::unique_ptr<brick::AST::node> node = std::make_unique<brick::AST::id_node>("stuff");
  ASSERT_TRUE(node->get_node_id().size() == 8);
  ASSERT_TRUE(node->to_string() ==  "stuff");
  ASSERT_TRUE(node->get_node_type() == brick::AST::node_type::_id);
  ASSERT_TRUE(node->num_children() == 0);
  ASSERT_TRUE(node->is_terminal());
  ASSERT_FALSE(node->wraps());
  ASSERT_TRUE(node->wrap_left() == "");
  ASSERT_TRUE(node->wrap_right() == "");
  ASSERT_FALSE(node->is_parens());
  ASSERT_FALSE(node->is_brackets());
  ASSERT_FALSE(node->is_unary());
  ASSERT_FALSE(node->is_infix());
  ASSERT_FALSE(node->is_posit());
  ASSERT_FALSE(node->is_negate());
  ASSERT_FALSE(node->is_addition());
  ASSERT_FALSE(node->is_subtraction());
  ASSERT_FALSE(node->is_multiplication());
  ASSERT_FALSE(node->is_division());
  ASSERT_FALSE(node->is_number());
  ASSERT_FALSE(node->is_function());
  ASSERT_TRUE(node->is_id());
  ASSERT_TRUE(node->get_gv_label() == "stuff");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}