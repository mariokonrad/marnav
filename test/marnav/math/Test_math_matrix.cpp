#include <marnav/math/matrix.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

using namespace marnav::math;

namespace marnav::math
{
// instantiate all of them to achieve the right coverage information.
template class matrix2<double>;
template class matrix3<double>;
template class matrix4<double>;
template class matrix_n<8, double>;
}

namespace
{

template <class T>
std::ostream & dump(std::ostream & os, const std::string & title, const T & m)
{
	os << "\n" << title << "\n";

	for (typename T::size_type i = 0; i < T::dimension; ++i) {
		for (typename T::size_type j = 0; j < T::dimension; ++j) {
			os << m[i * T::dimension + j] << " ";
		}
		os << "\n";
	}

	os << "\n";
	return os;
}

// This comparison uses a user definable threshold than epsilon to compare values.
template <class T>
bool equals(const T & a, const T & b,
	typename T::value_type threshold = std::numeric_limits<typename T::value_type>::epsilon())
{
	assert(threshold >= 0);

	using iterator = decltype(T::dimension);

	for (typename std::remove_cv<iterator>::type i = 0; i < T::dimension * T::dimension; ++i)
		if (std::abs(a[i] - b[i]) > threshold)
			return false;
	return true;
}

class test_math_matrix : public ::testing::Test
{
};

TEST_F(test_math_matrix, mat2_construction_default)
{
	mat2 m;

	EXPECT_NEAR(1.0, m[0], 1e-8);
	EXPECT_NEAR(0.0, m[1], 1e-8);
	EXPECT_NEAR(0.0, m[2], 1e-8);
	EXPECT_NEAR(1.0, m[3], 1e-8);
}

TEST_F(test_math_matrix, mat2_comparison_equal)
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

TEST_F(test_math_matrix, mat2_inverse_of_identity)
{
	const mat2 m1;
	const mat2 m2 = m1.inv();

	EXPECT_EQ(m1, m2);
}

TEST_F(test_math_matrix, mat2_inverse)
{
	const mat2 m1{1.0, 2.0, 3.0, 4.0};
	const mat2 m2 = m1.inv();
	const mat2 expected{-2, 1, 3.0 / 2.0, -0.5};

	EXPECT_EQ(expected, m2);
}

TEST_F(test_math_matrix, mat2_inverse_multiply)
{
	const mat2 m1{1.0, 2.0, 3.0, 4.0};
	const mat2 m2 = m1.inv();
	const mat2 expected; // identity

	EXPECT_TRUE((expected == (m1 * m2)));
	EXPECT_TRUE((expected == (m2 * m1)));
}

TEST_F(test_math_matrix, mat3_inverse_of_identity)
{
	const mat3 m1;
	const mat3 m2 = m1.inv();

	EXPECT_EQ(m1, m2);
}

TEST_F(test_math_matrix, mat3_inverse)
{
	const mat3 m1{1.0, 2.0, 3.0, 1.5, 0.5, 0.0, -0.5, 2.0, 1.5};
	const mat3 m2 = m1.inv();
	const mat3 expected{1.0 / 8.0, 1.0 / 2.0, -1.0 / 4.0, -3.0 / 8.0, 1.0 / 2.0, 3.0 / 4.0,
		13.0 / 24.0, -1.0 / 2.0, -5.0 / 12.0};

	EXPECT_EQ(expected, m2);
}

TEST_F(test_math_matrix, mat3_inverse_multiply)
{
	const mat3 m1{1.0, 2.0, 3.0, 1.5, 0.5, 0.0, -0.5, 2.0, 1.5};
	const mat3 m2 = m1.inv();
	const mat3 expected; // identity

	const mat3 result1 = m1 * m2;
	const mat3 result2 = m2 * m1;

	EXPECT_TRUE(equals(expected, result1, 1e-9));
	EXPECT_TRUE(equals(expected, result2, 1e-9));
}

TEST_F(test_math_matrix, mat2_add)
{
	const mat2 m1{1.0, 2.0, 3.0, 4.0};
	const mat2 m2{10.0, 20.0, 30.0, 40.0};
	const mat2 expected{11.0, 22.0, 33.0, 44.0};

	EXPECT_TRUE((expected == m1 + m2));
	EXPECT_TRUE((expected == m2 + m1));
}

TEST_F(test_math_matrix, mat2_sub)
{
	const mat2 m1{1.0, 2.0, 3.0, 4.0};
	const mat2 m2{10.0, 20.0, 30.0, 40.0};
	const mat2 expected{-9.0, -18.0, -27.0, -36.0};

	EXPECT_TRUE((expected == m1 - m2));
}

TEST_F(test_math_matrix, mat2_transpose)
{
	const mat2 m1{1.0, 2.0, 3.0, 4.0};
	const mat2 expected{1.0, 3.0, 2.0, 4.0};

	EXPECT_TRUE((expected == m1.transpose()));
}

TEST_F(test_math_matrix, mat2_trace)
{
	EXPECT_NEAR(5.0, (mat2{1.0, 2.0, 3.0, 4.0}.trace()), 1e-8);
	EXPECT_NEAR(6.0, (mat2{1.5, 2.5, 3.5, 4.5}.trace()), 1e-8);
	EXPECT_NEAR(2.0, (mat2{}.trace()), 1e-8);
}
}
