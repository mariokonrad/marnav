#include <gtest/gtest.h>
#include <marnav/nmea/bec.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{
using namespace marnav;

class Test_nmea_bec : public ::testing::Test
{
};

TEST_F(Test_nmea_bec, contruction)
{
	EXPECT_NO_THROW(nmea::bec bec);
}

TEST_F(Test_nmea_bec, properties)
{
	nmea_sentence_traits<nmea::bec>();
}

TEST_F(Test_nmea_bec, parse)
{
	auto s = nmea::make_sentence(
		"$GPBEC,123456.78,12.34,N,123.45,E,12.34,T,23.45,M,21.43,N,WAYPNT0*07");
	ASSERT_NE(nullptr, s);

	auto bec = nmea::sentence_cast<nmea::bec>(s);
	ASSERT_NE(nullptr, bec);
}

TEST_F(Test_nmea_bec, create_sentence)
{
	const auto s = nmea::create_sentence<nmea::bec>(
		"$GPBEC,123456.78,12.34,N,123.45,E,12.34,T,23.45,M,21.43,N,WAYPNT0*07");
	EXPECT_EQ(nmea::sentence_id::BEC, s.id());
}

TEST_F(Test_nmea_bec, create_sentence_exception)
{
	EXPECT_ANY_THROW(nmea::create_sentence<nmea::bec>(""));
	EXPECT_ANY_THROW(nmea::create_sentence<nmea::bec>("$IIMWV,084.0,R,10.4,N,A*04"));
}

TEST_F(Test_nmea_bec, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::bec>(nmea::talker_id::none, {11, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::bec>(nmea::talker_id::none, {13, "@"}));
}

TEST_F(Test_nmea_bec, empty_to_string)
{
	nmea::bec bec;

	EXPECT_STREQ("$GPBEC,000000,0000.0000,N,00000.0000,E,0,T,0,M,0,N,*0F",
		nmea::to_string(bec).c_str());
}

TEST_F(Test_nmea_bec, set_bearing_true)
{
	nmea::bec bec;
	bec.set_bearing_true(12.5);

	EXPECT_STREQ("$GPBEC,000000,0000.0000,N,00000.0000,E,12.5,T,0,M,0,N,*27",
		nmea::to_string(bec).c_str());
}

TEST_F(Test_nmea_bec, set_bearing_magn)
{
	nmea::bec bec;
	bec.set_bearing_magn(10.2);

	EXPECT_STREQ("$GPBEC,000000,0000.0000,N,00000.0000,E,0,T,10.2,M,0,N,*22",
		nmea::to_string(bec).c_str());
}

TEST_F(Test_nmea_bec, set_waypoint)
{
	nmea::bec bec;
	bec.set_waypoint(nmea::waypoint{"wpt-to"});

	EXPECT_STREQ("$GPBEC,000000,0000.0000,N,00000.0000,E,0,T,0,M,0,N,wpt-to*4A",
		nmea::to_string(bec).c_str());
}

TEST_F(Test_nmea_bec, set_time_utc)
{
	nmea::bec bec;
	bec.set_time_utc(nmea::time{12, 34, 56, 789});

	EXPECT_STREQ("$GPBEC,123456.789,0000.0000,N,00000.0000,E,0,T,0,M,0,N,*10",
		nmea::to_string(bec).c_str());
}

TEST_F(Test_nmea_bec, set_position)
{
	nmea::bec bec;
	bec.set_lat(geo::latitude{12.34});
	bec.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPBEC,000000,1220.4000,N,12327.0000,E,0,T,0,M,0,N,*0F",
		nmea::to_string(bec).c_str());
}
}
