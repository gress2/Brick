#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::AST::tree<T>;

class TreeFixture : public ::testing::Test {
  protected:
    virtual void SetUp() {}
    tree<std::string> root_{"root"};
};

TEST_F(TreeFixture, DFSIncrementTest1) {
  using t = tree<std::string>;

  t t0("0");
  t0.add_child("1");
  t0.add_child("4");

  t& t1 = t0.get_child(0);
  t1.add_child("2");
  t1.add_child("3");

  std::vector<std::string> correct = {"0", "1", "2", "3", "4"};
  std::vector<std::string> test = {};
  for (auto it = t0.begin_dfs(); it != t0.end_dfs(); ++it) {
    test.push_back(it->get_value());
  }
  ASSERT_EQ(correct, test);
}

TEST_F(TreeFixture, DFSIncrementTest2) {
  using t = tree<std::string>;

  t t0("0");
  t0.add_child("1");
  t& t1 = t0.get_child(0);
  t1.add_child("2");
  t& t2 = t1.get_child(0);
  t2.add_child("3");
  t2.add_child("4");

  std::vector<std::string> correct = {"0", "1", "2", "3", "4"};
  std::vector<std::string> test = {};
  for (auto it = t0.begin_dfs(); it != t0.end_dfs(); ++it) {
    test.push_back(it->get_value());
  }
  ASSERT_EQ(correct, test);
}

TEST_F(TreeFixture, DFSIncrementTest3) {
  using t = tree<int>;

  t t0(0);
  t0.add_child(1);
  t0.add_child(5);
  t0.add_child(7);
  t& t1 = t0.get_child(0);
  t1.add_child(2);
  t1.add_child(3);
  t& t3 = t1.get_child(1);
  t3.add_child(4);
  t& t5 = t0.get_child(1);
  t5.add_child(6);
  t& t7 = t0.get_child(2);
  t7.add_child(8);
  t7.add_child(10);
  t7.get_child(0).add_child(9);

  std::vector<int> correct = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> test = {};
  for (auto it = t0.begin_dfs(); it != t0.end_dfs(); ++it) {
    test.push_back(it->get_value());
  }
  ASSERT_EQ(correct, test);
}

TEST_F(TreeFixture, DFSDecrementTest1) {
  using t = tree<std::string>;

  t t0("0");
  t0.add_child("1");
  t0.add_child("4");

  t& t1 = t0.get_child(0);
  t1.add_child("2");
  t1.add_child("3");

  std::vector<std::string> correct = {"4", "3", "2", "1", "0"};
  std::vector<std::string> test = {};

  auto it = t0.end_dfs();
  while (it != t0.begin_dfs()) {
    --it;
    test.push_back(it->get_value());
  }
  
  ASSERT_EQ(correct, test);
}

TEST_F(TreeFixture, DFSDecrementTest2) {
  using t = tree<std::string>;

  t t0("0");
  t0.add_child("1");
  t& t1 = t0.get_child(0);
  t1.add_child("2");
  t& t2 = t1.get_child(0);
  t2.add_child("3");
  t2.add_child("4");

  std::vector<std::string> correct = {"4", "3", "2", "1", "0"};
  std::vector<std::string> test = {};

  auto it = t0.end_dfs();
  while (it != t0.begin_dfs()) {
    --it;
    test.push_back(it->get_value());
  }
  
  ASSERT_EQ(correct, test);
}

TEST_F(TreeFixture, DFSDecrementTest3) {
  using t = tree<int>;

  t t0(0);
  t0.add_child(1);
  t0.add_child(5);
  t0.add_child(7);
  t& t1 = t0.get_child(0);
  t1.add_child(2);
  t1.add_child(3);
  t& t3 = t1.get_child(1);
  t3.add_child(4);
  t& t5 = t0.get_child(1);
  t5.add_child(6);
  t& t7 = t0.get_child(2);
  t7.add_child(8);
  t7.add_child(10);
  t7.get_child(0).add_child(9);

  std::vector<int> correct = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> test = {};

  auto it = t0.end_dfs();
  while (it != t0.begin_dfs()) {
    --it;
    test.push_back(it->get_value());
  }
  
  ASSERT_EQ(correct, test);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
