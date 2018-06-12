#include "brick.hpp"
#include "gtest/gtest.h"

TEST(Position, Case1) {
  auto ast_ptr = brick::AST::parse("3+4");
  brick::AST::dfs_iterator dfs_it = ast_ptr->begin_dfs();
  ASSERT_TRUE(dfs_it.position() == 0);
}

TEST(Position, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::addition_node>());
  auto three_ptr = test.add_child(std::make_unique<brick::AST::number_node>(3));
  auto four_ptr = test.add_child(std::make_unique<brick::AST::number_node>(4));
  ASSERT_TRUE(test.begin_dfs().position() == 0);
  ASSERT_TRUE(three_ptr->begin_dfs().position() == 0);
  ASSERT_TRUE(four_ptr->begin_dfs().position() == 1);
}

TEST(IsFirst, Case1) {
  auto ast_ptr = brick::AST::parse("3+4");
  auto dfs_it = ast_ptr->begin_dfs();
  ASSERT_TRUE(dfs_it.is_first());
}

TEST(IsFirst, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::addition_node>());
  auto three_ptr = test.add_child(std::make_unique<brick::AST::number_node>(3));
  auto four_ptr = test.add_child(std::make_unique<brick::AST::number_node>(4));
  ASSERT_TRUE(test.begin_dfs().is_first());
  ASSERT_TRUE(three_ptr->begin_dfs().is_first());
  ASSERT_FALSE(four_ptr->begin_dfs().is_first());
}

TEST(IsLast, Case1) {
  auto ast_ptr = brick::AST::parse("3+4");
  auto dfs_it = ast_ptr->begin_dfs();
  ASSERT_TRUE(dfs_it.is_last());
}

TEST(IsLast, Case2) {
  brick::AST::AST test(std::make_unique<brick::AST::addition_node>());
  auto three_ptr = test.add_child(std::make_unique<brick::AST::number_node>(3));
  auto four_ptr = test.add_child(std::make_unique<brick::AST::number_node>(4));
  ASSERT_TRUE(test.begin_dfs().is_last());
  ASSERT_FALSE(three_ptr->begin_dfs().is_last());
  ASSERT_TRUE(four_ptr->begin_dfs().is_last());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}