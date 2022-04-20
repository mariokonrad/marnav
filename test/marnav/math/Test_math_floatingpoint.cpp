#include <marnav/math/floatingpoint.hpp>
#include <gtest/gtest.h>

using namespace marnav::math;

namespace
{
TEST(Test_math_floatingpoint, is_zero)
{
	EXPECT_TRUE(is_zero<float>(0.0f));
	EXPECT_TRUE(is_zero<double>(0.0));
	EXPECT_TRUE(is_zero<long double>(0.0));
}

TEST(Test_math_floatingpoint, is_zero_epsilon)
{
	EXPECT_TRUE(is_zero<float>(std::numeric_limits<float>::epsilon()));
	EXPECT_TRUE(is_zero<double>(std::numeric_limits<double>::epsilon()));
	EXPECT_TRUE(is_zero<long double>(std::numeric_limits<long double>::epsilon()));
}

TEST(Test_math_floatingpoint, is_zero_two_epsilon)
{
	EXPECT_FALSE(is_zero<float>(2.0f * std::numeric_limits<float>::epsilon()));
	EXPECT_FALSE(is_zero<double>(2.0 * std::numeric_limits<double>::epsilon()));
	EXPECT_FALSE(is_zero<long double>(2.0 * std::numeric_limits<long double>::epsilon()));
}

TEST(Test_math_floatingpoint, is_same_zero_zero)
{
	EXPECT_TRUE(is_same<float>(0.0f, 0.0f));
	EXPECT_TRUE(is_same<double>(0.0, 0.0));
	EXPECT_TRUE(is_same<long double>(0.0, 0.0));
}

TEST(Test_math_floatingpoint, is_same_zero_epsilon)
{
	EXPECT_TRUE(is_same<float>(0.0f, std::numeric_limits<float>::epsilon()));
	EXPECT_TRUE(is_same<double>(0.0, std::numeric_limits<double>::epsilon()));
	EXPECT_TRUE(is_same<long double>(0.0, std::numeric_limits<long double>::epsilon()));
}

TEST(Test_math_floatingpoint, is_same_zero_two_epsilon)
{
	EXPECT_FALSE(is_same<float>(0.0f, 2.0f * std::numeric_limits<float>::epsilon()));
	EXPECT_FALSE(is_same<double>(0.0, 2.0 * std::numeric_limits<double>::epsilon()));
	EXPECT_FALSE(is_same<long double>(0.0, 2.0 * std::numeric_limits<long double>::epsilon()));
}

TEST(Test_math_floatingpoint, is_same_zero_one)
{
	EXPECT_FALSE(is_same<float>(0.0f, 1.0f));
	EXPECT_FALSE(is_same<double>(0.0, 1.0));
	EXPECT_FALSE(is_same<long double>(0.0, 1.0));
}

TEST(Test_math_floatingpoint, is_same_pos_neg)
{
	EXPECT_FALSE(is_same<float>(-1.0f, 1.0f));
	EXPECT_FALSE(is_same<double>(-1.0, 1.0));
	EXPECT_FALSE(is_same<long double>(-1.0, 1.0));
}
}
