#include <gtest/gtest.h>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_bod : public ::testing::Test
{
};

TEST_F(Test_nmea_bod, contruction) { EXPECT_NO_THROW(nmea::bod bod); }

TEST_F(Test_nmea_bod, properties) { nmea_sentence_traits<nmea::bod>(); }

TEST_F(Test_nmea_bod, parse)
{
	auto s = nmea::make_sentence("$GPBOD,,T,,M,,*47");
	ASSERT_NE(nullptr, s);

	auto bod = nmea::sentence_cast<nmea::bod>(s);
	ASSERT_NE(nullptr, bod);
}

TEST_F(Test_nmea_bod, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::bod>("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::bod>("@@", {7, "@"}));
}

TEST_F(Test_nmea_bod, empty_to_string)
{
	nmea::bod bod;

	EXPECT_STREQ("$GPBOD,,,,,,*5E", nmea::to_string(bod).c_str());
}

TEST_F(Test_nmea_bod, set_bearing_true)
{
	nmea::bod bod;
	bod.set_bearing_true(12.5);

	EXPECT_STREQ("$GPBOD,12.5,T,,,,*12", nmea::to_string(bod).c_str());
}

TEST_F(Test_nmea_bod, set_bearing_magn)
{
	nmea::bod bod;
	bod.set_bearing_magn(10.2);

	EXPECT_STREQ("$GPBOD,,,10.2,M,,*0E", nmea::to_string(bod).c_str());
}

TEST_F(Test_nmea_bod, set_waypoint_to)
{
	nmea::bod bod;
	bod.set_waypoint_to("wpt-to");

	EXPECT_STREQ("$GPBOD,,,,,wpt-to,*1B", nmea::to_string(bod).c_str());
}

TEST_F(Test_nmea_bod, set_waypoint_to_to_large)
{
	nmea::bod bod;

	EXPECT_ANY_THROW(bod.set_waypoint_to("1234567890"));
}

TEST_F(Test_nmea_bod, set_waypoint_from)
{
	nmea::bod bod;
	bod.set_waypoint_from("wpt-from");

	EXPECT_STREQ("$GPBOD,,,,,,wpt-from*16", nmea::to_string(bod).c_str());
}

TEST_F(Test_nmea_bod, set_waypoint_from_to_large)
{
	nmea::bod bod;

	EXPECT_ANY_THROW(bod.set_waypoint_from("1234567890"));
}
}
