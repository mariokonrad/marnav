#include <gtest/gtest.h>
#include <marnav/nmea/bwr.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_bwr : public ::testing::Test
{
};

TEST_F(Test_nmea_bwr, contruction) { nmea::bwr bwr; }

TEST_F(Test_nmea_bwr, parse)
{
	auto s = nmea::make_sentence(
		"$GPBWR,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*30");
	ASSERT_NE(nullptr, s);

	auto bwr = nmea::sentence_cast<nmea::bwr>(s);
	ASSERT_NE(nullptr, bwr);
}

TEST_F(Test_nmea_bwr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::bwr::parse("@@", {11, "@"}));
	EXPECT_ANY_THROW(nmea::bwr::parse("@@", {13, "@"}));
}

TEST_F(Test_nmea_bwr, empty_to_string)
{
	nmea::bwr bwr;

	EXPECT_STREQ("$GPBWR,,,,,,,,,,,,*50", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_time_utc)
{
	nmea::bwr bwr;
	bwr.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPBWR,123456,,,,,,,,,,,*57", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_lat)
{
	nmea::bwr bwr;
	bwr.set_lat(geo::latitude{12.34});

	EXPECT_STREQ("$GPBWR,,1220.4000,N,,,,,,,,,*35", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_lon)
{
	nmea::bwr bwr;
	bwr.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPBWR,,,,12327.0000,W,,,,,,,*1C", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_bearing_true)
{
	nmea::bwr bwr;
	bwr.set_bearing_true(12.3);

	EXPECT_STREQ("$GPBWR,,,,,,12.3,T,,,,,*1A", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_bearing_mag)
{
	nmea::bwr bwr;
	bwr.set_bearing_mag(12.3);

	EXPECT_STREQ("$GPBWR,,,,,,,,12.3,M,,,*03", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_distance)
{
	nmea::bwr bwr;
	bwr.set_distance(100);

	EXPECT_STREQ("$GPBWR,,,,,,,,,,100,N,*2F", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_waypoint)
{
	nmea::bwr bwr;
	bwr.set_waypoint("POINT1");

	EXPECT_STREQ("$GPBWR,,,,,,,,,,,,POINT1*2D", nmea::to_string(bwr).c_str());
}
}
