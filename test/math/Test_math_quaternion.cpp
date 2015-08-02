#include <gtest/gtest.h>
#include <marnav/math/quaternion.hpp>

using namespace marnav::math;

namespace
{

class Test_math_quaternion : public ::testing::Test
{
};

TEST_F(Test_math_quaternion, construction_default)
{
	quaternion q;

	const auto v = q.getvec4();

	EXPECT_EQ(0.0, v[0]);
	EXPECT_EQ(0.0, v[1]);
	EXPECT_EQ(0.0, v[2]);
	EXPECT_EQ(0.0, v[3]);
}

}
