#include "antlr4-runtime.h"
#include "brick.hpp"
#include "gtest/gtest.h"
#include "MathLexer.h"
#include "math/AST/build_ast_visitor.hpp"

using lexer = brick::MathLexer;
using parser = brick::MathParser;

TEST(BasicShit, Idk) {
  std::stringstream stream;
  stream << "2+3" << std::endl;
  antlr4::ANTLRInputStream input(stream);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
