#include <gtest/gtest.h>
#include <marnav/math/matrix.hpp>

using namespace marnav::math;

namespace
{

class Test_math_matrix : public ::testing::Test
{
};

TEST_F(Test_math_matrix, mat2_construction_default)
{
	mat2 m;

	const mat2::value_type * v = m.get();

	EXPECT_EQ(1.0, v[0]);
	EXPECT_EQ(0.0, v[1]);
	EXPECT_EQ(0.0, v[2]);
	EXPECT_EQ(1.0, v[3]);
}

}
