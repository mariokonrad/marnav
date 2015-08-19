#include <gtest/gtest.h>
#include <marnav/math/matrix.hpp>

using namespace marnav::math;

namespace marnav
{
namespace math
{
// instantiate all of them to achieve the right coverage information.
template class matrix2<double>;
template class matrix3<double>;
template class matrix4<double>;
template class matrix_n<8, double>;
}
}

namespace
{

class Test_math_matrix : public ::testing::Test
{
};

TEST_F(Test_math_matrix, mat2_construction_default)
{
	mat2 m;

	EXPECT_NEAR(1.0, m[0], 1e-8);
	EXPECT_NEAR(0.0, m[1], 1e-8);
	EXPECT_NEAR(0.0, m[2], 1e-8);
	EXPECT_NEAR(1.0, m[3], 1e-8);
}

TEST_F(Test_math_matrix, mat2_comparison_equal)
{
	mat2 m1;
	mat2 m2;
	mat2 m3{1.0, 2.0, 3.0, 4.0};

	EXPECT_TRUE(m1 == m1);
	EXPECT_TRUE(m2 == m2);
	EXPECT_TRUE(m3 == m3);

	EXPECT_TRUE(m1 == m2);
	EXPECT_TRUE(m2 == m1);
	EXPECT_FALSE(m1 == m3);
	EXPECT_FALSE(m2 == m3);
}

}
