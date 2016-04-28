#include <gtest/gtest.h>
#include <marnav/nmea/vpw.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_vpw : public ::testing::Test
{
};

TEST_F(Test_nmea_vpw, contruction) { EXPECT_NO_THROW(nmea::vpw vpw); }

TEST_F(Test_nmea_vpw, properties) { nmea_sentence_traits<nmea::vpw>(); }

TEST_F(Test_nmea_vpw, parse)
{
	auto s = nmea::make_sentence("$IIVPW,4.5,N,6.7,M*52");
	ASSERT_NE(nullptr, s);

	auto vpw = nmea::sentence_cast<nmea::vpw>(s);
	ASSERT_NE(nullptr, vpw);
}

TEST_F(Test_nmea_vpw, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::vpw>("@@", {3, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::vpw>("@@", {5, "@"}));
}

TEST_F(Test_nmea_vpw, empty_to_string)
{
	nmea::vpw vpw;

	EXPECT_STREQ("$IIVPW,,,,*51", nmea::to_string(vpw).c_str());
}

TEST_F(Test_nmea_vpw, set_speed_knots)
{
	nmea::vpw vpw;
	vpw.set_speed_knots(4.5);

	EXPECT_STREQ("$IIVPW,4.5,N,,*30", nmea::to_string(vpw).c_str());
}

TEST_F(Test_nmea_vpw, set_speed_mps)
{
	nmea::vpw vpw;
	vpw.set_speed_mps(4.5);

	EXPECT_STREQ("$IIVPW,,,4.5,M*33", nmea::to_string(vpw).c_str());
}
}
