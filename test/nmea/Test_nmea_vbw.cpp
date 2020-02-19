#include <gtest/gtest.h>
#include <marnav/nmea/vbw.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{
using namespace marnav;

class Test_nmea_vbw : public ::testing::Test
{
};

TEST_F(Test_nmea_vbw, contruction)
{
	EXPECT_NO_THROW(nmea::vbw vbw);
}

TEST_F(Test_nmea_vbw, properties)
{
	nmea_sentence_traits<nmea::vbw>();
}

TEST_F(Test_nmea_vbw, parse)
{
	auto s = nmea::make_sentence("$IIVBW,1.0,-1.5,A,1.0,0.5,A*6F");
	ASSERT_NE(nullptr, s);

	auto vbw = nmea::sentence_cast<nmea::vbw>(s);
	ASSERT_NE(nullptr, vbw);
}

TEST_F(Test_nmea_vbw, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vbw>(nmea::talker_id::none, {5, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vbw>(nmea::talker_id::none, {7, "@"}));
}

TEST_F(Test_nmea_vbw, empty_to_string)
{
	nmea::vbw vbw;

	EXPECT_STREQ("$IIVBW,,,,,,*43", nmea::to_string(vbw).c_str());
}

TEST_F(Test_nmea_vbw, set_water_speed)
{
	nmea::vbw vbw;
	vbw.set_water_speed(units::knots{1.0}, units::knots{2.0}, nmea::status::ok);

	EXPECT_STREQ("$IIVBW,1.0,2.0,A,,,*01", nmea::to_string(vbw).c_str());
}

TEST_F(Test_nmea_vbw, set_water_speed_negative)
{
	nmea::vbw vbw;
	vbw.set_water_speed(units::knots{-1.0}, units::knots{-2.0}, nmea::status::ok);

	EXPECT_STREQ("$IIVBW,-1.0,-2.0,A,,,*01", nmea::to_string(vbw).c_str());
}

TEST_F(Test_nmea_vbw, set_ground_speed)
{
	nmea::vbw vbw;
	vbw.set_ground_speed(units::knots{1.0}, units::knots{2.0}, nmea::status::ok);

	EXPECT_STREQ("$IIVBW,,,,1.0,2.0,A*01", nmea::to_string(vbw).c_str());
}

TEST_F(Test_nmea_vbw, set_ground_speed_negative)
{
	nmea::vbw vbw;
	vbw.set_ground_speed(units::knots{-1.0}, units::knots{-2.0}, nmea::status::ok);

	EXPECT_STREQ("$IIVBW,,,,-1.0,-2.0,A*01", nmea::to_string(vbw).c_str());
}
}
