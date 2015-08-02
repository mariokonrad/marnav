#include <gtest/gtest.h>
#include <marnav/math/vector.hpp>

using namespace marnav::math;

namespace marnav
{
namespace math
{
// instantiate all of them to achieve the right coverage information.
template class vector2<double>;
template class vector3<double>;
template class vector4<double>;
template class vector_n<8, double>;
}
}

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
