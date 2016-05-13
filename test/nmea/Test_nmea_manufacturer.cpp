#include <gtest/gtest.h>
#include <marnav/nmea/manufacturer.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/pgrme.hpp>

namespace
{
using namespace marnav;

class Test_nmea_manufacturer : public ::testing::Test
{
};

TEST_F(Test_nmea_manufacturer, get_manufacturer_id)
{
	EXPECT_EQ(nmea::manufacturer_id::UNKNOWN, nmea::get_manufacturer_id("P"));
	EXPECT_EQ(nmea::manufacturer_id::UNKNOWN, nmea::get_manufacturer_id("Px"));
	EXPECT_EQ(nmea::manufacturer_id::NMEA, nmea::get_manufacturer_id("Pxx"));
	EXPECT_EQ(nmea::manufacturer_id::UNKNOWN, nmea::get_manufacturer_id("Pxxx"));
	EXPECT_EQ(nmea::manufacturer_id::UNKNOWN, nmea::get_manufacturer_id("Pxxx"));
	EXPECT_EQ(nmea::manufacturer_id::UNKNOWN, nmea::get_manufacturer_id("Pxxxxx"));
	EXPECT_EQ(nmea::manufacturer_id::NMEA, nmea::get_manufacturer_id("GPRMC"));
	EXPECT_EQ(nmea::manufacturer_id::GRM, nmea::get_manufacturer_id("PGRME"));
}

TEST_F(Test_nmea_manufacturer, get_manufacturer_tag_from_id)
{
	EXPECT_STREQ("", nmea::get_manufacturer_tag(nmea::manufacturer_id::NMEA).c_str());
	EXPECT_STREQ("", nmea::get_manufacturer_tag(nmea::manufacturer_id::UNKNOWN).c_str());
	EXPECT_STREQ("GRM", nmea::get_manufacturer_tag(nmea::manufacturer_id::GRM).c_str());
}

TEST_F(Test_nmea_manufacturer, get_manufacturer_name_from_id)
{
	EXPECT_STREQ("NMEA", nmea::get_manufacturer_name(nmea::manufacturer_id::NMEA).c_str());
	EXPECT_STREQ("UNKNOWN", nmea::get_manufacturer_name(nmea::manufacturer_id::UNKNOWN).c_str());
	EXPECT_STREQ("GARMIN CORPORATION", nmea::get_manufacturer_name(nmea::manufacturer_id::GRM).c_str());
}

TEST_F(Test_nmea_manufacturer, get_manufacturer_id_from_sentence)
{
	EXPECT_EQ(nmea::manufacturer_id::NMEA, nmea::get_manufacturer_id(nmea::rmc{}));
	EXPECT_EQ(nmea::manufacturer_id::GRM, nmea::get_manufacturer_id(nmea::pgrme{}));
}

TEST_F(Test_nmea_manufacturer, get_supported_manufacturer_id)
{
	const auto m = nmea::get_supported_manufacturer_id();

	EXPECT_EQ(541u, m.size());
}

TEST_F(Test_nmea_manufacturer, test_manufacturer_tags)
{
	for (const auto id : nmea::get_supported_manufacturer_id()) {
		EXPECT_FALSE(nmea::get_manufacturer_tag(id).empty());
	}
}

TEST_F(Test_nmea_manufacturer, test_manufacturer_names)
{
	for (const auto id : nmea::get_supported_manufacturer_id()) {
		EXPECT_FALSE(nmea::get_manufacturer_name(id).empty());
	}
}
}
