#include <gtest/gtest.h>
#include <marnav/nmea/tll.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_tll : public ::testing::Test
{
};

TEST_F(Test_nmea_tll, contruction) { EXPECT_NO_THROW(nmea::tll tll); }

TEST_F(Test_nmea_tll, properties) { nmea_sentence_traits<nmea::tll>(); }

TEST_F(Test_nmea_tll, parse)
{
	auto s = nmea::make_sentence("$GPTLL,00,0000.0000,N,00000.0000,E,,000000,T,*00");
	ASSERT_NE(nullptr, s);

	auto tll = nmea::sentence_cast<nmea::tll>(s);
	ASSERT_NE(nullptr, tll);
}

TEST_F(Test_nmea_tll, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::tll::parse("@@", {8, "@"}));
	EXPECT_ANY_THROW(nmea::tll::parse("@@", {10, "@"}));
}

TEST_F(Test_nmea_tll, empty_to_string)
{
	nmea::tll tll;

	EXPECT_STREQ(
		"$GPTLL,00,0000.0000,N,00000.0000,E,,000000,T,*00", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, set_lat)
{
	nmea::tll tll;
	tll.set_lat(geo::latitude{12.34});

	EXPECT_STREQ(
		"$GPTLL,00,1220.4000,N,00000.0000,E,,000000,T,*05", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, set_lon_west)
{
	nmea::tll tll;
	tll.set_lon(geo::longitude{-123.45});

	EXPECT_STREQ(
		"$GPTLL,00,0000.0000,N,12327.0000,W,,000000,T,*17", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, set_lon_east)
{
	nmea::tll tll;
	tll.set_lon(geo::longitude{123.45});

	EXPECT_STREQ(
		"$GPTLL,00,0000.0000,N,12327.0000,E,,000000,T,*05", nmea::to_string(tll).c_str());
}
}
