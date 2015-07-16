#include <gtest/gtest.h>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gll : public ::testing::Test
{
};

TEST_F(Test_nmea_gll, contruction) { nmea::gll gll; }

TEST_F(Test_nmea_gll, parse)
{
	auto s = nmea::make_sentence("$GPGLL,,,,,,*50");
	ASSERT_NE(nullptr, s);

	auto gll = nmea::sentence_cast<nmea::gll>(s);
	ASSERT_NE(nullptr, gll);
}

TEST_F(Test_nmea_gll, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::gll::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::gll::parse("@@", {7, "@"}));
}

TEST_F(Test_nmea_gll, empty_to_string)
{
	nmea::gll gll;

	EXPECT_STREQ("$GPGLL,,,,,,*50", nmea::to_string(gll).c_str());
}

TEST_F(Test_nmea_gll, set_lat_north)
{
	nmea::gll gll;
	gll.set_lat(geo::latitude{12.345});

	EXPECT_STREQ("$GPGLL,1220.7000,N,,,,*36", nmea::to_string(gll).c_str());
}

TEST_F(Test_nmea_gll, set_lat_south)
{
	nmea::gll gll;
	gll.set_lat(geo::latitude{-12.345});

	EXPECT_STREQ("$GPGLL,1220.7000,S,,,,*2B", nmea::to_string(gll).c_str());
}

TEST_F(Test_nmea_gll, set_lon_west)
{
	nmea::gll gll;
	gll.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPGLL,,,12327.0000,W,,*1C", nmea::to_string(gll).c_str());
}

TEST_F(Test_nmea_gll, set_lon_east)
{
	nmea::gll gll;
	gll.set_lon(geo::longitude{-123.45});

	EXPECT_STREQ("$GPGLL,,,12327.0000,E,,*0E", nmea::to_string(gll).c_str());
}
}

