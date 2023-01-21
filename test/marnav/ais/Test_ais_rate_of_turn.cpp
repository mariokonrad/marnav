#include <marnav/ais/rate_of_turn.hpp>
#include <gtest/gtest.h>

namespace
{
template <class T>
constexpr T sqr(T x)
{
	return x * x;
}

using marnav::ais::rate_of_turn;

class test_ais_rate_of_turn : public ::testing::Test
{
};

TEST_F(test_ais_rate_of_turn, construction_default)
{
	rate_of_turn r;
	EXPECT_EQ(rate_of_turn::no_information_available, r.raw());
}

TEST_F(test_ais_rate_of_turn, construction_explicit_raw_data)
{
	const rate_of_turn::value_type a = rate_of_turn::no_information_available;
	rate_of_turn r(a);
	EXPECT_EQ(rate_of_turn::no_information_available, r.raw());
}

TEST_F(test_ais_rate_of_turn, construction_angle_throwing)
{
	EXPECT_ANY_THROW(rate_of_turn(1000.0));
	EXPECT_ANY_THROW(rate_of_turn(714.35)); // approx. the nearest value to +0.0 that throws
	EXPECT_ANY_THROW(rate_of_turn(-1000.0));
	EXPECT_ANY_THROW(rate_of_turn(-714.35)); // approx. the nearest value to -0.0 that throws
}

TEST_F(test_ais_rate_of_turn, construction_angle_not_turning)
{
	const rate_of_turn r(0.0);
	EXPECT_TRUE(r.is_not_turning());
}

TEST_F(test_ais_rate_of_turn, construction_angle_read_back)
{
	static constexpr double data[] = {1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0};

	for (const auto val : data) {
		const rate_of_turn r(val);
		EXPECT_NEAR(r.value(), val, 2.0);
	}
}

TEST_F(test_ais_rate_of_turn, available)
{
	{
		const rate_of_turn::value_type val = 1;
		rate_of_turn r(val);
		EXPECT_TRUE(r.available());
	}
	{
		rate_of_turn r;
		EXPECT_FALSE(r.available());
	}
}

TEST_F(test_ais_rate_of_turn, not_turning)
{
	{
		const rate_of_turn::value_type val = 1;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_not_turning());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::not_turning;
		rate_of_turn r(val);
		EXPECT_TRUE(r.is_not_turning());
	}
}

TEST_F(test_ais_rate_of_turn, more_5deg_per_30s_right)
{
	{
		const rate_of_turn::value_type val = 1;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_more_5deg30s_right());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_right;
		rate_of_turn r(val);
		EXPECT_TRUE(r.is_more_5deg30s_right());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_right;
		rate_of_turn r(val);
		EXPECT_EQ(rate_of_turn::more_5deg_per_30s_right, r.raw());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_left;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_more_5deg30s_right());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::not_turning;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_more_5deg30s_right());
	}
	{
		rate_of_turn r;
		EXPECT_FALSE(r.is_more_5deg30s_right());
	}
}

TEST_F(test_ais_rate_of_turn, more_5deg_per_30s_left)
{
	{
		const rate_of_turn::value_type val = 1;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_more_5deg30s_left());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_right;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_more_5deg30s_left());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_left;
		rate_of_turn r(val);
		EXPECT_TRUE(r.is_more_5deg30s_left());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_left;
		rate_of_turn r(val);
		EXPECT_EQ(rate_of_turn::more_5deg_per_30s_left, r.raw());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::not_turning;
		rate_of_turn r(val);
		EXPECT_FALSE(r.is_more_5deg30s_left());
	}
	{
		rate_of_turn r;
		EXPECT_FALSE(r.is_more_5deg30s_left());
	}
}

TEST_F(test_ais_rate_of_turn, value)
{
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_right;
		rate_of_turn r(val);
		EXPECT_ANY_THROW(r.value());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::more_5deg_per_30s_left;
		rate_of_turn r(val);
		EXPECT_ANY_THROW(r.value());
	}
	{
		rate_of_turn r;
		EXPECT_ANY_THROW(r.value());
	}
	{
		const rate_of_turn::value_type val = rate_of_turn::not_turning;
		rate_of_turn r(val);
		EXPECT_NEAR(r.value(), 0.0, 1.0e-5);
	}
	{
		const rate_of_turn::value_type val = 126;
		rate_of_turn r(val);
		EXPECT_NEAR(r.value(), 708, 1.0);
	}
	{
		const rate_of_turn::value_type val = -126;
		rate_of_turn r(val);
		EXPECT_NEAR(r.value(), -708.0, 1.0);
	}
	{
		const rate_of_turn::value_type val = 1;
		rate_of_turn r(val);
		EXPECT_NEAR(r.value(), sqr(1.0 / 4.733), 0.001);
	}
}
}
