#include "brick.hpp"
#include "gtest/gtest.h"

class TreeFixture : public ::testing::Test {
  protected:
    virtual void SetUp() {}
};

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
