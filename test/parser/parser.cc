#include "antlr4-runtime.h"
#include "brick.hpp"
#include "gtest/gtest.h"
#include "MathLexer.h"

using lexer = brick::MathLexer;
using parser = brick::MathParser;
using ast_builder = brick::AST::ast_builder;

TEST(BasicShit, Idk) {
  std::stringstream stream;
  stream << "fn(3+4)-6" << std::endl;
  brick::tree::tree2* t = brick::AST::parse(stream);
  t->print();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
