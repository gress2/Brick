#include "brick.hpp"
#include "gtest/gtest.h"

TEST(ASTConstructionFromParse, Idk) {
  std::unique_ptr<brick::AST::AST> ast = brick::AST::parse("fn([3+4]*12)-6");
  ast->print();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
