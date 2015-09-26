#include <gtest/gtest.h>
#include <marnav/nmea/wpl.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_wpl : public ::testing::Test
{
};

TEST_F(Test_nmea_wpl, contruction) { EXPECT_NO_THROW(nmea::wpl wpl); }

TEST_F(Test_nmea_wpl, parse)
{
	auto s = nmea::make_sentence("$GPWPL,12.3,N,123.4,E,POINT1*32");
	ASSERT_NE(nullptr, s);

	auto wpl = nmea::sentence_cast<nmea::wpl>(s);
	ASSERT_NE(nullptr, wpl);
}

TEST_F(Test_nmea_wpl, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::wpl::parse("@@", {4, "@"}));
	EXPECT_ANY_THROW(nmea::wpl::parse("@@", {6, "@"}));
}

TEST_F(Test_nmea_wpl, empty_to_string)
{
	nmea::wpl wpl;

	EXPECT_STREQ("$GPWPL,,,,,*70", nmea::to_string(wpl).c_str());
}

TEST_F(Test_nmea_wpl, set_lat)
{
	nmea::wpl wpl;
	wpl.set_lat(geo::latitude{12.3});

	EXPECT_STREQ("$GPWPL,1218.0000,N,,,*1A", nmea::to_string(wpl).c_str());
}

TEST_F(Test_nmea_wpl, set_lon_west)
{
	nmea::wpl wpl;
	wpl.set_lon(geo::longitude{-123.4});

	EXPECT_STREQ("$GPWPL,,,12324.0000,W,*3F", nmea::to_string(wpl).c_str());
}

TEST_F(Test_nmea_wpl, set_lon_east)
{
	nmea::wpl wpl;
	wpl.set_lon(geo::longitude{123.4});

	EXPECT_STREQ("$GPWPL,,,12324.0000,E,*2D", nmea::to_string(wpl).c_str());
}

TEST_F(Test_nmea_wpl, set_waypoint)
{
	nmea::wpl wpl;
	wpl.set_waypoint("POINT1");

	EXPECT_STREQ("$GPWPL,,,,,POINT1*0D", nmea::to_string(wpl).c_str());
}
}
