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

	EXPECT_EQ(1.0, m[0]);
	EXPECT_EQ(0.0, m[1]);
	EXPECT_EQ(0.0, m[2]);
	EXPECT_EQ(1.0, m[3]);
}

}
