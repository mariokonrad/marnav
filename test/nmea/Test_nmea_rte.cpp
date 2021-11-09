#include <marnav/nmea/rte.hpp>
#include "exception_helper.hpp"
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

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

TEST_F(Test_nmea_rte, parse_no_ids)
{
	auto s = nmea::make_sentence("$GPRTE,1,1,c,*37");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(1u, rte->get_n_messages());
	EXPECT_EQ(1u, rte->get_message_number());
	EXPECT_EQ(nmea::route_mode::complete, rte->get_message_mode());
	EXPECT_FALSE(rte->get_route_id());

	for (int i = 0; i < nmea::rte::max_waypoints; ++i)
		EXPECT_FALSE(rte->get_waypoint_id(i));
}

TEST_F(Test_nmea_rte, parse_route_id_and_no_waypoint_ids)
{
	auto s = nmea::make_sentence("$GPRTE,1,1,c,r0*75");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(1u, rte->get_n_messages());
	EXPECT_EQ(1u, rte->get_message_number());
	EXPECT_EQ(nmea::route_mode::complete, rte->get_message_mode());

	const auto r = rte->get_route_id();
	EXPECT_TRUE(r);
	EXPECT_STREQ("r0", r->c_str());

	for (int i = 0; i < nmea::rte::max_waypoints; ++i)
		EXPECT_FALSE(rte->get_waypoint_id(i));
}

TEST_F(Test_nmea_rte, parse_route_id_and_one_waypoint_id)
{
	auto s = nmea::make_sentence("$GPRTE,1,1,c,r0,wp0*6E");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(1u, rte->get_n_messages());
	EXPECT_EQ(1u, rte->get_message_number());
	EXPECT_EQ(nmea::route_mode::complete, rte->get_message_mode());

	const auto r = rte->get_route_id();
	EXPECT_TRUE(r);
	EXPECT_STREQ("r0", r->c_str());

	const auto wp0 = rte->get_waypoint_id(0);
	EXPECT_TRUE(!!wp0);
	EXPECT_STREQ("wp0", wp0->c_str());

	for (int i = 1; i < nmea::rte::max_waypoints; ++i)
		EXPECT_FALSE(rte->get_waypoint_id(i));
}

