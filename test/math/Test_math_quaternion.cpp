#include <marnav/math/quaternion.hpp>
#include <gtest/gtest.h>
#include <vector>

using namespace marnav::math;

namespace marnav
{
namespace math
{
// instantiate all of them to achieve the right coverage information.
template class quaternion<double>;
}
}

namespace
{

class Test_math_quaternion : public ::testing::Test
{
};

TEST_F(Test_math_quaternion, construction_default)
{
	quat q;

	EXPECT_NEAR(1.0, q[0], 1e-8);
	EXPECT_NEAR(0.0, q[1], 1e-8);
	EXPECT_NEAR(0.0, q[2], 1e-8);
	EXPECT_NEAR(0.0, q[3], 1e-8);

	EXPECT_NEAR(1.0, q.w(), 1e-8);
	EXPECT_NEAR(0.0, q.x(), 1e-8);
	EXPECT_NEAR(0.0, q.y(), 1e-8);
	EXPECT_NEAR(0.0, q.z(), 1e-8);
}

TEST_F(Test_math_quaternion, construction_rotation)
{
	const quat q{90.0, {1.0, 0.0, 0.0}}; // rotation arround x-axis

	const vec3 expected{0.0, 0.0, 1.0};
	const vec3 v = q.rot(vec3{0.0, 1.0, 0.0});

	EXPECT_TRUE((expected == v));
}

TEST_F(Test_math_quaternion, rot_to)
{
	// rotation of 90 deg arround z-axis
	const quaternion<double> q = quaternion<double>::rot_to({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0});

	std::vector<vector3<double>> model = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

	for (auto & v : model) {
		v = q.rot(v);
	}

	EXPECT_TRUE((vector3<double>{0.0, 1.0, 0.0} == model[0]))
		<< model[0].x() << ", " << model[0].y() << ", " << model[0].z();
	EXPECT_TRUE((vector3<double>{-1.0, 0.0, 0.0} == model[1]))
		<< model[1].x() << ", " << model[1].y() << ", " << model[1].z();
	EXPECT_TRUE((vector3<double>{0.0, 0.0, 1.0} == model[2]))
		<< model[2].x() << ", " << model[2].y() << ", " << model[2].z();
}
}
