#include <gtest/gtest.h>
#include <marnav/nmea/wcv.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_wcv : public ::testing::Test
{
};

TEST_F(Test_nmea_wcv, contruction)
{
	EXPECT_NO_THROW(nmea::wcv wcv);
}

TEST_F(Test_nmea_wcv, properties)
{
	nmea_sentence_traits<nmea::wcv>();
}

TEST_F(Test_nmea_wcv, parse)
{
	auto s = nmea::make_sentence("$GPWCV,12.3,N,POINT1*54");
	ASSERT_NE(nullptr, s);

	auto wcv = nmea::sentence_cast<nmea::wcv>(s);
	ASSERT_NE(nullptr, wcv);
}

TEST_F(Test_nmea_wcv, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::wcv>(nmea::talker_id::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::wcv>(nmea::talker_id::none, {4, "@"}));
}

TEST_F(Test_nmea_wcv, empty_to_string)
{
	nmea::wcv wcv;

	EXPECT_STREQ("$GPWCV,,,*79", nmea::to_string(wcv).c_str());
}

TEST_F(Test_nmea_wcv, set_speed)
{
	nmea::wcv wcv;
	wcv.set_speed(12.3);

	EXPECT_STREQ("$GPWCV,12.3,N,*29", nmea::to_string(wcv).c_str());
}

TEST_F(Test_nmea_wcv, set_waypoint)
{
	nmea::wcv wcv;
	wcv.set_waypoint(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPWCV,,,POINT1*04", nmea::to_string(wcv).c_str());
}
}
