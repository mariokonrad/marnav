#include <gtest/gtest.h>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rte : public ::testing::Test
{
};

TEST_F(Test_nmea_rte, contruction)
{
	EXPECT_NO_THROW(nmea::rte rte);
}

TEST_F(Test_nmea_rte, properties)
{
	nmea_sentence_traits<nmea::rte>();
}

TEST_F(Test_nmea_rte, parse_0)
{
	auto s = nmea::make_sentence("$GPRTE,1,1,c,*37");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(1u, rte->get_n_messages());
	EXPECT_EQ(1u, rte->get_message_number());
	EXPECT_EQ(nmea::route::complete, rte->get_message_mode());

	for (int i = 0; i < nmea::rte::max_waypoints; ++i)
		EXPECT_FALSE(rte->get_waypoint_id(i));
}

TEST_F(Test_nmea_rte, parse_1)
{
	auto s = nmea::make_sentence("$GPRTE,1,1,c,0*07");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(1u, rte->get_n_messages());
	EXPECT_EQ(1u, rte->get_message_number());
	EXPECT_EQ(nmea::route::complete, rte->get_message_mode());

	const auto wp0 = rte->get_waypoint_id(0);
	EXPECT_TRUE(!!wp0);
	EXPECT_STREQ("0", wp0->c_str());

	for (int i = 1; i < nmea::rte::max_waypoints; ++i)
		EXPECT_FALSE(rte->get_waypoint_id(i));
}

TEST_F(Test_nmea_rte, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::rte>(nmea::talker_id::none, {2, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::rte>(nmea::talker_id::none, {14, "@"}));
}

TEST_F(Test_nmea_rte, empty_to_string)
{
	nmea::rte rte;

	EXPECT_STREQ("$GPRTE,1,1,c,*37", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_n_messages)
{
	nmea::rte rte;
	rte.set_n_messages(99);

	EXPECT_STREQ("$GPRTE,99,1,c,,,,,,,,,,*2A", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_message_number)
{
	nmea::rte rte;
	rte.set_message_number(66);

	EXPECT_STREQ("$GPRTE,1,66,c,*06", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_message_mode_complete)
{
	nmea::rte rte;
	rte.set_message_mode(marnav::nmea::route::complete);

	EXPECT_STREQ("$GPRTE,1,1,c,*37", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_message_mode_working)
{
	nmea::rte rte;
	rte.set_message_mode(marnav::nmea::route::working);

	EXPECT_STREQ("$GPRTE,1,1,w,*23", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_waypoint_id)
{
	nmea::rte rte;
	rte.set_n_messages(1);
	rte.set_waypoint_id(0, nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPRTE,1,1,c,POINT1*4A", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_waypoint_id_wrong_n_messages)
{
	nmea::rte rte;
	rte.set_waypoint_id(0, nmea::waypoint{"POINT1"});
	rte.set_waypoint_id(1, nmea::waypoint{"POINT2"});

	EXPECT_STREQ("$GPRTE,1,1,c,POINT1*4A", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_waypoint_id_index_to_low)
{
	nmea::rte rte;

	EXPECT_ANY_THROW(rte.set_waypoint_id(-1, nmea::waypoint{"POINT1"}));
}

TEST_F(Test_nmea_rte, set_waypoint_id_index_to_high)
{
	nmea::rte rte;

	EXPECT_ANY_THROW(rte.set_waypoint_id(10, nmea::waypoint{"POINT1"}));
}

TEST_F(Test_nmea_rte, get_waypoint_id)
{
	nmea::rte rte;
	rte.set_n_messages(1);
	rte.set_waypoint_id(0, nmea::waypoint{"POINT1"});

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
