#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::tree::tree<T>;

TEST(DFSIncrementSemantics, IncrementPostfixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_dfs();
  float x = (it++)->get_value();
  ASSERT_TRUE(x == 0);
}

TEST(DFSIncrementSemantics, IncrementPostfixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_dfs();
  it++;
  float x = (it++)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(DFSIncrementSemantics, IncrementPrefixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_dfs();
  float x = (++it)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(DFSIncrementSemantics, IncrementPrefixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_dfs();
  ++it;
  auto end_it = ++it;
  ASSERT_TRUE(end_it == t0.end_dfs());
}

TEST(DFSIncrementSemantics, DecrementPostfixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_dfs();
  auto end_it = it--;
  ASSERT_TRUE(t0.end_dfs() == end_it);
}

TEST(DFSDecrementSemantics, DecrementPostfixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_dfs();
  it--;
  float x = (it--)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(DFSDecrementSemantics, DecrementPrefixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_dfs();
  float x = (--it)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(DFSDecrementSemantics, DecrementPrefixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_dfs();
  --it;
  float x = (--it)->get_value();
  ASSERT_TRUE(x == 0);
}

TEST(DFSIncrementTest, BasicCase1) {
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

TEST(DFSIncrementTest, BasicCase2) {
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

TEST(DFSIncrementTest, MediumCase) {
  using t = tree<int>;
  t t0(0);
  t0.add_child(1);
  t0.add_child(5);
  t0.add_child(7);
  t& t1 = t0.get_child(0);
  t1.add_child(2); t1.add_child(3);
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

TEST(DFSDecrementTest, BasicCase1) {
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

TEST(DFSDecrementTest, BasicCase2) {
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

TEST(DFSDecrementTest, MediumCase) {
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

TEST(DFSEquality, BeginEqualsBegin) {
  using t = tree<int>;
  t t0(32);
  auto it1 = t0.begin_dfs();
  auto it2 = t0.begin_dfs();
  ASSERT_TRUE(it1 == it2);
}

TEST(DFSEquality, BasicCase) {
  using t = tree<int>;
  t t0(3);
  t0.add_child(4);

  auto it1 = t0.begin_dfs();
  auto it2 = t0.begin_dfs();
  it2++;
  it2--;
  ASSERT_TRUE(it1 == it2);
}

TEST(DFSEquality, EndEqualsEnd) {
  using t = tree<int>;
  t t0(4);
  auto it1 = t0.end_dfs();
  auto it2 = t0.end_dfs();
  ASSERT_TRUE(it1 == it2);
}

TEST(DFSEquality, MediumCase) {
  using t = tree<int>;
  t t0(0);
  t0.add_child(1);
  t0.add_child(2);
  t t1 = t0.get_child(0);
  t1.add_child(3);

  auto it1 = t0.end_dfs();
  auto it2 = t0.end_dfs();
  
  it1--;
  --it2;
 
  ASSERT_TRUE(it1 == it2);
}

TEST(DFSInequality, SeparateTreeBeginsUnequal1) {
  using t = tree<int>;
  t t0(0);
  t t1(1);
  auto it1 = t0.begin_dfs();
  auto it2 = t1.begin_dfs();

  ASSERT_TRUE(it1 != it2);
}

TEST(DFSInequality, SeparateTreeBeginsUnequal2) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.begin_dfs();
  auto it2 = t1.begin_dfs(); 

  ASSERT_TRUE(it1 != it2);
}

TEST(DFSInequality, SeparateTreeEndsUnequal) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.end_dfs();
  auto it2 = t1.end_dfs();
  ASSERT_TRUE(it1 != it2);
}

TEST(DFSInequality, BasicCase) {
  using t = tree<int>;
  t t0(0);
  t0.add_child(0);
  auto it1 = t0.begin_dfs();
  auto it2 = t0.begin_dfs();
  it2++;

  ASSERT_TRUE(it1 != it2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
