#include "gtest/gtest.h"

TEST(blaTest, test1)
{
    ASSERT_EQ(1, 1);
}

TEST(blaTest, test_FAILURE)
{
    ASSERT_FALSE(1 == 0);
}
