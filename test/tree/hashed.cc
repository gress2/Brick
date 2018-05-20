#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using hashed = brick::tree::hashed<T>;

TEST(ParenOperator, CanBeUsedAsGetterCase1) {
  std::string s("test"); 
  hashed<std::string> h(s); 
  auto t = h();
  ASSERT_TRUE(t == std::hash<std::string>{}(s));
}

TEST(ParenOperator, CanBeUsedAsGetterCase2) {
  float s(32); 
  hashed<float> h(s); 
  auto t = h();
  ASSERT_TRUE(t == std::hash<float>{}(s));
}

TEST(ParenOperator, CanBeUsedAsSetter) {
  std::string s("test");
  hashed<std::string> h(s);
  std::string s2("not test");
  h(s2);
  auto t = h();
  ASSERT_TRUE(t == std::hash<std::string>{}("not test"));
}

TEST(ExplicitConversionOperator, IsCorrect) {
  std::string s("test");
  hashed<std::string> h(s);
  std::string s2 = static_cast<std::string>(h);
  ASSERT_TRUE(s == s2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
