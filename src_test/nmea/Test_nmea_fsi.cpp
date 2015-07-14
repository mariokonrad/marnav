#include <gtest/gtest.h>
#include <marnav/nmea/fsi.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_fsi : public ::testing::Test
{
};

TEST_F(Test_nmea_fsi, contruction)
{
	nmea::fsi fsi;
}

TEST_F(Test_nmea_fsi, size)
{
	EXPECT_EQ(48u, sizeof(nmea::fsi));
}

TEST_F(Test_nmea_fsi, parse)
{
	auto s = nmea::make_sentence("$GPFSI,156000,156025,,*4C");
	ASSERT_NE(nullptr, s);

	auto fsi = nmea::sentence_cast<nmea::fsi>(s);
	ASSERT_NE(nullptr, fsi);
}

TEST_F(Test_nmea_fsi, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::fsi::parse("@@", {3, "@"}));
	EXPECT_ANY_THROW(nmea::fsi::parse("@@", {5, "@"}));
}

TEST_F(Test_nmea_fsi, empty_to_string)
{
	nmea::fsi fsi;

	EXPECT_STREQ("$GPFSI,,,,*4B", nmea::to_string(fsi).c_str());
}

}

