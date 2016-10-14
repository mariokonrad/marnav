#include <gtest/gtest.h>
#include <marnav/nmea/xte.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_xte : public ::testing::Test
{
};

TEST_F(Test_nmea_xte, contruction)
{
	EXPECT_NO_THROW(nmea::xte xte);
}

TEST_F(Test_nmea_xte, properties)
{
	nmea_sentence_traits<nmea::xte>();
}

TEST_F(Test_nmea_xte, parse)
{
	auto s = nmea::make_sentence("$GPXTE,,,,,,*5E");
	ASSERT_NE(nullptr, s);

	auto xte = nmea::sentence_cast<nmea::xte>(s);
	ASSERT_NE(nullptr, xte);
}

TEST_F(Test_nmea_xte, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::xte>(nmea::talker_id::none, {4, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::xte>(nmea::talker_id::none, {7, "@"}));
}

TEST_F(Test_nmea_xte, empty_to_string)
{
	nmea::xte xte;

	EXPECT_STREQ("$GPXTE,,,,,,*5E", nmea::to_string(xte).c_str());
}

TEST_F(Test_nmea_xte, set_cross_track_error_magnitude)
{
	nmea::xte xte;
	xte.set_cross_track_error_magnitude(1.2);

	EXPECT_STREQ("$GPXTE,,,1.2,,N,*3D", nmea::to_string(xte).c_str());
}
}
