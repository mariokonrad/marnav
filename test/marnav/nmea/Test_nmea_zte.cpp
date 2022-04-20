#include <marnav/nmea/zte.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_zte : public ::testing::Test
{
};

TEST_F(Test_nmea_zte, contruction)
{
	EXPECT_NO_THROW(nmea::zte zte);
}

TEST_F(Test_nmea_zte, properties)
{
	nmea_sentence_traits<nmea::zte>();
}

TEST_F(Test_nmea_zte, parse)
{
	auto s = nmea::make_sentence("$GPZTE,123456.1,000010,POINT1*14");
	ASSERT_NE(nullptr, s);

	auto zte = nmea::sentence_cast<nmea::zte>(s);
	ASSERT_NE(nullptr, zte);

	EXPECT_EQ(nmea::time(12, 34, 56, 100), zte->get_time_utc());
	EXPECT_EQ(nmea::duration(0, 0, 10), zte->get_time_remaining());
	EXPECT_STREQ("POINT1", zte->get_waypoint_id().c_str());
}

TEST_F(Test_nmea_zte, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zte>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zte>(nmea::talker::none, {4, "@"}));
}

TEST_F(Test_nmea_zte, empty_to_string)
{
	nmea::zte zte;

	EXPECT_STREQ("$GPZTE,000000,000000,*70", nmea::to_string(zte).c_str());
}

TEST_F(Test_nmea_zte, set_time_utc)
{
	nmea::zte zte;
	zte.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZTE,123456,000000,*77", nmea::to_string(zte).c_str());
}

TEST_F(Test_nmea_zte, set_time_remaining)
{
	nmea::zte zte;
	zte.set_time_remaining(nmea::duration{12, 34, 56});

	EXPECT_STREQ("$GPZTE,000000,123456,*77", nmea::to_string(zte).c_str());
}

TEST_F(Test_nmea_zte, set_waypoint_id)
{
	nmea::zte zte;
	zte.set_waypoint_id(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPZTE,000000,000000,POINT1*0D", nmea::to_string(zte).c_str());
}
}
