#include <gtest/gtest.h>
#include <marnav/nmea/bwr.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_bwr : public ::testing::Test
{
};

TEST_F(Test_nmea_bwr, contruction)
{
	EXPECT_NO_THROW(nmea::bwr bwr);
}

TEST_F(Test_nmea_bwr, properties)
{
	nmea_sentence_traits<nmea::bwr>();
}

TEST_F(Test_nmea_bwr, parse_12)
{
	auto s = nmea::make_sentence(
		"$GPBWR,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*30");
	ASSERT_NE(nullptr, s);

	auto bwr = nmea::sentence_cast<nmea::bwr>(s);
	ASSERT_NE(nullptr, bwr);
}

TEST_F(Test_nmea_bwr, parse_13)
{
	auto s = nmea::make_sentence(
		"$GPBWR,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM,A*5D");
	ASSERT_NE(nullptr, s);

	auto bwr = nmea::sentence_cast<nmea::bwr>(s);
	ASSERT_NE(nullptr, bwr);
}

TEST_F(Test_nmea_bwr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::bwr>(nmea::talker_id::none, {11, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::bwr>(nmea::talker_id::none, {14, "@"}));
}

TEST_F(Test_nmea_bwr, empty_to_string)
{
	nmea::bwr bwr;

	EXPECT_STREQ("$GPBWR,,,,,,,,,,,,,*7C", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_time_utc)
{
	nmea::bwr bwr;
	bwr.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPBWR,123456,,,,,,,,,,,,*7B", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_lat)
{
	nmea::bwr bwr;
	bwr.set_lat(geo::latitude{12.34});

	EXPECT_STREQ("$GPBWR,,1220.4000,N,,,,,,,,,,*19", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_lon)
{
	nmea::bwr bwr;
	bwr.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPBWR,,,,12327.0000,E,,,,,,,,*22", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_bearing_true)
{
	nmea::bwr bwr;
	bwr.set_bearing_true(12.3);

	EXPECT_STREQ("$GPBWR,,,,,,12.3,T,,,,,,*36", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_bearing_mag)
{
	nmea::bwr bwr;
	bwr.set_bearing_mag(12.3);

	EXPECT_STREQ("$GPBWR,,,,,,,,12.3,M,,,,*2F", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_distance)
{
	nmea::bwr bwr;
	bwr.set_distance(100);

	EXPECT_STREQ("$GPBWR,,,,,,,,,,100,N,,*03", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_waypoint)
{
	nmea::bwr bwr;
	bwr.set_waypoint(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPBWR,,,,,,,,,,,,POINT1,*01", nmea::to_string(bwr).c_str());
}

TEST_F(Test_nmea_bwr, set_mode_ind)
{
	nmea::bwr bwr;
	bwr.set_mode_ind(nmea::mode_indicator::autonomous);

	EXPECT_STREQ("$GPBWR,,,,,,,,,,,,,A*3D", nmea::to_string(bwr).c_str());
}
}
