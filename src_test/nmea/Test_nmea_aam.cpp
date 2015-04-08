#include <gtest/gtest.h>
#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_aam : public ::testing::Test
{
};

TEST_F(Test_nmea_aam, contruction) { nmea::aam aam; }

TEST_F(Test_nmea_aam, size) { EXPECT_EQ(64u, sizeof(nmea::aam)); }

TEST_F(Test_nmea_aam, parse)
{
	auto s = nmea::make_sentence("$GPAAM,A,A,0.5,N,POINT1*6E");
	ASSERT_NE(nullptr, s);

	auto aam = nmea::sentence_cast<nmea::aam>(s);
	ASSERT_NE(nullptr, aam);

	auto radius = aam->get_arrival_circle_radius();
	EXPECT_TRUE(radius.available());
	EXPECT_EQ(0.5, radius.value());
}

TEST_F(Test_nmea_aam, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::aam::parse("@@", {4, "@"}));
	EXPECT_ANY_THROW(nmea::aam::parse("@@", {6, "@"}));
}

TEST_F(Test_nmea_aam, empty_to_string)
{
	nmea::aam aam;

	EXPECT_STREQ("$GPAAM,,,,,*76", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_arrival_circle_radius)
{
	nmea::aam aam;
	aam.set_arrival_circle_radius(1.2);

	EXPECT_STREQ("$GPAAM,,,1.2,N,*15", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_waypoint_id)
{
	nmea::aam aam;
	aam.set_waypoint_id("wpt1");

	EXPECT_STREQ("$GPAAM,,,,,wpt1*34", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_waypoint_id_string_to_large)
{
	nmea::aam aam;

	EXPECT_ANY_THROW(aam.set_waypoint_id("123456789"));
}
}

