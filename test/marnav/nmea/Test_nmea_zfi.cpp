#include <marnav/nmea/zfi.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_zfi : public ::testing::Test
{
};

TEST_F(test_nmea_zfi, contruction)
{
	EXPECT_NO_THROW(nmea::zfi zfi);
}

TEST_F(test_nmea_zfi, properties)
{
	nmea_sentence_traits<nmea::zfi>();
}

TEST_F(test_nmea_zfi, parse)
{
	auto s = nmea::make_sentence("$GPZFI,123456.1,012345.12,POINT1*27");
	ASSERT_NE(nullptr, s);

	auto zfi = nmea::sentence_cast<nmea::zfi>(s);
	ASSERT_NE(nullptr, zfi);

	EXPECT_STREQ("POINT1", zfi->get_waypoint_id().c_str());
}

TEST_F(test_nmea_zfi, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zfi>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zfi>(nmea::talker::none, {4, "@"}));
}

TEST_F(test_nmea_zfi, empty_to_string)
{
	nmea::zfi zfi;

	EXPECT_STREQ("$GPZFI,000000,000000,*6E", nmea::to_string(zfi).c_str());
}

TEST_F(test_nmea_zfi, set_time_utc)
{
	nmea::zfi zfi;
	zfi.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZFI,123456,000000,*69", nmea::to_string(zfi).c_str());
}

TEST_F(test_nmea_zfi, set_time_elapsed)
{
	nmea::zfi zfi;
	zfi.set_time_elapsed(nmea::duration{12, 34, 56});

	EXPECT_STREQ("$GPZFI,000000,123456,*69", nmea::to_string(zfi).c_str());
}

TEST_F(test_nmea_zfi, set_waypoint_id)
{
	nmea::zfi zfi;
	zfi.set_waypoint_id(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPZFI,000000,000000,POINT1*13", nmea::to_string(zfi).c_str());
}
}
