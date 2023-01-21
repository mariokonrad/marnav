#include <marnav/nmea/angle.hpp>
#include <gtest/gtest.h>

namespace
{
class test_nmea_angle : public ::testing::Test
{
};

TEST_F(test_nmea_angle, parse_empty_string)
{
	const auto expected = marnav::geo::angle{0.0};

	auto result = marnav::nmea::parse_latitude("");

	EXPECT_DOUBLE_EQ(expected, result);
}

TEST_F(test_nmea_angle, parse_invalid_string)
{
	EXPECT_ANY_THROW(marnav::nmea::parse_latitude("001.abcdefgh"));
}

TEST_F(test_nmea_angle, parse_invalid_minutes)
{
	EXPECT_ANY_THROW(marnav::nmea::parse_latitude("00161.000"));
}
}
