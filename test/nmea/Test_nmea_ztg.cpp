#include <gtest/gtest.h>
#include <marnav/nmea/ztg.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_ztg : public ::testing::Test
{
};

TEST_F(Test_nmea_ztg, contruction) { nmea::ztg ztg; }

TEST_F(Test_nmea_ztg, parse)
{
	auto s = nmea::make_sentence("$GPZTG,123456.1,000010,POINT1*16");
	ASSERT_NE(nullptr, s);

	auto ztg = nmea::sentence_cast<nmea::ztg>(s);
	ASSERT_NE(nullptr, ztg);
}

TEST_F(Test_nmea_ztg, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::ztg::parse("@@", {2, "@"}));
	EXPECT_ANY_THROW(nmea::ztg::parse("@@", {4, "@"}));
}

TEST_F(Test_nmea_ztg, empty_to_string)
{
	nmea::ztg ztg;

	EXPECT_STREQ("$GPZTG,,,*72", nmea::to_string(ztg).c_str());
}

TEST_F(Test_nmea_ztg, set_time_utc)
{
	nmea::ztg ztg;
	ztg.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZTG,123456,,*75", nmea::to_string(ztg).c_str());
}

TEST_F(Test_nmea_ztg, set_time_remaining)
{
	nmea::ztg ztg;
	ztg.set_time_remaining(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZTG,,123456,*75", nmea::to_string(ztg).c_str());
}

TEST_F(Test_nmea_ztg, set_waypoint_id)
{
	nmea::ztg ztg;
	ztg.set_waypoint_id("POINT1");

	EXPECT_STREQ("$GPZTG,,,POINT1*0F", nmea::to_string(ztg).c_str());
}

}
