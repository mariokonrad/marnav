#include <marnav/nmea/rma.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_rma : public ::testing::Test
{
};

TEST_F(test_nmea_rma, contruction)
{
	EXPECT_NO_THROW(nmea::rma rma);
}

TEST_F(test_nmea_rma, properties)
{
	nmea_sentence_traits<nmea::rma>();
}

TEST_F(test_nmea_rma, parse)
{
	auto s = nmea::make_sentence("$GPRMA,,,,,,,,,,,*65");
	ASSERT_NE(nullptr, s);

	auto rma = nmea::sentence_cast<nmea::rma>(s);
	ASSERT_NE(nullptr, rma);
}

TEST_F(test_nmea_rma, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rma>(nmea::talker::none, {10, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rma>(nmea::talker::none, {12, "@"}));
}

TEST_F(test_nmea_rma, empty_to_string)
{
	nmea::rma rma;

	EXPECT_STREQ("$GPRMA,,,,,,,,,,,*65", nmea::to_string(rma).c_str());
}

TEST_F(test_nmea_rma, set_lat_north)
{
	nmea::rma rma;
	rma.set_lat(geo::latitude{12, 34, 56, geo::latitude::hemisphere::north});

	EXPECT_STREQ("$GPRMA,,1234.9333,N,,,,,,,,*0B", nmea::to_string(rma).c_str());
}

TEST_F(test_nmea_rma, set_lat_south)
{
	nmea::rma rma;
	rma.set_lat(geo::latitude{12, 34, 56, geo::latitude::hemisphere::south});

	EXPECT_STREQ("$GPRMA,,1234.9333,S,,,,,,,,*16", nmea::to_string(rma).c_str());
}

TEST_F(test_nmea_rma, set_lon_east)
{
	nmea::rma rma;
	rma.set_lon(geo::longitude{123, 45, 56, geo::longitude::hemisphere::east});

	EXPECT_STREQ("$GPRMA,,,,12345.9333,E,,,,,,*35", nmea::to_string(rma).c_str());
}

TEST_F(test_nmea_rma, set_lon_west)
{
	nmea::rma rma;
	rma.set_lon(geo::longitude{123, 45, 56, geo::longitude::hemisphere::west});

	EXPECT_STREQ("$GPRMA,,,,12345.9333,W,,,,,,*27", nmea::to_string(rma).c_str());
}

TEST_F(test_nmea_rma, set_mag)
{
	nmea::rma rma;
	rma.set_magnetic_var(nmea::magnetic(12.5, nmea::direction::west));

	EXPECT_STREQ("$GPRMA,,,,,,,,,,12.5,W*2A", nmea::to_string(rma).c_str());
}

TEST_F(test_nmea_rma, get_mag)
{
	auto s = nmea::make_sentence("$GPRMA,,,,,,,,,,12.5,E*38");
	ASSERT_NE(nullptr, s);

	auto rma = nmea::sentence_cast<nmea::rma>(s);
	ASSERT_NE(nullptr, rma);

	auto magn = rma->get_magnetic_var();
	ASSERT_TRUE(magn.has_value());

	EXPECT_NEAR(12.5, magn->angle(), 1e-8);
	EXPECT_EQ(nmea::direction::east, magn->hemisphere());
}
}
