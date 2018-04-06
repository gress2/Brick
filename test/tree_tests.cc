#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::AST::tree<T>;

class TreeFixture : public ::testing::Test {
  protected:
    virtual void SetUp() {}
    tree<std::string> root_{nullptr, "root"}; 
};

TEST_F(TreeFixture, Test1) { 
  auto it = root_.begin_dfs();
  auto& tmp = *it;
  std::cout << tmp.get_value() << std::endl;
  ASSERT_EQ(0, 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
