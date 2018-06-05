#include "brick.hpp"
#include "gtest/gtest.h"

TEST(ASTEvaluation, Case1) {
  brick::AST::AST* ast = brick::AST::parse("3");
  std::cout << ast->eval() << std::endl;
  ASSERT_TRUE(ast->eval() == 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
