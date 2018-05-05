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

TEST_F(TreeFixture, DFSEqualityTest1) {
  using t = tree<int>;

  t t0(32);
  auto it1 = t0.begin_dfs();
  auto it2 = t0.begin_dfs();
  ASSERT_TRUE(it1 == it2);
}

TEST_F(TreeFixture, DFSEqualityTest2) {
  using t = tree<int>;

  t t0(3);
  t0.add_child(4);

  auto it1 = t0.begin_dfs();
  auto it2 = t0.begin_dfs();
  it2++;
  it2--;
  ASSERT_TRUE(it1 == it2);
}

TEST_F(TreeFixture, DFSEqualityTest3) {
  using t = tree<int>;
  t t0(4);
  auto it1 = t0.end_dfs();
  auto it2 = t0.end_dfs();
  ASSERT_TRUE(it1 == it2);
}

TEST_F(TreeFixture, DFSEqualityTest4) {
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

TEST_F(TreeFixture, DFSInequalityTest1) {
  using t = tree<int>;
  t t0(0);
  t t1(1);
  auto it1 = t0.begin_dfs();
  auto it2 = t1.begin_dfs();

  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, DFSInequalityTest2) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.begin_dfs();
  auto it2 = t1.begin_dfs(); 

  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, DFSInequalityTest3) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.end_dfs();
  auto it2 = t1.end_dfs();
  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, DFSInequalityTest4) {
  using t = tree<int>;
  t t0(0);
  t0.add_child(0);
  auto it1 = t0.begin_dfs();
  auto it2 = t0.begin_dfs();
  it2++;

  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, BFSIncrementTest1) {
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

TEST_F(TreeFixture, BFSIncrementTest2) {
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

TEST_F(TreeFixture, BFSIncrementTest3) {
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

TEST_F(TreeFixture, BFSDecrementTest1) {
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

TEST_F(TreeFixture, BFSDecrementTest2) {
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

TEST_F(TreeFixture, BFSDecrementTest3) {
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

TEST_F(TreeFixture, BFSEqualityTest1) {
  using t = tree<int>;

  t t0(32);
  auto it1 = t0.begin_bfs();
  auto it2 = t0.begin_bfs();
  ASSERT_TRUE(it1 == it2);
}

TEST_F(TreeFixture, BFSEqualityTest2) {
  using t = tree<int>;

  t t0(3);
  t0.add_child(4);

  auto it1 = t0.begin_bfs();
  auto it2 = t0.begin_bfs();
  it2++;
  it2--;
  ASSERT_TRUE(it1 == it2);
}

TEST_F(TreeFixture, BFSEqualityTest3) {
  using t = tree<int>;
  t t0(4);
  auto it1 = t0.end_bfs();
  auto it2 = t0.end_bfs();
  ASSERT_TRUE(it1 == it2);
}

TEST_F(TreeFixture, BFSEqualityTest4) {
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

TEST_F(TreeFixture, BFSInequalityTest1) {
  using t = tree<int>;
  t t0(0);
  t t1(1);
  auto it1 = t0.begin_bfs();
  auto it2 = t1.begin_bfs();

  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, BFSInequalityTest2) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.begin_bfs();
  auto it2 = t1.begin_bfs(); 

  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, BFSInequalityTest3) {
  using t = tree<int>;
  t t0(0);
  t t1(0);
  auto it1 = t0.end_bfs();
  auto it2 = t1.end_bfs();
  ASSERT_TRUE(it1 != it2);
}

TEST_F(TreeFixture, BFSInequalityTest4) {
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
