#include <gtest/gtest.h>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_apb : public ::testing::Test
{
};

TEST_F(Test_nmea_apb, contruction)
{
	EXPECT_NO_THROW(nmea::apb apb);
}

TEST_F(Test_nmea_apb, properties)
{
	nmea_sentence_traits<nmea::apb>();
}

TEST_F(Test_nmea_apb, parse)
{
	auto s = nmea::make_sentence("$GPAPB,A,A,0.10,R,N,V,V,11.0,M,DEST,11.0,M,11.0,M*12");
	ASSERT_NE(nullptr, s);

	auto apb = nmea::sentence_cast<nmea::apb>(s);
	ASSERT_NE(nullptr, apb);
}

TEST_F(Test_nmea_apb, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::apb>(nmea::talker_id::none, {13, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::apb>(nmea::talker_id::none, {16, "@"}));
}

TEST_F(Test_nmea_apb, empty_to_string)
{
	nmea::apb apb;

	EXPECT_STREQ("$GPAPB,,,,,,,,,,,,,,,*68", nmea::to_string(apb).c_str());
}

TEST_F(Test_nmea_apb, set_waypoint)
{
	nmea::apb apb;
	apb.set_waypoint_id(nmea::waypoint{"ABC"});

	EXPECT_STREQ("$GPAPB,,,,,,,,,,ABC,,,,,*28", nmea::to_string(apb).c_str());
}

TEST_F(Test_nmea_apb, set_bearing_origin_to_destination)
{
	nmea::apb apb;
	apb.set_bearing_origin_to_destination(11, nmea::reference::MAGNETIC);
	EXPECT_STREQ("$GPAPB,,,,,,,,11.0,M,,,,,,*3B", nmea::to_string(apb).c_str());
}

TEST_F(Test_nmea_apb, set_bearing_pos_to_destination)
{
	nmea::apb apb;
	apb.set_bearing_pos_to_destination(11, nmea::reference::MAGNETIC);
	EXPECT_STREQ("$GPAPB,,,,,,,,,,,11.0,M,,,*3B", nmea::to_string(apb).c_str());
}

TEST_F(Test_nmea_apb, get_bearing_pos_to_destination)
{
	auto s = nmea::make_sentence("$GPAPB,A,A,0.10,R,N,V,V,11.0,M,DEST,11.0,M,11.0,M*12");
	ASSERT_NE(nullptr, s);

	auto apb = nmea::sentence_cast<nmea::apb>(s);
	ASSERT_NE(nullptr, apb);

	EXPECT_NEAR(11.0, *apb->get_bearing_pos_to_destination(), 1.0e-4);
	EXPECT_EQ(nmea::reference::MAGNETIC, *apb->get_bearing_pos_to_destination_ref());
}

TEST_F(Test_nmea_apb, set_heading_to_steer_to_destination)
{
	nmea::apb apb;
	apb.set_heading_to_steer_to_destination(11, nmea::reference::MAGNETIC);

	EXPECT_STREQ("$GPAPB,,,,,,,,,,,,,11.0,M,*3B", nmea::to_string(apb).c_str());
}

TEST_F(Test_nmea_apb, get_heading_to_steer)
{
	auto s = nmea::make_sentence("$GPAPB,A,A,0.10,R,N,V,V,11.0,M,DEST,11.0,M,11.0,M*12");
	ASSERT_NE(nullptr, s);

	auto apb = nmea::sentence_cast<nmea::apb>(s);
	ASSERT_NE(nullptr, apb);

	EXPECT_NEAR(11.0, *apb->get_heading_to_steer_to_destination(), 1.0e-4);
	EXPECT_EQ(nmea::reference::MAGNETIC, *apb->get_heading_to_steer_to_destination_ref());
}

TEST_F(Test_nmea_apb, set_mode_indicator)
{
	nmea::apb apb;
	apb.set_mode_indicator(nmea::mode_indicator::autonomous);
	EXPECT_STREQ("$GPAPB,,,,,,,,,,,,,,,A*29", nmea::to_string(apb).c_str());
}

TEST_F(Test_nmea_apb, set_mode_indicator_exception)
{
	nmea::apb apb;
	EXPECT_NO_THROW(apb.set_mode_indicator(nmea::mode_indicator::invalid));
	EXPECT_NO_THROW(apb.set_mode_indicator(nmea::mode_indicator::autonomous));
	EXPECT_NO_THROW(apb.set_mode_indicator(nmea::mode_indicator::differential));
	EXPECT_ANY_THROW(apb.set_mode_indicator(nmea::mode_indicator::estimated));
	EXPECT_ANY_THROW(apb.set_mode_indicator(nmea::mode_indicator::manual_input));
	EXPECT_ANY_THROW(apb.set_mode_indicator(nmea::mode_indicator::simulated));
	EXPECT_ANY_THROW(apb.set_mode_indicator(nmea::mode_indicator::data_not_valid));
	EXPECT_ANY_THROW(apb.set_mode_indicator(nmea::mode_indicator::precise));
}
}
