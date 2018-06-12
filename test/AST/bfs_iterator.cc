#include "brick.hpp"
#include "gtest/gtest.h"

TEST(PrefixIncrement, Case1) {
  auto ast_ptr = brick::AST::parse("1+2");
  auto iter = ast_ptr->begin_bfs();
  ++iter;
  ASSERT_TRUE(iter->get_node()->is_number());
  ++iter;
  ASSERT_TRUE(iter->get_node()->to_string() == "2");
}

TEST(PrefixIncrement, Case2) {
  auto ast_ptr = brick::AST::parse("([3+4]*12)-6");
  for (auto it = ast_ptr->begin_bfs(); it != ast_ptr->end_bfs(); ++it) {
    std::cout << it->get_node()->to_string() << std::endl;
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}