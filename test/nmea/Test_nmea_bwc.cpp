#include <gtest/gtest.h>
#include <marnav/nmea/bwc.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_bwc : public ::testing::Test
{
};

TEST_F(Test_nmea_bwc, contruction) { EXPECT_NO_THROW(nmea::bwc bwc); }

TEST_F(Test_nmea_bwc, properties) { nmea_sentence_traits<nmea::bwc>(); }

TEST_F(Test_nmea_bwc, parse_before_v23)
{
	auto s = nmea::make_sentence(
		"$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*21");
	ASSERT_NE(nullptr, s);

	auto bwc = nmea::sentence_cast<nmea::bwc>(s);
	ASSERT_NE(nullptr, bwc);
}

TEST_F(Test_nmea_bwc, parse)
{
	auto s = nmea::make_sentence(
		"$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM,A*4C");
	ASSERT_NE(nullptr, s);

	auto bwc = nmea::sentence_cast<nmea::bwc>(s);
	ASSERT_NE(nullptr, bwc);
}

TEST_F(Test_nmea_bwc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::bwc>("@@", {11, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::bwc>("@@", {14, "@"}));
}

TEST_F(Test_nmea_bwc, empty_to_string)
{
	nmea::bwc bwc;

	EXPECT_STREQ("$GPBWC,,,,,,,,,,,,,*6D", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_time_utc)
{
	nmea::bwc bwc;
	bwc.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPBWC,123456,,,,,,,,,,,,*6A", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_lat)
{
	nmea::bwc bwc;
	bwc.set_lat(geo::latitude{12.34});

	EXPECT_STREQ("$GPBWC,,1220.4000,N,,,,,,,,,,*08", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_lon)
{
	nmea::bwc bwc;
	bwc.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPBWC,,,,12327.0000,E,,,,,,,,*33", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_bearing_true)
{
	nmea::bwc bwc;
	bwc.set_bearing_true(12.3);

	EXPECT_STREQ("$GPBWC,,,,,,12.3,T,,,,,,*27", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_bearing_mag)
{
	nmea::bwc bwc;
	bwc.set_bearing_mag(12.3);

	EXPECT_STREQ("$GPBWC,,,,,,,,12.3,M,,,,*3E", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_distance)
{
	nmea::bwc bwc;
	bwc.set_distance(100);

	EXPECT_STREQ("$GPBWC,,,,,,,,,,100,N,,*12", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_waypoint)
{
	nmea::bwc bwc;
	bwc.set_waypoint(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPBWC,,,,,,,,,,,,POINT1,*10", nmea::to_string(bwc).c_str());
}

TEST_F(Test_nmea_bwc, set_faa_mode_indicator)
{
	nmea::bwc bwc;
	bwc.set_faa_mode_indicator(nmea::positioning_system_mode_indicator::differential);

	EXPECT_STREQ("$GPBWC,,,,,,,,,,,,,D*29", nmea::to_string(bwc).c_str());
}
}
