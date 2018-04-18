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

TEST_F(TreeFixture, Test1) { 
  using t = tree<std::string>;

  t t0("0");
  t& t1 = t0.add_child("1");
  t0.add_child("4");
  std::cout << "A" << std::endl;
  t1.add_child("2");
  std::cout << "B" << std::endl;
  t1.add_child("3");

  std::cout << "umm" << std::endl;

  auto it = t0.begin_shiterator();

  std::cout << (*it).get_value() << std::endl;
  for (int i = 0; i < 4; i++) {
    ++it;
    std::cout << (*it).get_value() << std::endl;
  }
}

TEST_F(TreeFixture, Test2) {
  using t = tree<std::string>;

  t t0("0");
  t& t1 = t0.add_child("1");
  t& t2 = t1.add_child("2");
  t2.add_child("3");
  t2.add_child("4");

  auto it = t0.begin_shiterator();
  std::cout << (*it).get_value() << std::endl;
  for (int i = 0; i < 4; i++) {
    ++it;
    std::cout << (*it).get_value() << std::endl;
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
