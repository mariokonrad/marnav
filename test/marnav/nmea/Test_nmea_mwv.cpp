#include <marnav/nmea/mwv.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_mwv : public ::testing::Test
{
};

TEST_F(test_nmea_mwv, contruction)
{
	EXPECT_NO_THROW(nmea::mwv mwv);
}

TEST_F(test_nmea_mwv, properties)
{
	nmea_sentence_traits<nmea::mwv>();
}

TEST_F(test_nmea_mwv, parse)
{
	auto s = nmea::make_sentence("$IIMWV,084.0,R,10.4,N,A*04");
	ASSERT_NE(nullptr, s);

	auto mwv = nmea::sentence_cast<nmea::mwv>(s);
	ASSERT_NE(nullptr, mwv);

	auto angle = mwv->get_angle();
	ASSERT_TRUE(angle.has_value());
	EXPECT_NEAR(84.0, angle.value(), 1e-8);

	auto speed = mwv->get_speed();
	ASSERT_TRUE(speed.has_value());
	EXPECT_NEAR(10.4, speed->get<units::knots>().value(), 1e-8);
}

TEST_F(test_nmea_mwv, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mwv>(nmea::talker::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mwv>(nmea::talker::none, {6, "@"}));
}

TEST_F(test_nmea_mwv, empty_to_string)
{
	nmea::mwv mwv;

	EXPECT_STREQ("$IIMWV,,,,,*60", nmea::to_string(mwv).c_str());
}

TEST_F(test_nmea_mwv, set_angle)
{
	nmea::mwv mwv;
	mwv.set_angle(12.5, nmea::reference::RELATIVE);

	EXPECT_STREQ("$IIMWV,12.5,R,,,*2A", nmea::to_string(mwv).c_str());
}

TEST_F(test_nmea_mwv, set_speed_knots_explicit)
{
	nmea::mwv mwv;
	mwv.set_speed(units::knots{22.5}, nmea::unit::velocity::knot);

	EXPECT_STREQ("$IIMWV,,,22.5,N,*35", nmea::to_string(mwv).c_str());
}

TEST_F(test_nmea_mwv, set_speed_knots_implicit)
{
	nmea::mwv mwv;
	mwv.set_speed(units::knots{22.5});

	EXPECT_STREQ("$IIMWV,,,22.5,N,*35", nmea::to_string(mwv).c_str());
}
}
