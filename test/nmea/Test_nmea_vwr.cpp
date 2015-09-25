#include <gtest/gtest.h>
#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_vwr : public ::testing::Test
{
};

TEST_F(Test_nmea_vwr, contruction) { EXPECT_NO_THROW(nmea::vwr vwr); }

TEST_F(Test_nmea_vwr, parse)
{
	auto s = nmea::make_sentence("$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*4A");
	ASSERT_NE(nullptr, s);

	auto vwr = nmea::sentence_cast<nmea::vwr>(s);
	ASSERT_NE(nullptr, vwr);

	auto angle = vwr->get_angle();
	EXPECT_TRUE(angle.available());
	EXPECT_NEAR(84.0, angle.value(), 1e-8);

	auto side = vwr->get_angle_side();
	EXPECT_TRUE(side.available());
	EXPECT_EQ(nmea::side::right, side.value());
}

TEST_F(Test_nmea_vwr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::vwr::parse("@@", {7, "@"}));
	EXPECT_ANY_THROW(nmea::vwr::parse("@@", {9, "@"}));
}

TEST_F(Test_nmea_vwr, empty_to_string)
{
	nmea::vwr vwr;

	EXPECT_STREQ("$IIVWR,,,,,,,,*53", nmea::to_string(vwr).c_str());
}

TEST_F(Test_nmea_vwr, set_angle_left)
{
	nmea::vwr vwr;
	vwr.set_angle(22.5, nmea::side::left);

	EXPECT_STREQ("$IIVWR,22.5,L,,,,,,*04", nmea::to_string(vwr).c_str());
}

TEST_F(Test_nmea_vwr, set_angle_right)
{
	nmea::vwr vwr;
	vwr.set_angle(22.5, nmea::side::right);

	EXPECT_STREQ("$IIVWR,22.5,R,,,,,,*1A", nmea::to_string(vwr).c_str());
}

TEST_F(Test_nmea_vwr, set_speed_knots)
{
	nmea::vwr vwr;
	vwr.set_speed_knots(12.5);

	EXPECT_STREQ("$IIVWR,,,12.5,N,,,,*05", nmea::to_string(vwr).c_str());
}

TEST_F(Test_nmea_vwr, set_speed_mps)
{
	nmea::vwr vwr;
	vwr.set_speed_mps(2.5);

	EXPECT_STREQ("$IIVWR,,,,,2.5,M,,*37", nmea::to_string(vwr).c_str());
}

TEST_F(Test_nmea_vwr, set_speed_kmh)
{
	nmea::vwr vwr;
	vwr.set_speed_kmh(13.5);

	EXPECT_STREQ("$IIVWR,,,,,,,13.5,K*01", nmea::to_string(vwr).c_str());
}
}

