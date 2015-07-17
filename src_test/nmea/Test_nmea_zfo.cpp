#include <gtest/gtest.h>
#include <marnav/nmea/zfo.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_zfo : public ::testing::Test
{
};

TEST_F(Test_nmea_zfo, contruction) { nmea::zfo zfo; }

TEST_F(Test_nmea_zfo, parse)
{
	auto s = nmea::make_sentence("$GPZFO,123456.1,000010,POINT1*0C");
	ASSERT_NE(nullptr, s);

	auto zfo = nmea::sentence_cast<nmea::zfo>(s);
	ASSERT_NE(nullptr, zfo);
}

TEST_F(Test_nmea_zfo, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::zfo::parse("@@", {2, "@"}));
	EXPECT_ANY_THROW(nmea::zfo::parse("@@", {4, "@"}));
}

TEST_F(Test_nmea_zfo, empty_to_string)
{
	nmea::zfo zfo;

	EXPECT_STREQ("$GPZFO,,,*68", nmea::to_string(zfo).c_str());
}

TEST_F(Test_nmea_zfo, set_time_utc)
{
	nmea::zfo zfo;
	zfo.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZFO,123456,,*6F", nmea::to_string(zfo).c_str());
}

TEST_F(Test_nmea_zfo, set_time_elapsed)
{
	nmea::zfo zfo;
	zfo.set_time_elapsed(nmea::duration{12, 34, 56});

	EXPECT_STREQ("$GPZFO,,123456,*6F", nmea::to_string(zfo).c_str());
}

TEST_F(Test_nmea_zfo, set_waypoint_id)
{
	nmea::zfo zfo;
	zfo.set_waypoint_id("POINT1");

	EXPECT_STREQ("$GPZFO,,,POINT1*15", nmea::to_string(zfo).c_str());
}

}
