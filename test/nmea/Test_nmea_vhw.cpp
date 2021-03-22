#include <marnav/nmea/vhw.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_vhw : public ::testing::Test
{
};

TEST_F(Test_nmea_vhw, contruction)
{
	EXPECT_NO_THROW(nmea::vhw vhw);
}

TEST_F(Test_nmea_vhw, properties)
{
	nmea_sentence_traits<nmea::vhw>();
}

TEST_F(Test_nmea_vhw, parse)
{
	auto s = nmea::make_sentence("$IIVHW,,,211.0,M,0.00,N,0.00,K*2D");
	ASSERT_NE(nullptr, s);

	auto vhw = nmea::sentence_cast<nmea::vhw>(s);
	ASSERT_NE(nullptr, vhw);

	auto heading = vhw->get_heading_magn();
	EXPECT_TRUE(heading.has_value());
	EXPECT_NEAR(211.0, heading.value(), 1e-8);
}

TEST_F(Test_nmea_vhw, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vhw>(nmea::talker::none, {7, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vhw>(nmea::talker::none, {9, "@"}));
}

TEST_F(Test_nmea_vhw, empty_to_string)
{
	nmea::vhw vhw;

	EXPECT_STREQ("$IIVHW,,,,,,,,*49", nmea::to_string(vhw).c_str());
}

TEST_F(Test_nmea_vhw, set_heading)
{
	nmea::vhw vhw;
	vhw.set_heading_magn(45.8);

	EXPECT_STREQ("$IIVHW,,,45.8,M,,,,*13", nmea::to_string(vhw).c_str());
}

TEST_F(Test_nmea_vhw, set_speed_knots)
{
	nmea::vhw vhw;
	vhw.set_speed_knots(units::knots{12.5});

	EXPECT_STREQ("$IIVHW,,,,,12.5,N,,*1F", nmea::to_string(vhw).c_str());
}

TEST_F(Test_nmea_vhw, set_speed_kmh)
{
	nmea::vhw vhw;
	vhw.set_speed_kmh(units::kilometers_per_hour{13.5});

	EXPECT_STREQ("$IIVHW,,,,,,,13.5,K*1B", nmea::to_string(vhw).c_str());
}
}
