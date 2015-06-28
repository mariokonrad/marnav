#include <gtest/gtest.h>
#include <marnav/nmea/r00.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_r00 : public ::testing::Test
{
};

TEST_F(Test_nmea_r00, contruction) { nmea::r00 r00; }

TEST_F(Test_nmea_r00, size) { EXPECT_EQ(248u, sizeof(nmea::r00)); }

TEST_F(Test_nmea_r00, parse)
{
	auto s = nmea::make_sentence("$GPR00,EGLL,EGLM,EGTB,EGUB,EGTK,MBOT,EGTB,,,,,,,*58");
	ASSERT_NE(nullptr, s);

	auto r00 = nmea::sentence_cast<nmea::r00>(s);
	ASSERT_NE(nullptr, r00);
}

TEST_F(Test_nmea_r00, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::r00::parse("@@", {13, "@"}));
	EXPECT_ANY_THROW(nmea::r00::parse("@@", {15, "@"}));
}

TEST_F(Test_nmea_r00, empty_to_string)
{
	nmea::r00 r00;

	EXPECT_STREQ("$GPR00,,,,,,,,,,,,,,*45", nmea::to_string(r00).c_str());
}

TEST_F(Test_nmea_r00, set_id_invalid_index)
{
	nmea::r00 r00;

	EXPECT_ANY_THROW(r00.set_waypoint_id(-1, "ABC"));
	EXPECT_ANY_THROW(r00.set_waypoint_id(15, "ABC"));
}

TEST_F(Test_nmea_r00, set_id)
{
	nmea::r00 r00;

	r00.set_waypoint_id(0, "ABC");
	EXPECT_STREQ("$GPR00,ABC,,,,,,,,,,,,,*05", nmea::to_string(r00).c_str());
}

TEST_F(Test_nmea_r00, get_id)
{
	auto s = nmea::make_sentence("$GPR00,EGLL,EGLM,EGTB,EGUB,EGTK,MBOT,EGTB,,,,,,,*58");
	ASSERT_NE(nullptr, s);

	auto r00 = nmea::sentence_cast<nmea::r00>(s);
	ASSERT_NE(nullptr, r00);

	{
		auto wp = *r00->get_waypoint_id(0);
		EXPECT_STREQ("EGLL", wp.c_str());
	}
	{
		auto wp = *r00->get_waypoint_id(1);
		EXPECT_STREQ("EGLM", wp.c_str());
	}
	{
		auto wp = *r00->get_waypoint_id(2);
		EXPECT_STREQ("EGTB", wp.c_str());
	}
}

TEST_F(Test_nmea_r00, found_on_internet)
{
	{
		auto s = nmea::make_sentence("$GPR00,EGLL,EGLM,EGTB,EGUB,EGTK,MBOT,EGTB,,,,,,,*58");
		EXPECT_NE(nullptr, s);
	}
	{
		auto s = nmea::make_sentence("$GPR00,MINST,CHATN,CHAT1,CHATW,CHATM,CHATE,003,004,005,006,007,,,*05");
		EXPECT_NE(nullptr, s);
	}
}

}
