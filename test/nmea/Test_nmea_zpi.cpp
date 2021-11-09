#include <marnav/nmea/zpi.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_nmea_zpi : public ::testing::Test
{
};

TEST_F(Test_nmea_zpi, contruction)
{
	EXPECT_NO_THROW(nmea::zpi zpi);
}

TEST_F(Test_nmea_zpi, properties)
{
	nmea_sentence_traits<nmea::zpi>();
}

TEST_F(Test_nmea_zpi, parse)
{
	auto s = nmea::make_sentence("$GPZPI,123456.1,124456.1,POINT1*02");
	ASSERT_NE(nullptr, s);

	auto zpi = nmea::sentence_cast<nmea::zpi>(s);
	ASSERT_NE(nullptr, zpi);
}

TEST_F(Test_nmea_zpi, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zpi>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zpi>(nmea::talker::none, {4, "@"}));
}

TEST_F(Test_nmea_zpi, empty_to_string)
{
	nmea::zpi zpi;

	EXPECT_STREQ("$GPZPI,000000,000000,*78", nmea::to_string(zpi).c_str());
}

TEST_F(Test_nmea_zpi, set_time_utc)
{
	nmea::zpi zpi;
	zpi.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZPI,123456,000000,*7F", nmea::to_string(zpi).c_str());
}

TEST_F(Test_nmea_zpi, set_time_remaining)
{
	nmea::zpi zpi;
	zpi.set_time_arrival(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZPI,000000,123456,*7F", nmea::to_string(zpi).c_str());
}

TEST_F(Test_nmea_zpi, set_waypoint_id)
{
	nmea::zpi zpi;
	zpi.set_waypoint_id(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPZPI,000000,000000,POINT1*05", nmea::to_string(zpi).c_str());
}
}

