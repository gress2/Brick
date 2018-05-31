#include "antlr4-runtime.h"
#include "brick.hpp"
#include "gtest/gtest.h"
#include "MathLexer.h"

using lexer = brick::MathLexer;
using parser = brick::MathParser;
using ast_builder = brick::AST::ast_builder;

TEST(BasicShit, Idk) {
  std::stringstream stream;
  stream << "3+4" << std::endl;
  antlr4::ANTLRInputStream input(stream);
  lexer lex(&input);
  antlr4::CommonTokenStream tokens(&lex);
  parser par(&tokens);

  antlr4::tree::ParseTree *tree = par.math();
  ast_builder builder;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&builder, tree);
  brick::tree::tree2* t = builder.build();
  t->print();
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
