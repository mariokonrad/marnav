#include <marnav/nmea/rmb.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_rmb : public ::testing::Test
{
};

TEST_F(test_nmea_rmb, contruction)
{
	EXPECT_NO_THROW(nmea::rmb rmb);
}

TEST_F(test_nmea_rmb, properties)
{
	nmea_sentence_traits<nmea::rmb>();
}

TEST_F(test_nmea_rmb, parse)
{
	auto s = nmea::make_sentence("$GPRMB,V,,,,,,,,,,,,V,N*04");
	ASSERT_NE(nullptr, s);

	auto rmb = nmea::sentence_cast<nmea::rmb>(s);
	ASSERT_NE(nullptr, rmb);
}

TEST_F(test_nmea_rmb, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rmb>(nmea::talker::none, {12, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rmb>(nmea::talker::none, {15, "@"}));
}

TEST_F(test_nmea_rmb, empty_to_string)
{
	nmea::rmb rmb;

	EXPECT_STREQ("$GPRMB,,,,,,,,,,,,,,*4A", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_waypoint_to)
{
	nmea::rmb rmb;
	rmb.set_waypoint_to(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPRMB,,,,,POINT1,,,,,,,,,*37", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_waypoint_from)
{
	nmea::rmb rmb;
	rmb.set_waypoint_from(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPRMB,,,,POINT1,,,,,,,,,,*37", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_lat)
{
	nmea::rmb rmb;
	rmb.set_lat(marnav::geo::latitude{2.34});

	EXPECT_STREQ("$GPRMB,,,,,,0220.4000,N,,,,,,,*2E", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_lon_west)
{
	nmea::rmb rmb;
	rmb.set_lon(marnav::geo::longitude{-2.34});

	EXPECT_STREQ("$GPRMB,,,,,,,,00220.4000,W,,,,,*07", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_lon_east)
{
	nmea::rmb rmb;
	rmb.set_lon(marnav::geo::longitude{2.34});

	EXPECT_STREQ("$GPRMB,,,,,,,,00220.4000,E,,,,,*15", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_dst_velocity)
{
	nmea::rmb rmb;
	rmb.set_dst_velocity(units::knots{2.0});

	EXPECT_STREQ("$GPRMB,,,,,,,,,,,,2,,*78", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_dst_velocity_different_unit)
{
	nmea::rmb rmb;
	rmb.set_dst_velocity(units::meters_per_second{1.02889});

	EXPECT_STREQ("$GPRMB,,,,,,,,,,,,2,,*78", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_range)
{
	nmea::rmb rmb;
	rmb.set_range(units::nautical_miles{2.0});

	EXPECT_STREQ("$GPRMB,,,,,,,,,,2,,,,*78", nmea::to_string(rmb).c_str());
}

TEST_F(test_nmea_rmb, set_range_different_unit)
{
	nmea::rmb rmb;
	rmb.set_range(units::kilometers{3.704});

	EXPECT_STREQ("$GPRMB,,,,,,,,,,2,,,,*78", nmea::to_string(rmb).c_str());
}
}