TEST_F(Test_nmea_rte, parse_invalid_number_of_arguments)
{
	EXPECT_EXCEPTION_STREQ(
		nmea::detail::factory::sentence_parse<nmea::rte>(nmea::talker::none, {3, "@"}),
		std::invalid_argument, "invalid number of fields in rte");

	EXPECT_EXCEPTION_STREQ(
		nmea::detail::factory::sentence_parse<nmea::rte>(nmea::talker::none, {15, "@"}),
		std::invalid_argument, "invalid number of fields in rte");
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

	EXPECT_STREQ("$GPRTE,99,1,c,*06", nmea::to_string(rte).c_str());
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
	rte.set_message_mode(marnav::nmea::route_mode::complete);

	EXPECT_STREQ("$GPRTE,1,1,c,*37", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_message_mode_working)
{
	nmea::rte rte;
	rte.set_message_mode(marnav::nmea::route_mode::working);

	EXPECT_STREQ("$GPRTE,1,1,w,*23", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, set_route_id)
{
	nmea::rte rte;
	rte.set_route_id(nmea::route{"ROUTE1"});

	EXPECT_STREQ("$GPRTE,1,1,c,ROUTE1*5F", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, add_waypoint_id)
{
	nmea::rte rte;
	rte.add_waypoint_id(nmea::waypoint{"POINT1"});

	EXPECT_STREQ("$GPRTE,1,1,c,,POINT1*66", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, add_multiple_waypoint_ids_no_route_id)
{
	nmea::rte rte;
	rte.add_waypoint_id(nmea::waypoint{"POINT1"});
	rte.add_waypoint_id(nmea::waypoint{"POINT2"});

	EXPECT_STREQ("$GPRTE,1,1,c,,POINT1,POINT2*34", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, add_multiple_waypoint_ids_with_route_id)
{
	nmea::rte rte;
	rte.set_route_id(nmea::route{"0"});
	rte.add_waypoint_id(nmea::waypoint{"POINT1"});
	rte.add_waypoint_id(nmea::waypoint{"POINT2"});

	EXPECT_STREQ("$GPRTE,1,1,c,0,POINT1,POINT2*04", nmea::to_string(rte).c_str());
}

TEST_F(Test_nmea_rte, add_to_many_waypoints)
{
	nmea::rte rte;
	rte.add_waypoint_id(nmea::waypoint{"P0"});
	rte.add_waypoint_id(nmea::waypoint{"P1"});
	rte.add_waypoint_id(nmea::waypoint{"P2"});
	rte.add_waypoint_id(nmea::waypoint{"P3"});
	rte.add_waypoint_id(nmea::waypoint{"P4"});
	rte.add_waypoint_id(nmea::waypoint{"P5"});
	rte.add_waypoint_id(nmea::waypoint{"P6"});
	rte.add_waypoint_id(nmea::waypoint{"P7"});
	rte.add_waypoint_id(nmea::waypoint{"P8"});
	rte.add_waypoint_id(nmea::waypoint{"P9"});

	EXPECT_ANY_THROW(rte.add_waypoint_id(nmea::waypoint{"P10"}));
}

TEST_F(Test_nmea_rte, add_to_waypoints_then_clear)
{
	nmea::rte rte;
	rte.add_waypoint_id(nmea::waypoint{"P0"});
	rte.add_waypoint_id(nmea::waypoint{"P1"});
	rte.add_waypoint_id(nmea::waypoint{"P2"});

	EXPECT_EQ(3, rte.get_n_waypoints());

	rte.clear_waypoint_id();

	EXPECT_EQ(0, rte.get_n_waypoints());
}

TEST_F(Test_nmea_rte, get_waypoint_id)
{
	nmea::rte rte;
	rte.add_waypoint_id(nmea::waypoint{"POINT1"});

	auto wp = rte.get_waypoint_id(0);

	EXPECT_TRUE(wp.available());
	EXPECT_STREQ("POINT1", wp.value().c_str());
}

TEST_F(Test_nmea_rte, get_non_existing_waypoint)
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

TEST_F(Test_nmea_rte, example_found_on_internet_1)
{
	// found here: http://aprs.gids.nl/nmea/#rte

	auto s = nmea::make_sentence(
		"$GPRTE,2,1,c,0,PBRCPK,PBRTO,PTELGR,PPLAND,PYAMBU,PPFAIR,PWARRN,PMORTL,PLISMR*73");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(2, rte->get_n_messages());
	EXPECT_EQ(1, rte->get_message_number());

	EXPECT_EQ(nmea::route_mode::complete, rte->get_message_mode());

	EXPECT_TRUE(rte->get_route_id());
	EXPECT_STREQ("0", rte->get_route_id().value().c_str());

	EXPECT_EQ(9, rte->get_n_waypoints());

	EXPECT_STREQ("PBRCPK", rte->get_waypoint_id(0).value().c_str());
	EXPECT_STREQ("PBRTO", rte->get_waypoint_id(1).value().c_str());
	EXPECT_STREQ("PTELGR", rte->get_waypoint_id(2).value().c_str());
	EXPECT_STREQ("PPLAND", rte->get_waypoint_id(3).value().c_str());
	EXPECT_STREQ("PYAMBU", rte->get_waypoint_id(4).value().c_str());
	EXPECT_STREQ("PPFAIR", rte->get_waypoint_id(5).value().c_str());
	EXPECT_STREQ("PWARRN", rte->get_waypoint_id(6).value().c_str());
	EXPECT_STREQ("PMORTL", rte->get_waypoint_id(7).value().c_str());
	EXPECT_STREQ("PLISMR", rte->get_waypoint_id(8).value().c_str());
}

TEST_F(Test_nmea_rte, example_found_on_internet_2)
{
	// found here: http://aprs.gids.nl/nmea/#rte

	auto s = nmea::make_sentence("$GPRTE,2,2,c,0,PCRESY,GRYRIE,GCORIO,GWERR,GWESTG,7FED*34");
	ASSERT_NE(nullptr, s);

	auto rte = nmea::sentence_cast<nmea::rte>(s);
	ASSERT_NE(nullptr, rte);

	EXPECT_EQ(2, rte->get_n_messages());
	EXPECT_EQ(2, rte->get_message_number());

	EXPECT_EQ(nmea::route_mode::complete, rte->get_message_mode());

	EXPECT_TRUE(rte->get_route_id());
	EXPECT_STREQ("0", rte->get_route_id().value().c_str());

	EXPECT_EQ(6, rte->get_n_waypoints());

	EXPECT_STREQ("PCRESY", rte->get_waypoint_id(0).value().c_str());
	EXPECT_STREQ("GRYRIE", rte->get_waypoint_id(1).value().c_str());
	EXPECT_STREQ("GCORIO", rte->get_waypoint_id(2).value().c_str());
	EXPECT_STREQ("GWERR", rte->get_waypoint_id(3).value().c_str());
	EXPECT_STREQ("GWESTG", rte->get_waypoint_id(4).value().c_str());
	EXPECT_STREQ("7FED", rte->get_waypoint_id(5).value().c_str());
}
}
