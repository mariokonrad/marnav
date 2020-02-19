#include <gtest/gtest.h>
#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_aam : public ::testing::Test
{
};

TEST_F(Test_nmea_aam, contruction)
{
	EXPECT_NO_THROW(nmea::aam aam);
}

TEST_F(Test_nmea_aam, properties)
{
	nmea_sentence_traits<nmea::aam>();
}

TEST_F(Test_nmea_aam, parse)
{
	auto s = nmea::make_sentence("$GPAAM,A,A,0.5,N,POINT1*6E");
	ASSERT_NE(nullptr, s);

	auto aam = nmea::sentence_cast<nmea::aam>(s);
	ASSERT_NE(nullptr, aam);

	auto radius = aam->get_arrival_circle_radius();
	EXPECT_NEAR(0.5, radius.get<marnav::units::nautical_miles>().value(), 1e-8);
}

TEST_F(Test_nmea_aam, parse_wrong_distance_unit)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPAAM,,,0.5,M,POINT1*6D"));
}

TEST_F(Test_nmea_aam, parse_missing_distance_unit)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPAAM,,,0.5,,POINT1*20"));
}

TEST_F(Test_nmea_aam, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::aam>(nmea::talker_id::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::aam>(nmea::talker_id::none, {6, "@"}));
}

TEST_F(Test_nmea_aam, empty_to_string)
{
	nmea::aam aam;

	EXPECT_STREQ("$GPAAM,V,V,0,N,*08", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_arrival_circle_entered_ok)
{
	nmea::aam aam;
	aam.set_arrival_circle_entered(nmea::status::ok);

	EXPECT_STREQ("$GPAAM,A,V,0,N,*1F", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_arrival_circle_entered_warning)
{
	nmea::aam aam;
	aam.set_arrival_circle_entered(nmea::status::warning);

	EXPECT_STREQ("$GPAAM,V,V,0,N,*08", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_arrival_circle_entered_invalid_status)
{
	nmea::aam aam;
	EXPECT_THROW(
		aam.set_arrival_circle_entered(static_cast<nmea::status>('?')), std::invalid_argument);
}

TEST_F(Test_nmea_aam, set_perpendicular_passed_ok)
{
	nmea::aam aam;
	aam.set_perpendicular_passed(nmea::status::ok);

	EXPECT_STREQ("$GPAAM,V,A,0,N,*1F", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_perpendicular_passed_warning)
{
	nmea::aam aam;
	aam.set_perpendicular_passed(nmea::status::warning);

	EXPECT_STREQ("$GPAAM,V,V,0,N,*08", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_perpendicular_passed_invalid_status)
{
	nmea::aam aam;
	EXPECT_THROW(
		aam.set_perpendicular_passed(static_cast<nmea::status>('?')), std::invalid_argument);
}

TEST_F(Test_nmea_aam, set_arrival_circle_radius)
{
	nmea::aam aam;
	aam.set_arrival_circle_radius(marnav::units::nautical_miles{1.2});

	EXPECT_STREQ("$GPAAM,V,V,1.2,N,*15", nmea::to_string(aam).c_str());
}

TEST_F(Test_nmea_aam, set_arrival_circle_radius_negative)
{
	nmea::aam aam;

	EXPECT_THROW(aam.set_arrival_circle_radius(marnav::units::nautical_miles{-1.2}),
		std::invalid_argument);
}

TEST_F(Test_nmea_aam, set_waypoint_id)
{
	nmea::aam aam;
	aam.set_waypoint_id(nmea::waypoint{"wpt1"});

	EXPECT_STREQ("$GPAAM,V,V,0,N,wpt1*4A", nmea::to_string(aam).c_str());
}
}
