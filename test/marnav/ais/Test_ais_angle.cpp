#include <marnav/ais/angle.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace
{
using namespace marnav;

class test_ais_angle : public ::testing::Test
{
public:
	struct test_case {
		double angle;
		uint32_t angle_minutes;
	};

	static const std::vector<test_case> LATITUDE_CASES;
	static const std::vector<test_case> LONGITUDE_CASES;
};

// clang-format off
const std::vector<test_ais_angle::test_case> test_ais_angle::LATITUDE_CASES = {
	{  0.00123,        738},
	{  0.01234,       7404},
	{  0.1234,       74040},
	{  1.234,       740400},
	{  0.0,              0},
	{  4.407047,   2644228},
	{-23.395383, 120180498},
};

const std::vector<test_ais_angle::test_case> test_ais_angle::LONGITUDE_CASES = {
	{   0.00123,        738},
	{   0.01234,       7404},
	{   0.1234,       74040},
	{   1.234,       740400},
	{  12.345,      7407000},
	{   0.0,              0},
	{   4.407047,   2644228},
	{-123.395383, 194398226},
};
// clang-format on

TEST_F(test_ais_angle, to_geo_latitude)
{
	for (auto const & test : LATITUDE_CASES) {
		const geo::latitude expected{test.angle};
		const geo::latitude converted
			= ais::to_geo_latitude(test.angle_minutes, 27, ais::angle_scale::I4);
		EXPECT_DOUBLE_EQ(expected, converted);
	}
}

TEST_F(test_ais_angle, to_latitude_minutes)
{
	for (auto const & test : LATITUDE_CASES) {
		const uint32_t expected{test.angle_minutes};
		const uint32_t converted
			= ais::to_latitude_minutes(geo::latitude{test.angle}, 27, ais::angle_scale::I4);
		EXPECT_EQ(expected, converted);
	}
}

TEST_F(test_ais_angle, to_geo_longitude)
{
	for (auto const & test : LONGITUDE_CASES) {
		const geo::longitude expected{test.angle};
		const geo::longitude converted
			= ais::to_geo_longitude(test.angle_minutes, 28, ais::angle_scale::I4);
		EXPECT_DOUBLE_EQ(expected, converted);
	}
}

TEST_F(test_ais_angle, to_longitude_minutes)
{
	for (auto const & test : LONGITUDE_CASES) {
		const uint32_t expected{test.angle_minutes};
		const uint32_t converted
			= ais::to_longitude_minutes(geo::longitude{test.angle}, 28, ais::angle_scale::I4);
		EXPECT_EQ(expected, converted);
	}
}
}
