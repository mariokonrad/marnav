#include <gtest/gtest.h>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_rte : public ::testing::Test
{
};

TEST_F(Test_nmea_rte, contruction) { nmea::rte rte; }

TEST_F(Test_nmea_rte, parse)
{
	auto s = nmea::make_sentence("$GPRTE,1,1,c,*37");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);
}

TEST_F(Test_nmea_rte, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::rte::parse("@@", {2, "@"}));
	EXPECT_ANY_THROW(nmea::rte::parse("@@", {14, "@"}));
}

TEST_F(Test_nmea_rte, empty_to_string)
{
	nmea::rte rte;

	EXPECT_STREQ("$GPRTE,,,*78", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_n_messages)
{
	nmea::rte rte;
	rte.set_n_messages(99);

	EXPECT_STREQ("$GPRTE,99,,*78", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_message_number)
{
	nmea::rte rte;
	rte.set_message_number(66);

	EXPECT_STREQ("$GPRTE,,66,*78", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_message_mode)
{
	nmea::rte rte;
	rte.set_message_mode(marnav::nmea::message_mode::complete_route);

	EXPECT_STREQ("$GPRTE,,,c*1B", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_waypoint_id)
{
	nmea::rte rte;
	rte.set_n_messages(1);
	rte.set_waypoint_id(0, "POINT1");

	EXPECT_STREQ("$GPRTE,1,,,POINT1*18", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_waypoint_id_without_n_messages)
{
	nmea::rte rte;
	rte.set_waypoint_id(0, "POINT1");

	EXPECT_STREQ("$GPRTE,,,*78", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_waypoint_id_index_to_low)
{
	nmea::rte rte;

	EXPECT_ANY_THROW(rte.set_waypoint_id(-1, "POINT1"));
}

TEST_F(Test_nmea_rte, set_waypoint_id_index_to_high)
{
	nmea::rte rte;

	EXPECT_ANY_THROW(rte.set_waypoint_id(10, "POINT1"));
}

TEST_F(Test_nmea_rte, set_waypoint_id_to_large)
{
	nmea::rte rte;

	EXPECT_ANY_THROW(rte.set_waypoint_id(0, "POINT1abcdef"));
}

TEST_F(Test_nmea_rte, get_waypoint_id)
{
	nmea::rte rte;
	rte.set_n_messages(1);
	rte.set_waypoint_id(0, "POINT1");

	auto wp = rte.get_waypoint_id(0);

	EXPECT_TRUE(wp.available());
	EXPECT_STREQ("POINT1", wp.value().c_str());
}

TEST_F(Test_nmea_rte, get_waypoint_id_invaild_waypoint)
{
	nmea::rte rte;

	auto wp = rte.get_waypoint_id(0);

	EXPECT_FALSE(wp.available());
}

TEST_F(Test_nmea_rte, get_waypoint_id_invaild_index)
{
	nmea::rte rte;

	EXPECT_ANY_THROW(rte.get_waypoint_id(-1));
}
}
