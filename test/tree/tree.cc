#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::tree::tree<T>;

TEST(AddChild, IncreasesSizeOfChildVector) {
  tree<int> t(0);
  ASSERT_TRUE(0 == t.children().size());
  t.add_child(1);
  ASSERT_TRUE(1 == t.children().size());
}

TEST(GetChild, ReturnsCorrectChild) {
  tree<float> t(0);
  t.add_child(0);
  t.add_child(1);
  t.add_child(2);
  auto tmp = t.get_child(2).get_value();
  ASSERT_TRUE(tmp == 2);
}

TEST(GetParent, ReturnsNullptrIfNoParent) {
  tree<int> t(0);
  ASSERT_TRUE(t.get_parent() == nullptr);
}

TEST(GetParent, ReturnsCorrectParentIfExists) {
  tree<int> t(0);
  t.add_child(1);
  auto& tmp = t.get_child(0);
  ASSERT_TRUE(tmp.get_parent() == &t);
}

TEST(EqualityOperator, IsCorrectCase1) {
  tree<int> t1(0);
  t1.add_child(1);

  tree<int> t2(0); t2.add_child(1);

  ASSERT_TRUE(t1 == t2);
}

TEST(SetValue, DoesWhatItShould) {
  tree<int> t1(0);
  t1.set_value(1);
  ASSERT_TRUE(t1.get_value() == 1);
}

TEST(EqualityOperator, IsCorrectCase2) {
  tree<int> t1(0);
  t1.add_child(1).add_child(2);
  auto& child1 = t1.get_child(0);
  auto& child2 = t1.get_child(1);
  child1.add_child(1).add_child(2).add_child(3);
  child2.add_child(4).add_child(5).add_child(6);

  tree<int> t2(0);
  t2.add_child(1).add_child(2);
  auto& child3 = t2.get_child(0);
  auto& child4 = t2.get_child(1);
  child3.add_child(1).add_child(2).add_child(3);
  child4.add_child(4).add_child(5).add_child(6);

  ASSERT_TRUE(t1 == t2);
}

TEST(ToString, Case1) {
  tree<std::string> t("+");
  t.add_child("1").add_child("2");
  ASSERT_TRUE(t.to_string() == "1+2");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
