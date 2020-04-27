#include <gtest/gtest.h>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_gga : public ::testing::Test
{
};

TEST_F(Test_nmea_gga, contruction)
{
	EXPECT_NO_THROW(nmea::gga gga);
}

TEST_F(Test_nmea_gga, properties)
{
	nmea_sentence_traits<nmea::gga>();
}

TEST_F(Test_nmea_gga, parse)
{
	static const std::vector<std::string> TESTS
		= {"$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47"};

	for (const auto & test : TESTS) {
		auto s = nmea::make_sentence(test);
		EXPECT_NE(nullptr, s);
		if (s) {
			auto gga = nmea::sentence_cast<nmea::gga>(s);
			EXPECT_NE(nullptr, gga);
		}
	}
}

TEST_F(Test_nmea_gga, parse_failure)
{
	static const std::vector<std::string> TESTS = {
		"$GPGGA,171537,3350.975,N,11823.991,W,2,07,1.1,-25.8,M,,M,1.8,,D*17", // Raytheon RN300
		"$GPGGA,171538,3350.974,N,11823.991,W,2,07,1.1,-25.8,M,,M,1.8,,D*19" // Raytheon RN300
	};

	for (const auto & test : TESTS) {
		EXPECT_ANY_THROW(nmea::make_sentence(test));
	}
}

TEST_F(Test_nmea_gga, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::gga>(nmea::talker::none, {13, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::gga>(nmea::talker::none, {15, "@"}));
}

TEST_F(Test_nmea_gga, empty_to_string)
{
	nmea::gga gga;

	EXPECT_STREQ("$GPGGA,,,,,,,,,,,,,,*56", nmea::to_string(gga).c_str());
}

TEST_F(Test_nmea_gga, set_time)
{
	nmea::gga gga;
	gga.set_time(nmea::time{12, 34, 56, 0});

	EXPECT_STREQ("$GPGGA,123456,,,,,,,,,,,,,*51", nmea::to_string(gga).c_str());
}

TEST_F(Test_nmea_gga, set_lat_north)
{
	nmea::gga gga;
	gga.set_lat(geo::latitude{12.345});

	EXPECT_STREQ("$GPGGA,,1220.7000,N,,,,,,,,,,,*30", nmea::to_string(gga).c_str());
}

TEST_F(Test_nmea_gga, set_lat_south)
{
	nmea::gga gga;
	gga.set_lat(geo::latitude{-12.345});

	EXPECT_STREQ("$GPGGA,,1220.7000,S,,,,,,,,,,,*2D", nmea::to_string(gga).c_str());
}

TEST_F(Test_nmea_gga, set_lon_west)
{
	nmea::gga gga;
	gga.set_lon(geo::longitude{-123.45});

	EXPECT_STREQ("$GPGGA,,,,12327.0000,W,,,,,,,,,*1A", nmea::to_string(gga).c_str());
}

TEST_F(Test_nmea_gga, set_lon_east)
{
	nmea::gga gga;
	gga.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPGGA,,,,12327.0000,E,,,,,,,,,*08", nmea::to_string(gga).c_str());
}
}
