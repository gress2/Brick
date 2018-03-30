#include "brick.hpp"
#include "gtest/gtest.h"

class ASTTest : public ::testing::Test {
  protected:
    virtual void SetUp() {}
};

class ASTReaderTest : public ::testing::Test {
  protected:
    virtual void SetUp() {}
};

TEST_F(ASTReaderTest, DeadSimpleTreeReadTest) {
  using Tree = Brick::AST::Tree;
  Tree root("+");
  Tree one("1");
  Tree two("2");
  root.set_children({one, two});

  Brick::AST::Reader reader("../data/dead_simple.ast");
  Tree read_ast = reader.read();

  bool equivalent = (root == read_ast);
  ASSERT_TRUE(equivalent);
}

TEST_F(ASTReaderTest, EasyTreeReadTest) {
  using Tree = Brick::AST::Tree;
  Tree root("/");
  Tree t1("+");
  Tree t2("3");
  Tree t3("5");
  Tree t4("2");
  t1.set_children({t2, t3});
  root.set_children({t1, t4});

  Brick::AST::Reader reader("../data/easy.ast");
  Tree read_ast = reader.read();
  read_ast.print();
  
  bool equivalent = (root == read_ast);
  ASSERT_TRUE(equivalent);  
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
