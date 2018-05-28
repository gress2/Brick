#include "antlr4-runtime.h"
#include "brick.hpp"
#include "gtest/gtest.h"
#include "MathLexer.h"

using lexer = brick::MathLexer;
using parser = brick::MathParser;
using listener = brick::AST::tree_shape_listener;

TEST(BasicShit, Idk) {
  std::stringstream stream;
  stream << "2/3" << std::endl;
  antlr4::ANTLRInputStream input(stream);
  lexer lex(&input);
  antlr4::CommonTokenStream tokens(&lex);
  parser par(&tokens);

  antlr4::tree::ParseTree *tree = par.math();
  listener lis;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&lis, tree);

}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
