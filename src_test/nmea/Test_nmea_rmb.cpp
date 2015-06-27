#include <gtest/gtest.h>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_rmb : public ::testing::Test
{
};

TEST_F(Test_nmea_rmb, contruction) { nmea::rmb rmb; }

TEST_F(Test_nmea_rmb, size) { EXPECT_EQ(184u, sizeof(nmea::rmb)); }

TEST_F(Test_nmea_rmb, parse)
{
	auto s = nmea::make_sentence("$GPRMB,V,,,,,,,,,,,,V,N*04");
	ASSERT_NE(nullptr, s);

	auto rmb = nmea::sentence_cast<nmea::rmb>(s);
	ASSERT_NE(nullptr, rmb);
}

TEST_F(Test_nmea_rmb, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::rmb::parse("@@", {12, "@"}));
	EXPECT_ANY_THROW(nmea::rmb::parse("@@", {14, "@"}));
}

TEST_F(Test_nmea_rmb, empty_to_string)
{
	nmea::rmb rmb;

	EXPECT_STREQ("$GPRMB,,,,,,,,,,,,,,*4A", nmea::to_string(rmb).c_str());
}

TEST_F(Test_nmea_rmb, set_waypoint_from)
{
	nmea::rmb rmb;
	rmb.set_waypoint_from("POINT1");

	EXPECT_STREQ("$GPRMB,,,,,POINT1,,,,,,,,,*37", nmea::to_string(rmb).c_str());
}

TEST_F(Test_nmea_rmb, set_waypoint_from_to_large)
{
	nmea::rmb rmb;

	EXPECT_ANY_THROW(rmb.set_waypoint_from("POINT1abcdefghijklm"));
}

TEST_F(Test_nmea_rmb, set_waypoint_to)
{
	nmea::rmb rmb;
	rmb.set_waypoint_to("POINT1");

	EXPECT_STREQ("$GPRMB,,,,POINT1,,,,,,,,,,*37", nmea::to_string(rmb).c_str());
}

TEST_F(Test_nmea_rmb, set_waypoint_to_to_large)
{
	nmea::rmb rmb;

	EXPECT_ANY_THROW(rmb.set_waypoint_to("POINT1abcdefghijklm"));
}

TEST_F(Test_nmea_rmb, set_lat)
{
	nmea::rmb rmb;
	rmb.set_lat(marnav::geo::latitude{2.34});

	EXPECT_STREQ("$GPRMB,,,,,,0220.4000,N,,,,,,,*2E", nmea::to_string(rmb).c_str());
}

TEST_F(Test_nmea_rmb, set_lon)
{
	nmea::rmb rmb;
	rmb.set_lon(marnav::geo::longitude{2.34});

	EXPECT_STREQ("$GPRMB,,,,,,,,00220.4000,W,,,,,*07", nmea::to_string(rmb).c_str());
}

// @todo: implementation of RMB unit tests
}
