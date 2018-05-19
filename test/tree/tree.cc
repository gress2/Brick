#include <string>

#include "brick.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::tree::tree<T>;

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
