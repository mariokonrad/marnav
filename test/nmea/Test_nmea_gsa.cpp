#include <gtest/gtest.h>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_gsa : public ::testing::Test
{
};

TEST_F(Test_nmea_gsa, contruction) { EXPECT_NO_THROW(nmea::gsa gsa); }

TEST_F(Test_nmea_gsa, properties) { nmea_sentence_traits<nmea::gsa>(); }

TEST_F(Test_nmea_gsa, parse)
{
	auto s = nmea::make_sentence("$GPGSA,A,1,05,08,,,,17,,,,,,,,,*15");
	ASSERT_NE(nullptr, s);

	auto gsa = nmea::sentence_cast<nmea::gsa>(s);
	ASSERT_NE(nullptr, gsa);
}

TEST_F(Test_nmea_gsa, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::gsa::parse("@@", {16, "@"}));
	EXPECT_ANY_THROW(nmea::gsa::parse("@@", {18, "@"}));
}

TEST_F(Test_nmea_gsa, empty_to_string)
{
	nmea::gsa gsa;

	EXPECT_STREQ("$GPGSA,,,,,,,,,,,,,,,,,*6E", nmea::to_string(gsa).c_str());
}

TEST_F(Test_nmea_gsa, set_sel_mode)
{
	nmea::gsa gsa;
	gsa.set_sel_mode(marnav::nmea::selection_mode::automatic);

	EXPECT_STREQ("$GPGSA,A,,,,,,,,,,,,,,,,*2F", nmea::to_string(gsa).c_str());
}

TEST_F(Test_nmea_gsa, set_satellite_id_indexed)
{
	static const std::string DATA[12] = {
		"$GPGSA,,,01,,,,,,,,,,,,,,*6F", "$GPGSA,,,,01,,,,,,,,,,,,,*6F",
		"$GPGSA,,,,,01,,,,,,,,,,,,*6F", "$GPGSA,,,,,,01,,,,,,,,,,,*6F",
		"$GPGSA,,,,,,,01,,,,,,,,,,*6F", "$GPGSA,,,,,,,,01,,,,,,,,,*6F",
		"$GPGSA,,,,,,,,,01,,,,,,,,*6F", "$GPGSA,,,,,,,,,,01,,,,,,,*6F",
		"$GPGSA,,,,,,,,,,,01,,,,,,*6F", "$GPGSA,,,,,,,,,,,,01,,,,,*6F",
		"$GPGSA,,,,,,,,,,,,,01,,,,*6F", "$GPGSA,,,,,,,,,,,,,,01,,,*6F",
	};

	for (size_t i = 0; i < sizeof(DATA) / sizeof(DATA[0]); ++i) {
		nmea::gsa gsa;
		gsa.set_satellite_id(i + 1, 1);
		EXPECT_STREQ(DATA[i].c_str(), nmea::to_string(gsa).c_str());
	}
}

TEST_F(Test_nmea_gsa, set_satellite_id_indexed_invalid_index)
{
	nmea::gsa gsa;

	EXPECT_ANY_THROW(gsa.set_satellite_id(0, 1));
	EXPECT_ANY_THROW(gsa.set_satellite_id(13, 1));
	EXPECT_ANY_THROW(gsa.set_satellite_id(99, 1));
}

TEST_F(Test_nmea_gsa, get_satellite_id_invalid_index)
{
	nmea::gsa gsa;

	EXPECT_ANY_THROW(gsa.get_satellite_id(0));
	EXPECT_ANY_THROW(gsa.get_satellite_id(13));
	EXPECT_ANY_THROW(gsa.get_satellite_id(99));
}

TEST_F(Test_nmea_gsa, get_satellite_id)
{
	auto s = nmea::make_sentence("$GPGSA,A,1,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25*1F");
	ASSERT_NE(nullptr, s);

	auto gsa = nmea::sentence_cast<nmea::gsa>(s);
	ASSERT_NE(nullptr, gsa);

	uint32_t id = 11;
	for (int index = 1; index <= 12; ++index, ++id) {
		EXPECT_EQ(id, *gsa->get_satellite_id(index));
	}
}
}
