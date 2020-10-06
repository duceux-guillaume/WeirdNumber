#include "number.hpp"
#include <gtest/gtest.h>

TEST(Integer, EqualsAndConstructors) {
  ASSERT_EQ(Integer(), 0);
  ASSERT_EQ(Integer(25), 25);
  ASSERT_NE(Integer(25), Integer());
  ASSERT_EQ(Integer(256), 256);
  ASSERT_EQ(Integer(-50), -50);
}

TEST(Integer, Comparisons) {
  ASSERT_GT(Integer(25), Integer(0));
  ASSERT_GE(Integer(25), 0);
  ASSERT_GE(Integer(25), 25);
  ASSERT_NE(Integer(25), -50);
  ASSERT_EQ(Integer(-50), -50);
  ASSERT_EQ(Integer(-50), -Integer(50));
}

TEST(Integer, Addition) {
  ASSERT_EQ(Integer(25) + Integer(25), 50);
  ASSERT_EQ(25 + Integer(25), 50);
  ASSERT_EQ(Integer(25) + 25, 50);
}

TEST(Integer, String) {
  ASSERT_EQ(std::string("25."), std::string(Integer(25)));
  ASSERT_EQ(std::string("-1.0."), std::string(Integer(-256)));
  ASSERT_EQ(std::string("-1.255."), std::string(Integer(-511)));
}
