#include <gtest/gtest.h>
#include <marnav/math/vector.hpp>

#include <cmath>

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

	EXPECT_NEAR(0.0, v[0], 1e-8);
	EXPECT_NEAR(0.0, v[1], 1e-8);
}

TEST_F(Test_math_vector, vec2_construction_uniform)
{
	vec2 v{1.0, 2.0};

	EXPECT_NEAR(1.0, v[0], 1e-8);
	EXPECT_NEAR(2.0, v[1], 1e-8);
}

TEST_F(Test_math_vector, vec2_construction_comparison_equal)
{
	vec2 v0{1.0, 2.0};
	vec2 v1{1.0, 2.0};
	vec2 v2{0.0, 2.0};
	vec2 v3{1.0, 0.0};

	EXPECT_TRUE(v0 == v0);
	EXPECT_TRUE(v0 == v1);
	EXPECT_FALSE(v0 == v2);
	EXPECT_FALSE(v0 == v3);

	EXPECT_TRUE(v1 == v1);
	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v1 == v3);

	EXPECT_TRUE(v2 == v2);
	EXPECT_FALSE(v2 == v3);

	EXPECT_TRUE(v3 == v3);
}

TEST_F(Test_math_vector, vec2_construction_comparison_not_equal)
{
	vec2 v0{1.0, 2.0};
	vec2 v1{1.0, 2.0};
	vec2 v2{0.0, 2.0};
	vec2 v3{1.0, 0.0};

	EXPECT_FALSE(v0 != v0);
	EXPECT_FALSE(v0 != v1);
	EXPECT_TRUE(v0 != v2);
	EXPECT_TRUE(v0 != v3);

	EXPECT_FALSE(v1 != v1);
	EXPECT_TRUE(v1 != v2);
	EXPECT_TRUE(v1 != v3);

	EXPECT_FALSE(v2 != v2);
	EXPECT_TRUE(v2 != v3);

	EXPECT_FALSE(v3 != v3);
}

TEST_F(Test_math_vector, vec2_components)
{
	vec2 v{1.0, 2.0};

	EXPECT_NEAR(1.0, v.x(), 1e-8);
	EXPECT_NEAR(2.0, v.y(), 1e-8);
}

TEST_F(Test_math_vector, vec2_make_from_polar)
{
	static const std::vector<double> TESTS = {0.0, 1.0, 30.0, 45.0, 89.0, 90.0, 91.0, 179.0,
		180.0, 181.0, 269.0, 270.0, 271.0, 359.0, 360.0};

	for (auto test : TESTS) {
		vec2 v = vec2::make_from_polar(1.0, test);

		EXPECT_NEAR(cos(test * M_PI / 180.0), v[0], 1e-9);
		EXPECT_NEAR(sin(test * M_PI / 180.0), v[1], 1e-9);
	}
}

TEST_F(Test_math_vector, vec2_phi)
{
	static const std::vector<double> TESTS = {0.0, 1.0, 30.0, 45.0, 89.0, 90.0, 91.0, 179.0,
		180.0, 181.0, 269.0, 270.0, 271.0, 359.0, 360.0};

	for (auto test : TESTS) {
		const vec2 v = vec2::make_from_polar(1.0, test);
		EXPECT_NEAR(test * M_PI / 180.0, v.phi(), 1e-7) << "test:" << test << ", v=(" << v[0]
														<< ", " << v[1] << ")";
	}
}

TEST_F(Test_math_vector, vec2_phi_deg)
{
	static const std::vector<double> TESTS = {0.0, 1.0, 30.0, 45.0, 89.0, 90.0, 91.0, 179.0,
		180.0, 181.0, 269.0, 270.0, 271.0, 359.0, 360.0};

	for (auto test : TESTS) {
		const vec2 v = vec2::make_from_polar(1.0, test);
		EXPECT_NEAR(test, v.phi_deg(), 1e-7) << "test:" << test << ", v=(" << v[0] << ", "
											 << v[1] << ")";
	}
}

