#include <gtest/gtest.h>
#include <marnav/nmea/vlw.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_vlw : public ::testing::Test
{
};

TEST_F(Test_nmea_vlw, contruction) { EXPECT_NO_THROW(nmea::vlw vlw); }

TEST_F(Test_nmea_vlw, parse)
{
	auto s = nmea::make_sentence("$IIVLW,7803.2,N,0.00,N*43");
	ASSERT_NE(nullptr, s);

	auto vlw = nmea::sentence_cast<nmea::vlw>(s);
	ASSERT_NE(nullptr, vlw);

	auto distance = vlw->get_distance_cum();
	EXPECT_TRUE(distance.available());
	EXPECT_NEAR(7803.2, distance.value(), 1e-8);
}

TEST_F(Test_nmea_vlw, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::vlw::parse("@@", {3, "@"}));
	EXPECT_ANY_THROW(nmea::vlw::parse("@@", {5, "@"}));
}

TEST_F(Test_nmea_vlw, empty_to_string)
{
	nmea::vlw vlw;

	EXPECT_STREQ("$IIVLW,,,,*4D", nmea::to_string(vlw).c_str());
}

TEST_F(Test_nmea_vlw, set_distance_cum_nm)
{
	nmea::vlw vlw;
	vlw.set_distance_cum_nm(123.4);

	EXPECT_STREQ("$IIVLW,123.4,N,,*29", nmea::to_string(vlw).c_str());
}

TEST_F(Test_nmea_vlw, set_distance_reset_nm)
{
	nmea::vlw vlw;
	vlw.set_distance_reset_nm(12.4);

	EXPECT_STREQ("$IIVLW,,,12.4,N*1A", nmea::to_string(vlw).c_str());
}
}

