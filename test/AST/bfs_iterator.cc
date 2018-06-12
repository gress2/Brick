#include <sstream>

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
  std::string correct("-( )6*[ ]12+34");

  std::stringstream ss;
  for (auto it = ast_ptr->begin_bfs(); it != ast_ptr->end_bfs(); ++it) {
    ss << it->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PrefixIncrement, Case3) {
  auto ast_ptr = brick::AST::parse("sin(3*x)+cos(4-y)");
  std::string correct("+sincos*-3x4y");

  std::stringstream ss;
  for (auto it = ast_ptr->begin_bfs(); it != ast_ptr->end_bfs(); ++it) {
    ss << it->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PrefixIncrement, CorrectSemantics) {
  auto ast_ptr = brick::AST::parse("3-8");
  auto iter = ast_ptr->begin_bfs();
  ASSERT_TRUE((++iter)->get_node()->get_node_type() 
    == brick::AST::node_type::_number);
}

TEST(PostfixIncrement, Case1) {
  auto ast_ptr = brick::AST::parse("1+2");
  auto iter = ast_ptr->begin_bfs();
  iter++;
  ASSERT_TRUE(iter->get_node()->is_number());
  iter++;
  ASSERT_TRUE(iter->get_node()->to_string() == "2");
}

TEST(PostfixIncrement, Case2) {
  auto ast_ptr = brick::AST::parse("([3+4]*12)-6");
  std::string correct("-( )6*[ ]12+34");

  std::stringstream ss;
  for (auto it = ast_ptr->begin_bfs(); it != ast_ptr->end_bfs(); it++) {
    ss << it->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PostfixIncrement, Case3) {
  auto ast_ptr = brick::AST::parse("sin(3*x)+cos(4-y)");
  std::string correct("+sincos*-3x4y");

  std::stringstream ss;
  for (auto it = ast_ptr->begin_bfs(); it != ast_ptr->end_bfs(); it++) {
    ss << it->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PostfixIncrement, CorrectSemantics) {
  auto ast_ptr = brick::AST::parse("3-8");
  auto iter = ast_ptr->begin_bfs();
  ASSERT_TRUE((iter++)->get_node()->get_node_type() 
    == brick::AST::node_type::_subtraction);
  ASSERT_TRUE(iter->get_node()->get_node_type() 
    == brick::AST::node_type::_number);
}

TEST(PrefixDecrement, Case1) {
  auto ast_ptr = brick::AST::parse("1+2");
  auto iter = ast_ptr->end_dfs();
  --iter;
  ASSERT_TRUE(iter->get_node()->is_number());
  --iter;
  ASSERT_TRUE(iter->get_node()->to_string() == "1");
}

TEST(PrefixDecrement, Case2) {
  auto ast_ptr = brick::AST::parse("([3+4]*12)-6");
  std::string correct("43+12[ ]*6( )-");

  std::stringstream ss;
  auto iter = ast_ptr->end_bfs();
  while (iter != ast_ptr->begin_bfs()) {
    --iter;
    ss << iter->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PrefixDecrement, Case3) {
  auto ast_ptr = brick::AST::parse("sin(3*x)+cos(4-y)");
  std::string correct("y4x3-*cossin+");
  
  std::stringstream ss;
  auto iter = ast_ptr->end_bfs();
  while (iter != ast_ptr->begin_bfs()) {
    --iter;
    ss << iter->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PrefixDecrement, CorrectSemantics) {
  auto ast_ptr = brick::AST::parse("3-8");
  auto iter = ast_ptr->end_bfs();
  ASSERT_TRUE((--iter)->get_node()->get_node_type() 
    == brick::AST::node_type::_number);
}

TEST(PostfixDecrement, Case1) {
  auto ast_ptr = brick::AST::parse("1+2");
  auto iter = ast_ptr->end_dfs();
  iter--;
  ASSERT_TRUE(iter->get_node()->is_number());
  iter--;
  ASSERT_TRUE(iter->get_node()->to_string() == "1");
}

TEST(PostfixDecrement, Case2) {
  auto ast_ptr = brick::AST::parse("([3+4]*12)-6");
  std::string correct("43+12[ ]*6( )-");

  std::stringstream ss;
  auto iter = ast_ptr->end_bfs();
  while (iter != ast_ptr->begin_bfs()) {
    iter--;
    ss << iter->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PostfixDecrement, Case3) {
  auto ast_ptr = brick::AST::parse("sin(3*x)+cos(4-y)");
  std::string correct("y4x3-*cossin+");
  
  std::stringstream ss;
  auto iter = ast_ptr->end_bfs();
  while (iter != ast_ptr->begin_bfs()) {
    iter--;
    ss << iter->get_node()->to_string();
  }
  ASSERT_TRUE(ss.str() == correct);
}

TEST(PostfixDecrement, CorrectSemantics) {
  auto ast_ptr = brick::AST::parse("3-8");
  auto iter = ast_ptr->end_bfs();
  ASSERT_TRUE((iter--) == ast_ptr->end_dfs());
  ASSERT_TRUE(iter->get_node()->get_node_type() 
    == brick::AST::node_type::_number);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}