TEST_F(Test_math_vector, vec2_length)
{
	EXPECT_NEAR(1.0 * sqrt(2.0), (vec2{1.0, 1.0}.length()), 1e-7);
	EXPECT_NEAR(2.0 * sqrt(2.0), (vec2{2.0, 2.0}.length()), 1e-7);
	EXPECT_NEAR(1.0, (vec2{1.0, 0.0}.length()), 1e-7);
	EXPECT_NEAR(1.0, (vec2{0.0, 1.0}.length()), 1e-7);
	EXPECT_NEAR(2.0, (vec2{2.0, 0.0}.length()), 1e-7);
	EXPECT_NEAR(2.0, (vec2{0.0, 2.0}.length()), 1e-7);
}

TEST_F(Test_math_vector, vec2_length2)
{
	EXPECT_NEAR(2.0, (vec2{1.0, 1.0}.length2()), 1e-7);
	EXPECT_NEAR(8.0, (vec2{2.0, 2.0}.length2()), 1e-7);
	EXPECT_NEAR(1.0, (vec2{1.0, 0.0}.length2()), 1e-7);
	EXPECT_NEAR(1.0, (vec2{0.0, 1.0}.length2()), 1e-7);
	EXPECT_NEAR(4.0, (vec2{2.0, 0.0}.length2()), 1e-7);
	EXPECT_NEAR(4.0, (vec2{0.0, 2.0}.length2()), 1e-7);
}

TEST_F(Test_math_vector, vecn_initializer_list)
{
	{
		vector_n<5, double> v{1, 2, 3, 4, 5};
		EXPECT_NEAR(1.0, v[0], 1e-8);
		EXPECT_NEAR(2.0, v[1], 1e-8);
		EXPECT_NEAR(3.0, v[2], 1e-8);
		EXPECT_NEAR(4.0, v[3], 1e-8);
		EXPECT_NEAR(5.0, v[4], 1e-8);
	}
#if !defined(NDEBUG)
	{
		EXPECT_DEATH((vector_n<5, double>{1, 2, 3, 4}), ".*");
	}
#endif
}

TEST_F(Test_math_vector, nullify)
{
	{
		vector2<double> v{
			std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()};
		nullify(v);
		EXPECT_NEAR(0.0, v.x(), 1e-5);
		EXPECT_NEAR(0.0, v.y(), 1e-5);
	}
	{
		vector2<double> v{2.0, 2.0};
		nullify(v);
		EXPECT_NEAR(2.0, v.x(), 1e-5);
		EXPECT_NEAR(2.0, v.y(), 1e-5);
	}
	{
		vector3<double> v{std::numeric_limits<double>::epsilon(),
			std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()};
		nullify(v);
		EXPECT_NEAR(0.0, v.x(), 1e-5);
		EXPECT_NEAR(0.0, v.y(), 1e-5);
		EXPECT_NEAR(0.0, v.z(), 1e-5);
	}
	{
		vector3<double> v{2.0, 2.0, 2.0};
		nullify(v);
		EXPECT_NEAR(2.0, v.x(), 1e-5);
		EXPECT_NEAR(2.0, v.y(), 1e-5);
		EXPECT_NEAR(2.0, v.z(), 1e-5);
	}
	{
		vector4<double> v{std::numeric_limits<double>::epsilon(),
			std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon(),
			std::numeric_limits<double>::epsilon()};
		nullify(v);
		EXPECT_NEAR(0.0, v[0], 1e-5);
		EXPECT_NEAR(0.0, v[1], 1e-5);
		EXPECT_NEAR(0.0, v[2], 1e-5);
		EXPECT_NEAR(0.0, v[3], 1e-5);
	}
	{
		vector4<double> v{2.0, 2.0, 2.0, 2.0};
		nullify(v);
		EXPECT_NEAR(2.0, v[0], 1e-5);
		EXPECT_NEAR(2.0, v[1], 1e-5);
		EXPECT_NEAR(2.0, v[2], 1e-5);
		EXPECT_NEAR(2.0, v[3], 1e-5);
	}
	{
		vector_n<5, double> v{std::numeric_limits<double>::epsilon(),
			std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon(),
			std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()};
		nullify(v);
		EXPECT_NEAR(0.0, v[0], 1e-5);
		EXPECT_NEAR(0.0, v[1], 1e-5);
		EXPECT_NEAR(0.0, v[2], 1e-5);
		EXPECT_NEAR(0.0, v[3], 1e-5);
		EXPECT_NEAR(0.0, v[4], 1e-5);
	}
	{
		vector_n<5, double> v{2.0, 2.0, 2.0, 2.0, 2.0};
		nullify(v);
		EXPECT_NEAR(2.0, v[0], 1e-5);
		EXPECT_NEAR(2.0, v[1], 1e-5);
		EXPECT_NEAR(2.0, v[2], 1e-5);
		EXPECT_NEAR(2.0, v[3], 1e-5);
		EXPECT_NEAR(2.0, v[4], 1e-5);
	}
}

