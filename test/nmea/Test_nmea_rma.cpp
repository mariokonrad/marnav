#include <gtest/gtest.h>
#include <marnav/nmea/rma.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rma : public ::testing::Test
{
};

TEST_F(Test_nmea_rma, contruction) { EXPECT_NO_THROW(nmea::rma rma); }

TEST_F(Test_nmea_rma, properties) { nmea_sentence_traits<nmea::rma>(); }

TEST_F(Test_nmea_rma, parse)
{
	auto s = nmea::make_sentence("$GPRMA,,,,,,,,,,,*65");
	ASSERT_NE(nullptr, s);

	auto rma = nmea::sentence_cast<nmea::rma>(s);
	ASSERT_NE(nullptr, rma);
}

TEST_F(Test_nmea_rma, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::rma::parse("@@", {10, "@"}));
	EXPECT_ANY_THROW(nmea::rma::parse("@@", {12, "@"}));
}

TEST_F(Test_nmea_rma, empty_to_string)
{
	nmea::rma rma;

	EXPECT_STREQ("$GPRMA,,,,,,,,,,,*65", nmea::to_string(rma).c_str());
}

TEST_F(Test_nmea_rma, set_lat_north)
{
	nmea::rma rma;
	rma.set_lat(geo::latitude{12, 34, 56, geo::latitude::hemisphere::north});

	EXPECT_STREQ("$GPRMA,,1234.9333,N,,,,,,,,*0B", nmea::to_string(rma).c_str());
}

TEST_F(Test_nmea_rma, set_lat_south)
{
	nmea::rma rma;
	rma.set_lat(geo::latitude{12, 34, 56, geo::latitude::hemisphere::south});

	EXPECT_STREQ("$GPRMA,,1234.9333,S,,,,,,,,*16", nmea::to_string(rma).c_str());
}

TEST_F(Test_nmea_rma, set_lon_east)
{
	nmea::rma rma;
	rma.set_lon(geo::longitude{123, 45, 56, geo::longitude::hemisphere::east});

	EXPECT_STREQ("$GPRMA,,,,12345.9333,E,,,,,,*35", nmea::to_string(rma).c_str());
}

TEST_F(Test_nmea_rma, set_lon_west)
{
	nmea::rma rma;
	rma.set_lon(geo::longitude{123, 45, 56, geo::longitude::hemisphere::west});

	EXPECT_STREQ("$GPRMA,,,,12345.9333,W,,,,,,*27", nmea::to_string(rma).c_str());
}
}
