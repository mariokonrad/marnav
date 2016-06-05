#include <gtest/gtest.h>
#include <marnav/nmea/bww.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_bww : public ::testing::Test
{
};

TEST_F(Test_nmea_bww, contruction) { EXPECT_NO_THROW(nmea::bww bww); }

TEST_F(Test_nmea_bww, properties) { nmea_sentence_traits<nmea::bww>(); }

TEST_F(Test_nmea_bww, parse)
{
	auto s = nmea::make_sentence("$GPBWW,213.8,T,218.0,M,POINT1,POINT2*4C");
	ASSERT_NE(nullptr, s);

	auto bww = nmea::sentence_cast<nmea::bww>(s);
	ASSERT_NE(nullptr, bww);
}

TEST_F(Test_nmea_bww, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::bww>("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::bww>("@@", {7, "@"}));
}

TEST_F(Test_nmea_bww, empty_to_string)
{
	nmea::bww bww;

	EXPECT_STREQ("$GPBWW,,,,,,*55", nmea::to_string(bww).c_str());
}

TEST_F(Test_nmea_bww, set_bearing_true)
{
	nmea::bww bww;
	bww.set_bearing_true(12.3);

	EXPECT_STREQ("$GPBWW,12.3,T,,,,*1F", nmea::to_string(bww).c_str());
}

TEST_F(Test_nmea_bww, set_bearing_mag)
{
	nmea::bww bww;
	bww.set_bearing_mag(12.3);

	EXPECT_STREQ("$GPBWW,,,12.3,M,,*06", nmea::to_string(bww).c_str());
}

TEST_F(Test_nmea_bww, set_waypoint_to)
{
	nmea::bww bww;
	bww.set_waypoint_to(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPBWW,,,,,POINT1,*28", nmea::to_string(bww).c_str());
}

TEST_F(Test_nmea_bww, set_waypoint_from)
{
	nmea::bww bww;
	bww.set_waypoint_from(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPBWW,,,,,,POINT1*28", nmea::to_string(bww).c_str());
}
}
