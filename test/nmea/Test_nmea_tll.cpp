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
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::tll>("@@", {8, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::tll>("@@", {10, "@"}));
}

TEST_F(Test_nmea_tll, empty_to_string)
{
	nmea::tll tll;

	EXPECT_STREQ(
		"$GPTLL,00,0000.0000,N,00000.0000,E,,000000,T,*00", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, set_lat_north)
{
	nmea::tll tll;
	tll.set_lat(geo::latitude{12.34});

	EXPECT_STREQ(
		"$GPTLL,00,1220.4000,N,00000.0000,E,,000000,T,*05", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, get_latitude_north)
{
	const auto s = nmea::make_sentence("$GPTLL,00,1220.4000,N,00000.0000,E,,000000,T,*05");
	const auto tll = nmea::sentence_cast<nmea::tll>(s);

	EXPECT_EQ(geo::latitude{12.34}, tll->get_latitude());
}

TEST_F(Test_nmea_tll, set_lat_south)
{
	nmea::tll tll;
	tll.set_lat(geo::latitude{-12.34});

	EXPECT_STREQ(
		"$GPTLL,00,1220.4000,S,00000.0000,E,,000000,T,*18", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, get_latitude_south)
{
	const auto s = nmea::make_sentence("$GPTLL,00,1220.4000,S,00000.0000,E,,000000,T,*18");
	const auto tll = nmea::sentence_cast<nmea::tll>(s);

	EXPECT_EQ(geo::latitude{-12.34}, tll->get_latitude());
}

TEST_F(Test_nmea_tll, set_lon_west)
{
	nmea::tll tll;
	tll.set_lon(geo::longitude{-123.45});

	EXPECT_STREQ(
		"$GPTLL,00,0000.0000,N,12327.0000,W,,000000,T,*17", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, get_longitude_west)
{
	const auto s = nmea::make_sentence("$GPTLL,00,0000.0000,N,12327.0000,W,,000000,T,*17");
	const auto tll = nmea::sentence_cast<nmea::tll>(s);

	EXPECT_EQ(geo::longitude{-123.45}, tll->get_longitude());
}

TEST_F(Test_nmea_tll, set_lon_east)
{
	nmea::tll tll;
	tll.set_lon(geo::longitude{123.45});

	EXPECT_STREQ(
		"$GPTLL,00,0000.0000,N,12327.0000,E,,000000,T,*05", nmea::to_string(tll).c_str());
}

TEST_F(Test_nmea_tll, get_longitude_east)
{
	const auto s = nmea::make_sentence("$GPTLL,00,0000.0000,N,12327.0000,E,,000000,T,*05");
	const auto tll = nmea::sentence_cast<nmea::tll>(s);

	EXPECT_EQ(geo::longitude{123.45}, tll->get_longitude());
}

TEST_F(Test_nmea_tll, set_status)
{
	{
		nmea::tll tll;
		tll.set_status(nmea::target_status::lost);
		EXPECT_STREQ(
			"$GPTLL,00,0000.0000,N,00000.0000,E,,000000,L,*18", nmea::to_string(tll).c_str());
	}
	{
		nmea::tll tll;
		tll.set_status(nmea::target_status::query);
		EXPECT_STREQ(
			"$GPTLL,00,0000.0000,N,00000.0000,E,,000000,Q,*05", nmea::to_string(tll).c_str());
	}
	{
		nmea::tll tll;
		tll.set_status(nmea::target_status::tracking);
		EXPECT_STREQ(
			"$GPTLL,00,0000.0000,N,00000.0000,E,,000000,T,*00", nmea::to_string(tll).c_str());
	}
}

TEST_F(Test_nmea_tll, get_status)
{
	{
		const auto s = nmea::make_sentence("$GPTLL,00,0000.0000,N,00000.0000,E,,000000,L,*18");
		EXPECT_EQ(nmea::target_status::lost, nmea::sentence_cast<nmea::tll>(s)->get_status());
	}
	{
		const auto s = nmea::make_sentence("$GPTLL,00,0000.0000,N,00000.0000,E,,000000,Q,*05");
		EXPECT_EQ(nmea::target_status::query, nmea::sentence_cast<nmea::tll>(s)->get_status());
	}
	{
		const auto s = nmea::make_sentence("$GPTLL,00,0000.0000,N,00000.0000,E,,000000,T,*00");
		EXPECT_EQ(
			nmea::target_status::tracking, nmea::sentence_cast<nmea::tll>(s)->get_status());
	}
}
}
