#include <gtest/gtest.h>
#include <marnav/math/vector.hpp>

using namespace marnav::math;

namespace
{

class Test_math_vector : public ::testing::Test
{
};

TEST_F(Test_math_vector, vec2_construction_default)
{
	vec2 v;

	EXPECT_EQ(0.0, v[0]);
	EXPECT_EQ(0.0, v[1]);
}

}
