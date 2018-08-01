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

TEST(IsTerminal, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::number_node>(3));
  ASSERT_TRUE(test.is_terminal());
}

TEST(IsTerminal, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::brackets_node>());
  ASSERT_FALSE(test.is_terminal());
}

TEST(IsTerminal, Case3) {
  brick::AST::AST test(std::make_unique<brick::AST::brackets_node>());
  auto child_ptr = test.add_child(std::make_unique<brick::AST::id_node>("hi44"));
  ASSERT_FALSE(test.is_terminal());
  ASSERT_TRUE(child_ptr->is_terminal());
}

TEST(HasChildren, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::id_node>("test"));
  ASSERT_FALSE(test.has_children());
}

TEST(HasChildren, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::posit_node>());
  auto child_ptr = test.add_child(std::make_unique<brick::AST::number_node>(890));
  ASSERT_TRUE(test.has_children());
  ASSERT_FALSE(child_ptr->has_children());
}

TEST(GetChild, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::division_node>());
  auto child_ptr = test.get_child(0);
  ASSERT_TRUE(child_ptr == nullptr);
}

TEST(GetChild, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::parens_node>());
  std::shared_ptr<brick::AST::AST> child = 
    std::make_shared<brick::AST::AST>(std::make_unique<brick::AST::number_node>(4));
  test.add_child(child);
  ASSERT_TRUE(*(test.get_child(0)) == *child);
}

TEST(GetChildren, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::subtraction_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(5));
  test.add_child(std::make_unique<brick::AST::number_node>(2));
  auto& vec = test.get_children();
  ASSERT_TRUE(vec.size() == 2);
}

TEST(ToString, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::parens_node>());
  ASSERT_TRUE(test.to_string() == "( )");
}

TEST(ToString, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::number_node>(4));
  ASSERT_TRUE(test.to_string() == "4");
}

TEST(ToString, Case3) {
  brick::AST::AST test(std::make_unique<brick::AST::brackets_node>());
  auto mul_ptr = test.add_child(std::make_unique<brick::AST::multiplication_node>());
  auto log_ptr = mul_ptr->add_child(std::make_unique<brick::AST::log_function_node>());
  log_ptr->add_child(std::make_unique<brick::AST::number_node>(100));
  mul_ptr->add_child(std::make_unique<brick::AST::id_node>("x"));
  ASSERT_EQ(test.to_string(), "[(log(100)*x)]");
}

TEST(ToString, Hard) {
  brick::AST::AST root(std::make_unique<brick::AST::posit_node>());
  auto mul_ptr = root.add_child(std::make_unique<brick::AST::multiplication_node>()); 
  mul_ptr->add_child(std::make_unique<brick::AST::id_node>("_x0"));
  auto mul_ptr2 = mul_ptr->add_child(std::make_unique<brick::AST::multiplication_node>());
  mul_ptr2->add_child(std::make_unique<brick::AST::id_node>("_x0"));
  auto add_ptr = mul_ptr2->add_child(std::make_unique<brick::AST::addition_node>());
  add_ptr->add_child(std::make_unique<brick::AST::id_node>("_x0"));
  add_ptr->add_child(std::make_unique<brick::AST::number_node>(1));
  ASSERT_EQ(root.to_string(), "+(_x0*(_x0*(_x0+1)))");
}

TEST(Evaluation, Case1) {
  // (3*4)/2-12+55
  brick::AST::AST test(std::make_unique<brick::AST::addition_node>());
  auto sub_ptr = test.add_child(std::make_unique<brick::AST::subtraction_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(55));
  auto div_ptr = sub_ptr->add_child(std::make_unique<brick::AST::division_node>());
  sub_ptr->add_child(std::make_unique<brick::AST::number_node>(12));
  auto paren_ptr = div_ptr->add_child(std::make_unique<brick::AST::parens_node>());
  div_ptr->add_child(std::make_unique<brick::AST::number_node>(2));
  auto mul_ptr = paren_ptr->add_child(std::make_unique<brick::AST::multiplication_node>());
  mul_ptr->add_child(std::make_unique<brick::AST::number_node>(3));
  mul_ptr->add_child(std::make_unique<brick::AST::number_node>(4));
  ASSERT_TRUE(test.eval() == 49);
}

TEST(Evaluation, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::id_node>("x"));
  std::unordered_map<std::string, double> sym_tbl = {{"x", 78}};
  ASSERT_TRUE(test.eval(&sym_tbl) == 78);
}

TEST(Evaluation, Case3) {
  brick::AST::AST test(std::make_unique<brick::AST::cos_function_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(45));
  ASSERT_TRUE(test.eval() == std::cos(45));
}

TEST(GetNodeID, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::negate_node>());
  auto node_id = test.get_node_id();
  ASSERT_TRUE(node_id.length() == 8);
}

TEST(ToGV, Case1) {
  // 4*(3+2)
  brick::AST::AST test(std::make_unique<brick::AST::multiplication_node>());
  test.add_child(std::make_unique<brick::AST::number_node>(4));
  auto paren_ptr = test.add_child(std::make_unique<brick::AST::parens_node>());
  auto add_ptr = paren_ptr->add_child(std::make_unique<brick::AST::addition_node>());
  add_ptr->add_child(std::make_unique<brick::AST::number_node>(3));
  add_ptr->add_child(std::make_unique<brick::AST::number_node>(2));

  std::string gv_str = test.to_gv();
  std::size_t n = std::count(gv_str.begin(), gv_str.end(), '\n');
  ASSERT_TRUE(n == 13);
}

TEST(ToGV, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::function_node>("fn"));
  auto mul_node = test.add_child(std::make_unique<brick::AST::multiplication_node>());
  mul_node->add_child(std::make_unique<brick::AST::number_node>(33));
  mul_node->add_child(std::make_unique<brick::AST::id_node>("x"));
  std::string gv_str = test.to_gv();
  std::size_t n = std::count(gv_str.begin(), gv_str.end(), '\n');
  ASSERT_TRUE(n == 9);
}

TEST(GetLevel, Case1) {
  brick::AST::AST test(std::make_unique<brick::AST::parens_node>());
  ASSERT_TRUE(test.get_level() == 0);
  auto paren_ptr = test.add_child(std::make_unique<brick::AST::parens_node>());
  ASSERT_TRUE(paren_ptr->get_level() == 1);
  auto num_ptr = paren_ptr->add_child(std::make_unique<brick::AST::number_node>(4));
  ASSERT_TRUE(num_ptr->get_level() == 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
