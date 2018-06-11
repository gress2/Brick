#include "brick.hpp"
#include "gtest/gtest.h"

#include <algorithm>
#include <cmath>
#include <memory>

TEST(AddChild, UniquePtrToNode) {
  brick::AST::AST test(std::make_unique<brick::AST::parens_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(7));
  ASSERT_TRUE(test.get_children().size() == 1);
  auto child_ptr = test.get_child(0);
  std::shared_ptr<brick::AST::AST> child_ast = 
    std::make_shared<brick::AST::AST>(std::make_unique<brick::AST::number_node>(7));
  ASSERT_TRUE(*child_ptr == *child_ast);
}

TEST(AddChild, SharedPtrToAST) {
  brick::AST::AST test(std::make_unique<brick::AST::parens_node>());
  std::shared_ptr<brick::AST::AST> child_ast = 
    std::make_shared<brick::AST::AST>(std::make_unique<brick::AST::id_node>("x"));
  auto child_ptr = test.add_child(child_ast);
  ASSERT_TRUE(*child_ptr == *child_ast);
}

TEST(SetNode, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::parens_node>());
  test.set_node(std::make_unique<brick::AST::brackets_node>());
  brick::AST::brackets_node bn;
  ASSERT_TRUE(*test.get_node() == bn);
}

TEST(SetNode, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::addition_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(3));
  auto child_ptr = test.add_child(std::make_unique<brick::AST::number_node>(14));
  child_ptr->set_node(std::make_unique<brick::AST::number_node>(44));
  std::shared_ptr<brick::AST::AST> child_ast =
    std::make_shared<brick::AST::AST>(std::make_unique<brick::AST::number_node>(44));

  ASSERT_TRUE(*child_ptr == *child_ast);
}

TEST(SetParent, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::brackets_node>());
  auto child_ptr = test.add_child(std::make_unique<brick::AST::id_node>("hello"));
  child_ptr->set_parent(nullptr);
  ASSERT_TRUE(child_ptr->get_parent() == nullptr);
}

TEST(SetParent, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::negate_node>());
  ASSERT_TRUE(test.get_parent() == nullptr);
  brick::AST::AST parent(std::make_unique<brick::AST::parens_node>());
  test.set_parent(&parent);
  ASSERT_TRUE(parent == *test.get_parent());
}

TEST(GetNode, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::id_node>("ok"));
  brick::AST::id_node id("ok");
  ASSERT_TRUE(*test.get_node() == id);
}

TEST(IsFull, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::division_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(7));
  test.add_child(std::make_unique<brick::AST::id_node>("n"));
  ASSERT_TRUE(test.is_full());
}

TEST(IsFull, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::posit_node>());
  ASSERT_FALSE(test.is_full());
}

TEST(Evaluation, Case1) {
  std::unique_ptr<brick::AST::AST> ast = brick::AST::parse("(3*4)/2-12+55");
  ASSERT_TRUE(ast->eval() == 49);
}

TEST(Evaluation, Case2) {
  std::unique_ptr<brick::AST::AST> ast = brick::AST::parse("x");
  std::unordered_map<std::string, double> sym_tbl = {{"x", 78}};
  ASSERT_TRUE(ast->eval(&sym_tbl) == 78);
}

TEST(Evaluation, Case3) {
  std::unique_ptr<brick::AST::AST> ast = brick::AST::parse("cos(45)");
  ASSERT_TRUE(ast->eval() == std::cos(45));
}

TEST(ToGV, Case1) {
  std::unique_ptr<brick::AST::AST> ast = brick::AST::parse("4*(3+2)");
  std::string gv_str = ast->to_gv();
  std::size_t n = std::count(gv_str.begin(), gv_str.end(), '\n');
  ASSERT_TRUE(n == 13);
}

TEST(TOGV, Case2) {
  std::unique_ptr<brick::AST::AST> ast = brick::AST::parse("fn(33*x)");
  std::string gv_str = ast->to_gv();
  std::size_t n = std::count(gv_str.begin(), gv_str.end(), '\n');
  ASSERT_TRUE(n == 9);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
