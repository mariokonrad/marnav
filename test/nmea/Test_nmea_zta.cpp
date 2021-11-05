#include <marnav/nmea/zta.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_zta : public ::testing::Test
{
};

TEST_F(Test_nmea_zta, contruction)
{
	EXPECT_NO_THROW(nmea::zta zta);
}

TEST_F(Test_nmea_zta, properties)
{
	nmea_sentence_traits<nmea::zta>();
}

TEST_F(Test_nmea_zta, parse)
{
	auto s = nmea::make_sentence("$GPZTA,123456.1,000010,POINT1*10");
	ASSERT_NE(nullptr, s);

	auto zta = nmea::sentence_cast<nmea::zta>(s);
	ASSERT_NE(nullptr, zta);

	EXPECT_EQ(nmea::time(12, 34, 56, 100), zta->get_time_utc());
	EXPECT_EQ(nmea::time(0, 0, 10), zta->get_time_arrival());
	EXPECT_STREQ("POINT1", zta->get_waypoint_id().c_str());
}

TEST_F(Test_nmea_zta, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zta>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zta>(nmea::talker::none, {4, "@"}));
}

TEST_F(Test_nmea_zta, empty_to_string)
{
	nmea::zta zta;

	EXPECT_STREQ("$GPZTA,000000,000000,*74", nmea::to_string(zta).c_str());
}

TEST_F(Test_nmea_zta, set_time_utc)
{
	nmea::zta zta;
	zta.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZTA,123456,000000,*73", nmea::to_string(zta).c_str());
}

TEST_F(Test_nmea_zta, set_time_remaining)
{
	nmea::zta zta;
	zta.set_time_arrival(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZTA,000000,123456,*73", nmea::to_string(zta).c_str());
}

TEST_F(Test_nmea_zta, set_waypoint_id)
{
	nmea::zta zta;
	zta.set_waypoint_id(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPZTA,000000,000000,POINT1*09", nmea::to_string(zta).c_str());
}
}

