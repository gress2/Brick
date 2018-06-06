#include "brick.hpp"
#include "gtest/gtest.h"

#include <cmath>

TEST(Evaluation, Case1) {
  brick::AST::AST* ast = brick::AST::parse("(3*4)/2-12+55");
  ASSERT_TRUE(ast->eval() == 49);
}

TEST(Evaluation, Case2) {
  brick::AST::AST* ast = brick::AST::parse("x");
  std::unordered_map<std::string, double> sym_tbl = {{"x", 78}};
  ASSERT_TRUE(ast->eval(&sym_tbl) == 78);
}

TEST(Evaluation, Case3) {
  brick::AST::AST* ast = brick::AST::parse("cos(45)");
  std::cout << ast->eval() << std::endl;
  ASSERT_TRUE(ast->eval() == std::cos(45));
}

TEST(ToGV, Case1) {
  brick::AST::AST* ast = brick::AST::parse("4*(3+2)");
  std::cout << ast->to_gv();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
