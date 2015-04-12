#include <gtest/gtest.h>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gsa : public ::testing::Test
{
};

TEST_F(Test_nmea_gsa, contruction) { nmea::gsa gsa; }

TEST_F(Test_nmea_gsa, size) { EXPECT_EQ(176u, sizeof(nmea::gsa)); }

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

TEST_F(Test_nmea_gsa, set_selection_mode)
{
	nmea::gsa gsa;
	gsa.set_selection_mode(marnav::nmea::selectionmode::AUTOMATIC);

	EXPECT_STREQ("$GPGSA,A,,,,,,,,,,,,,,,,*2F", nmea::to_string(gsa).c_str());
}

TEST_F(Test_nmea_gsa, set_satellite_id_01)
{
	nmea::gsa gsa;
	gsa.set_satellite_id_01(1);

	EXPECT_STREQ("$GPGSA,,,01,,,,,,,,,,,,,,*6F", nmea::to_string(gsa).c_str());
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

// TODO: implementation

TEST_F(Test_nmea_gsa, set_satellite_id_indexed_invalid_index)
{
	nmea::gsa gsa;
	gsa.set_satellite_id(99, 1);

	EXPECT_STREQ("$GPGSA,,,,,,,,,,,,,,,,,*6E", nmea::to_string(gsa).c_str());
}

}