TEST_F(Test_math_vector, vec2_normalize)
{
	{
		const vector2<double> expected{1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)};
		vector2<double> v{2.0, 2.0};
		v.normalize();
		EXPECT_EQ(expected, v);
	}
	{
		const vector2<double> expected{2.0 / std::sqrt(2.0), 2.0 / std::sqrt(2.0)};
		vector2<double> v{2.0, 2.0};
		v.normalize(2.0);
		EXPECT_EQ(expected, v);
	}

	{
		const vector2<double> expected{1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)};
		const vector2<double> v{2.0, 2.0};
		vector2<double> v1 = v.normalize();
		EXPECT_EQ(expected, v1);
	}
	{
		const vector2<double> expected{2.0 / std::sqrt(2.0), 2.0 / std::sqrt(2.0)};
		const vector2<double> v{2.0, 2.0};
		vector2<double> v1 = v.normalize(2.0);
		EXPECT_EQ(expected, v1);
	}
}

TEST_F(Test_math_vector, vec3_normalize)
{
	{
		const vector3<double> expected{
			1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0)};
		vector3<double> v{2.0, 2.0, 2.0};
		v.normalize();
		EXPECT_EQ(expected, v);
	}
	{
		const vector3<double> expected{
			2.0 / std::sqrt(3.0), 2.0 / std::sqrt(3.0), 2.0 / std::sqrt(3.0)};
		vector3<double> v{2.0, 2.0, 2.0};
		v.normalize(2.0);
		EXPECT_EQ(expected, v);
	}

	{
		const vector3<double> expected{
			1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0)};
		const vector3<double> v{2.0, 2.0, 2.0};
		vector3<double> v1 = v.normalize();
		EXPECT_EQ(expected, v1);
	}
	{
		const vector3<double> expected{
			2.0 / std::sqrt(3.0), 2.0 / std::sqrt(3.0), 2.0 / std::sqrt(3.0)};
		const vector3<double> v{2.0, 2.0, 2.0};
		vector3<double> v1 = v.normalize(2.0);
		EXPECT_EQ(expected, v1);
	}
}

TEST_F(Test_math_vector, vec3_make_from_sphere)
{
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 0.0);
		EXPECT_NEAR(0.0, v[0], 1e-7);
		EXPECT_NEAR(0.0, v[1], 1e-7);
		EXPECT_NEAR(1.0, v[2], 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 90.0, 0.0);
		EXPECT_NEAR(1.0, v[0], 1e-7);
		EXPECT_NEAR(0.0, v[1], 1e-7);
		EXPECT_NEAR(0.0, v[2], 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 90.0);
		EXPECT_NEAR(0.0, v[0], 1e-7);
		EXPECT_NEAR(0.0, v[1], 1e-7);
		EXPECT_NEAR(1.0, v[2], 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 45.0, 45.0);
		EXPECT_NEAR(0.5, v[0], 1e-7);
		EXPECT_NEAR(0.5, v[1], 1e-7);
		EXPECT_NEAR(1.0 / std::sqrt(2.0), v[2], 1e-7);
	}
}

