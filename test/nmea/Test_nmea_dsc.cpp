#include <gtest/gtest.h>
#include <marnav/nmea/dsc.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_dsc : public ::testing::Test
{
};

TEST_F(Test_nmea_dsc, contruction)
{
	EXPECT_NO_THROW(nmea::dsc dsc);
}

TEST_F(Test_nmea_dsc, properties)
{
	nmea_sentence_traits<nmea::dsc>();
}

TEST_F(Test_nmea_dsc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::dsc>(nmea::talker_id::none, {10, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::dsc>(nmea::talker_id::none, {12, "@"}));
}

TEST_F(Test_nmea_dsc, parse)
{
	static const std::vector<std::string> TESTS
		= {"$CDDSC,20,3380210040,00,21,26,1394807410,2231,,,B,E*75",
			"$CDDSC,20,3380210040,00,21,26,1394807410,2242,,,B,E*71",
			"$CDDSC,20,3664251410,00,21,26,1335111802,0004,,,B,E*72",
			"$CDDSC,20,3380210040,00,21,26,1394807410,0021,,,B,E*74",
			"$CDDSC,20,3380210040,00,21,26,1394807410,0021,,,B,*31"};

	for (const auto & test : TESTS) {
		auto s = nmea::make_sentence(test);
		EXPECT_NE(nullptr, s);
		if (s) {
			auto dsc = nmea::sentence_cast<nmea::dsc>(s);
			EXPECT_NE(nullptr, dsc);
		}
	}
}

TEST_F(Test_nmea_dsc, get_fmt_spec)
{
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,02,3380210040,00,21,26,1394807410,2231,,,B,E*75"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::format_specifier::geographical_area, s->get_fmt_spec());
	}
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,12,3380210040,00,21,26,1394807410,2231,,,B,E*74"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::format_specifier::distress, s->get_fmt_spec());
	}
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,16,3380210040,00,21,26,1394807410,2231,,,B,E*70"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::format_specifier::all_ships, s->get_fmt_spec());
	}
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,20,3380210040,00,21,26,1394807410,2231,,,B,E*75"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::format_specifier::individual_station, s->get_fmt_spec());
	}
}

TEST_F(Test_nmea_dsc, get_cat)
{
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,02,3380210040,00,21,26,1394807410,2231,,,B,E*75"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::category::routine, s->get_cat());
	}
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,02,3380210040,08,21,26,1394807410,2231,,,B,E*7D"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::category::safety, s->get_cat());
	}
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,02,3380210040,10,21,26,1394807410,2231,,,B,E*74"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::category::urgency, s->get_cat());
	}
	{
		auto s = nmea::sentence_cast<nmea::dsc>(
			nmea::make_sentence("$CDDSC,02,3380210040,12,21,26,1394807410,2231,,,B,E*76"));
		ASSERT_NE(nullptr, s);
		EXPECT_EQ(nmea::dsc::category::distress, s->get_cat());
	}
}

TEST_F(Test_nmea_dsc, get_mmsi)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,3380210040,00,21,26,1394807410,2231,,,B,E*75"));
	ASSERT_NE(nullptr, s);
	EXPECT_EQ(utils::mmsi{338021004}, s->get_mmsi());
}

TEST_F(Test_nmea_dsc, get_geographical_area_SE)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,2380210102,00,21,26,1394807410,2231,,,B,E*73"));
	ASSERT_NE(nullptr, s);
	const geo::region r = s->get_geographical_area();
	EXPECT_EQ((geo::latitude{38, 0, 0, geo::latitude::hemisphere::south}), r.top());
	EXPECT_EQ((geo::longitude{21, 0, 0, geo::longitude::hemisphere::east}), r.left());
	EXPECT_EQ((geo::latitude{39, 0, 0, geo::latitude::hemisphere::south}), r.bottom());
	EXPECT_EQ((geo::longitude{23, 0, 0, geo::longitude::hemisphere::east}), r.right());
}

TEST_F(Test_nmea_dsc, get_geographical_area_SW)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,3380210102,00,21,26,1394807410,2231,,,B,E*72"));
	ASSERT_NE(nullptr, s);
	const geo::region r = s->get_geographical_area();
	EXPECT_EQ((geo::latitude{38, 0, 0, geo::latitude::hemisphere::south}), r.top());
	EXPECT_EQ((geo::longitude{21, 0, 0, geo::longitude::hemisphere::west}), r.left());
	EXPECT_EQ((geo::latitude{39, 0, 0, geo::latitude::hemisphere::south}), r.bottom());
	EXPECT_EQ((geo::longitude{19, 0, 0, geo::longitude::hemisphere::west}), r.right());
}

TEST_F(Test_nmea_dsc, get_ack_B)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,3380210102,00,21,26,1394807410,2231,,,B,E*72"));
	ASSERT_NE(nullptr, s);
	EXPECT_EQ(nmea::dsc::acknowledgement::B, s->get_ack());
}

TEST_F(Test_nmea_dsc, get_ack_R)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,3380210102,00,21,26,1394807410,2231,,,R,E*62"));
	ASSERT_NE(nullptr, s);
	EXPECT_EQ(nmea::dsc::acknowledgement::R, s->get_ack());
}

TEST_F(Test_nmea_dsc, get_ack_end_of_sequence)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,3380210102,00,21,26,1394807410,2231,,,S,E*63"));
	ASSERT_NE(nullptr, s);
	EXPECT_EQ(nmea::dsc::acknowledgement::end_of_sequence, s->get_ack());
}

TEST_F(Test_nmea_dsc, get_extension)
{
	auto s = nmea::sentence_cast<nmea::dsc>(
		nmea::make_sentence("$CDDSC,02,3380210102,00,21,26,1394807410,2231,,,B,E*72"));
	ASSERT_NE(nullptr, s);
	EXPECT_EQ(nmea::dsc::extension_indicator::extension_follows, s->get_extension());
}

TEST_F(Test_nmea_dsc, empty_to_string)
{
	nmea::dsc dsc;
	EXPECT_STREQ("$CDDSC,12,0000000000,12,,,,,,,S,*2C", nmea::to_string(dsc).c_str());
}
}
