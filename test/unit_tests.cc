#include "gtest/gtest.h"

class ASTTest : public ::testing::Test {
protected:
  virtual void SetUp() {}
};

TEST_F(ASTTest, UnitTest) {
  ASSERT_EQ(true, true);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
