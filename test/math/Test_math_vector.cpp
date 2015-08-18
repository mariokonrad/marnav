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
	{
		EXPECT_DEATH((vector_n<5, double>{1, 2, 3, 4}), ".*");
	}
}

TEST_F(Test_math_vector, vec2_normalize)
{
	{
		const vector2<double> expected{1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)};
		vector2<double> v{2.0, 2.0};
		v.normalize();
		EXPECT_NEAR(expected.x(), v.x(), 1e-5);
		EXPECT_NEAR(expected.y(), v.y(), 1e-5);
	}
}

TEST_F(Test_math_vector, vec2_nullify)
{
	{
		vector2<double> v{2.0, 2.0};
		v.nullify();
		EXPECT_NEAR(2.0, v.x(), 1e-5);
		EXPECT_NEAR(2.0, v.y(), 1e-5);
	}
	{
		vector2<double> v{
			std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()};
		v.nullify();
		EXPECT_NEAR(0.0, v.x(), 1e-5);
		EXPECT_NEAR(0.0, v.y(), 1e-5);
	}
}
}