TEST_F(Test_math_vector, vec3_get_sphere_r)
{
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 0.0);
		EXPECT_NEAR(1.0, v.get_sphere_r(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(0.5, 90.0, 0.0);
		EXPECT_NEAR(0.5, v.get_sphere_r(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 90.0);
		EXPECT_NEAR(1.0, v.get_sphere_r(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(2.0, 45.0, 45.0);
		EXPECT_NEAR(2.0, v.get_sphere_r(), 1e-7);
	}
	{
		const vec3 v{0.5, 0.5, 1.0 / std::sqrt(2.0)};
		EXPECT_NEAR(1.0, v.get_sphere_r(), 1e-7);
	}
}

TEST_F(Test_math_vector, vec3_get_sphere_theta)
{
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 0.0);
		EXPECT_NEAR(0.0, v.get_sphere_theta(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 90.0, 0.0);
		EXPECT_NEAR(90.0, v.get_sphere_theta(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 90.0);
		EXPECT_NEAR(0.0, v.get_sphere_theta(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 45.0, 45.0);
		EXPECT_NEAR(45.0, v.get_sphere_theta(), 1e-7);
	}
	{
		const vec3 v{0.5, 0.5, 1.0 / std::sqrt(2.0)};
		EXPECT_NEAR(45.0, v.get_sphere_theta(), 1e-7);
	}
}

TEST_F(Test_math_vector, vec3_get_sphere_phi)
{
	{
		const auto v = vec3::make_from_sphere(1.0, 0.0, 0.0);
		EXPECT_NEAR(0.0, v.get_sphere_phi(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 90.0, 0.0);
		EXPECT_NEAR(00.0, v.get_sphere_phi(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 90.0, 90.0);
		EXPECT_NEAR(90.0, v.get_sphere_phi(), 1e-7);
	}
	{
		const auto v = vec3::make_from_sphere(1.0, 45.0, 45.0);
		EXPECT_NEAR(45.0, v.get_sphere_phi(), 1e-7);
	}
	{
		const vec3 v{1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0)};
		EXPECT_NEAR(45.0, v.get_sphere_phi(), 1e-7);
	}
}

TEST_F(Test_math_vector, vec3_operator_plus)
{
	{
		const vec3 a{0.0, 0.0, 0.0};
		const vec3 b{1.0, 2.0, 3.0};

		const auto result = a + b;

		EXPECT_NEAR(1.0, result[0], 1e-9);
		EXPECT_NEAR(2.0, result[1], 1e-9);
		EXPECT_NEAR(3.0, result[2], 1e-9);
	}
	{
		const vec3 a{0.0, 0.0, 0.0};
		const vec3 b{-1.0, -2.0, -3.0};

		const auto result = a + b;

		EXPECT_NEAR(-1.0, result[0], 1e-9);
		EXPECT_NEAR(-2.0, result[1], 1e-9);
		EXPECT_NEAR(-3.0, result[2], 1e-9);
	}
}

TEST_F(Test_math_vector, vec3_operator_minus)
{
	{
		const vec3 a{0.0, 0.0, 0.0};
		const vec3 b{1.0, 2.0, 3.0};

		const auto result = a - b;

		EXPECT_NEAR(-1.0, result[0], 1e-9);
		EXPECT_NEAR(-2.0, result[1], 1e-9);
		EXPECT_NEAR(-3.0, result[2], 1e-9);
	}
	{
		const vec3 a{0.0, 0.0, 0.0};
		const vec3 b{-1.0, -2.0, -3.0};

		const auto result = a - b;

		EXPECT_NEAR(1.0, result[0], 1e-9);
		EXPECT_NEAR(2.0, result[1], 1e-9);
		EXPECT_NEAR(3.0, result[2], 1e-9);
	}
}
}
