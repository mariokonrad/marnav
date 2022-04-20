#include <marnav/nmea/version.hpp>
#include <gtest/gtest.h>

namespace
{
using marnav::nmea::version;

class Test_nmea_version : public ::testing::Test
{
};

TEST_F(Test_nmea_version, properties)
{
	using type = marnav::nmea::version;

	// construction

	EXPECT_TRUE(std::is_default_constructible_v<type>);
	EXPECT_FALSE(std::is_trivially_default_constructible_v<type>);
	EXPECT_TRUE(std::is_nothrow_default_constructible_v<type>);

	EXPECT_TRUE((std::is_constructible_v<type, type::value_type, type::value_type>));
	EXPECT_FALSE((std::is_trivially_constructible_v<type, type::value_type, type::value_type>));
	EXPECT_TRUE((std::is_nothrow_constructible_v<type, type::value_type, type::value_type>));

	EXPECT_TRUE(std::is_copy_constructible_v<type>);
	EXPECT_TRUE(std::is_trivially_copy_constructible_v<type>);
	EXPECT_TRUE(std::is_nothrow_copy_constructible_v<type>);

	EXPECT_TRUE(std::is_move_constructible_v<type>);
	EXPECT_TRUE(std::is_trivially_move_constructible_v<type>);
	EXPECT_TRUE(std::is_nothrow_move_constructible_v<type>);

	// destruction

	EXPECT_TRUE(std::is_destructible_v<type>);

	// assignable

	EXPECT_TRUE(std::is_copy_assignable_v<type>);
	EXPECT_TRUE(std::is_nothrow_copy_assignable_v<type>);
	EXPECT_TRUE(std::is_trivially_copy_assignable_v<type>);

	EXPECT_TRUE(std::is_move_assignable_v<type>);
	EXPECT_TRUE(std::is_trivially_move_assignable_v<type>);
	EXPECT_TRUE(std::is_nothrow_move_assignable_v<type>);
}

TEST_F(Test_nmea_version, default_construction)
{
	const auto v = version{};

	EXPECT_EQ(0, v.major());
	EXPECT_EQ(0, v.minor());
}

TEST_F(Test_nmea_version, construction)
{
	const auto v = version{4, 1};

	EXPECT_EQ(4, v.major());
	EXPECT_EQ(1, v.minor());
}

TEST_F(Test_nmea_version, comparison_equal)
{
	EXPECT_TRUE(version(1, 0) == version(1, 0));
	EXPECT_TRUE(version(2, 3) == version(2, 3));
	EXPECT_TRUE(version(4, 0) == version(4, 0));
	EXPECT_TRUE(version(4, 1) == version(4, 1));

	EXPECT_FALSE(version(2, 0) == version(1, 0));
	EXPECT_FALSE(version(3, 3) == version(2, 3));
	EXPECT_FALSE(version(5, 0) == version(4, 0));
	EXPECT_FALSE(version(4, 2) == version(4, 1));
}

TEST_F(Test_nmea_version, comparison_not_equal)
{
	EXPECT_FALSE(version(1, 0) != version(1, 0));
	EXPECT_FALSE(version(2, 3) != version(2, 3));
	EXPECT_FALSE(version(4, 0) != version(4, 0));
	EXPECT_FALSE(version(4, 1) != version(4, 1));

	EXPECT_TRUE(version(2, 0) != version(1, 0));
	EXPECT_TRUE(version(3, 3) != version(2, 3));
	EXPECT_TRUE(version(5, 0) != version(4, 0));
	EXPECT_TRUE(version(4, 2) != version(4, 1));
}

TEST_F(Test_nmea_version, comparison_less)
{
	EXPECT_TRUE(version(1, 0) < version(2, 0));
	EXPECT_TRUE(version(2, 2) < version(2, 3));
	EXPECT_TRUE(version(4, 0) < version(4, 1));
	EXPECT_TRUE(version(4, 1) < version(5, 0));

	EXPECT_FALSE(version(2, 0) < version(1, 0));
	EXPECT_FALSE(version(3, 3) < version(2, 3));
	EXPECT_FALSE(version(4, 0) < version(4, 0));
	EXPECT_FALSE(version(4, 2) < version(4, 1));
}
}
