#include "brick.hpp"
#include "gtest/gtest.h"

using AST = brick::AST::AST;
using std::unique_ptr;
using std::make_unique;

TEST(ConstructionFromParse, Case1) {
  unique_ptr<AST> ast = brick::AST::parse("3+4");

  AST correct(make_unique<brick::AST::addition_node>());
  correct.add_child(make_unique<brick::AST::number_node>(3));
  correct.add_child(make_unique<brick::AST::number_node>(4));
  
  ASSERT_TRUE(*ast == correct);
}

TEST(ConstructionFromParse, Case2) {
  unique_ptr<AST> ast = brick::AST::parse("cos(x)");

  AST correct(make_unique<brick::AST::cos_function_node>());
  correct.add_child(make_unique<brick::AST::id_node>("x"));

  ASSERT_TRUE(*ast == correct);
}

TEST(ConstructionFromParse, Case3) {
  unique_ptr<AST> ast = brick::AST::parse("");

  ASSERT_TRUE(ast == nullptr);
}

TEST(ConstructionFromParse, Case4) {
  unique_ptr<AST> ast = brick::AST::parse("cos()");
  
  AST correct(make_unique<brick::AST::cos_function_node>());
  ASSERT_TRUE(*ast == correct);
}

TEST(ConstructionFromParse, Case5) {
  unique_ptr<AST> ast = brick::AST::parse("([3+4]*12)-6");
  
  AST correct(make_unique<brick::AST::subtraction_node>());
  auto parens = correct.add_child(make_unique<brick::AST::parens_node>());
  correct.add_child(make_unique<brick::AST::number_node>(6));
  auto mul = parens->add_child(make_unique<brick::AST::multiplication_node>());
  auto brackets = mul->add_child(make_unique<brick::AST::brackets_node>());
  mul->add_child(make_unique<brick::AST::number_node>(12));
  auto add = brackets->add_child(make_unique<brick::AST::addition_node>());
  add->add_child(make_unique<brick::AST::number_node>(3));
  add->add_child(make_unique<brick::AST::number_node>(4));

  ASSERT_TRUE(*ast == correct);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
