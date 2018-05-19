#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::tree::tree<T>;

TEST(BFSIncrementSemantics, IncrementPostfixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_bfs();
  float x = (it++)->get_value();
  ASSERT_TRUE(x == 0);
}

TEST(BFSIncrementSemantics, IncrementPostfixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_bfs();
  it++;
  float x = (it++)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(BFSIncrementSemantics, IncrementPrefixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_bfs();
  float x = (++it)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(BFSIncrementSemantics, IncrementPrefixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.begin_bfs();
  ++it;
  auto end_it = ++it;
  ASSERT_TRUE(end_it == t0.end_dfs());
}

TEST(BFSIncrementSemantics, DecrementPostfixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_bfs();
  auto end_it = it--;
  ASSERT_TRUE(t0.end_dfs() == end_it);
}

TEST(BFSDecrementSemantics, DecrementPostfixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_bfs();
  it--;
  float x = (it--)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(BFSDecrementSemantics, DecrementPrefixCase1) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_bfs();
  float x = (--it)->get_value();
  ASSERT_TRUE(x == 1);
}

TEST(BFSDecrementSemantics, DecrementPrefixCase2) {
  using t = tree<float>;
  t t0(0);
  t0.add_child(1);
  auto it = t0.end_bfs();
  --it;
  float x = (--it)->get_value();
  ASSERT_TRUE(x == 0);
}

TEST(BFSIncrement, BasicCase1) {
  using t = tree<std::string>;
  t t0("0");
  t0.add_child("1");
  t0.add_child("4");

  t& t1 = t0.get_child(0);
  t1.add_child("2");
  t1.add_child("3");

  std::vector<std::string> correct = {"0", "1", "4", "2", "3"};
  std::vector<std::string> test = {};

  for (auto it = t0.begin_bfs(); it != t0.end_bfs(); ++it) {
    test.push_back(it->get_value());
  }
  ASSERT_EQ(correct, test);
}

TEST(BFSIncrement, BasicCase2) {
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
  for (auto it = t0.begin_bfs(); it != t0.end_bfs(); ++it) {
    test.push_back(it->get_value());
  }
  ASSERT_EQ(correct, test);
}

TEST(BFSIncrement, MediumCase) {
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

  std::vector<int> correct = {0, 1, 5, 7, 2, 3, 6, 8, 10, 4, 9};
  std::vector<int> test = {};
  for (auto it = t0.begin_bfs(); it != t0.end_bfs(); ++it) {
    test.push_back(it->get_value());
  }
  ASSERT_EQ(correct, test);
}

TEST(BFSDecrement, BasicCase1) {
  using t = tree<std::string>;
  t t0("0");
  t0.add_child("1");
  t0.add_child("4");

  t& t1 = t0.get_child(0);
  t1.add_child("2");
  t1.add_child("3");

  std::vector<std::string> correct = {"3", "2", "4", "1", "0"};
  std::vector<std::string> test = {};

  auto it = t0.end_bfs();
  while (it != t0.begin_bfs()) {
    --it;
    test.push_back(it->get_value());
  }
  
  ASSERT_EQ(correct, test);
}

TEST(BFSDecrement, BasicCase2) {
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

  auto it = t0.end_bfs();
  while (it != t0.begin_bfs()) {
    --it;
    test.push_back(it->get_value());
  }
  
  ASSERT_EQ(correct, test);
}

TEST(BFSDecrement, MediumCase) {
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

  std::vector<int> correct = {9, 4, 10, 8, 6, 3, 2, 7, 5, 1, 0};
  std::vector<int> test = {};

  auto it = t0.end_bfs();
  while (it != t0.begin_bfs()) {
    --it;
    test.push_back(it->get_value());
  }
  
  ASSERT_EQ(correct, test);
}

TEST(BFSEquality, SameTreeBeginsEqual) {
  using t = tree<int>;
  t t0(32);
  auto it1 = t0.begin_bfs();
  auto it2 = t0.begin_bfs();
  ASSERT_TRUE(it1 == it2);
}

TEST(BFSEquality, BasicCase) {
  using t = tree<int>;
  t t0(3);
  t0.add_child(4);

  auto it1 = t0.begin_bfs();
  auto it2 = t0.begin_bfs();
  it2++;
  it2--;
  ASSERT_TRUE(it1 == it2);
}

TEST(BFSEquality, SameTreeEndsEqual) {
  using t = tree<int>;
  t t0(4);
  auto it1 = t0.end_bfs();
  auto it2 = t0.end_bfs();
  ASSERT_TRUE(it1 == it2);
}

TEST(DFSEquality, BasicCase2) {
  using t = tree<int>;
  t t0(0);
  t0.add_child(1);
  t0.add_child(2);
  t t1 = t0.get_child(0);
  t1.add_child(3);

  auto it1 = t0.end_bfs();
  auto it2 = t0.end_bfs();
  
  it1--;
  --it2;
 
  ASSERT_TRUE(it1 == it2);
}

TEST(BFSInequality, SeparateTreeBeginsUnequal1) {
  using t = tree<int>;
  t t0(0);
  t t1(1);
  auto it1 = t0.begin_bfs();
  auto it2 = t1.begin_bfs();

  ASSERT_TRUE(it1 != it2);
}

TEST(BFSInequality, SeparateTreeBeginsUnequal2) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.begin_bfs();
  auto it2 = t1.begin_bfs(); 

  ASSERT_TRUE(it1 != it2);
}

TEST(BFSInequality, SeparateTreeEndsUnequal) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.end_bfs();
  auto it2 = t1.end_bfs();
  ASSERT_TRUE(it1 != it2);
}

TEST(BFSInequality, BasicCase) {
  using t = tree<int>;
  t t0(0);
  t0.add_child(0);
  auto it1 = t0.begin_bfs();
  auto it2 = t0.begin_bfs();
  it2++;

  ASSERT_TRUE(it1 != it2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
