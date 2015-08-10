#include <gtest/gtest.h>
#include <marnav/nmea/ttm.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_ttm : public ::testing::Test
{
};

TEST_F(Test_nmea_ttm, contruction) { nmea::ttm ttm; }

TEST_F(Test_nmea_ttm, parse)
{
	auto s = nmea::make_sentence("$GPTTM,,,,,,,,,,,,,*76");
	ASSERT_NE(nullptr, s);

	auto ttm = nmea::sentence_cast<nmea::ttm>(s);
	ASSERT_NE(nullptr, ttm);
}

TEST_F(Test_nmea_ttm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::ttm::parse("@@", {12, "@"}));
	EXPECT_ANY_THROW(nmea::ttm::parse("@@", {14, "@"}));
}

TEST_F(Test_nmea_ttm, empty_to_string)
{
	nmea::ttm ttm;

	EXPECT_STREQ("$GPTTM,,,,,,,,,,,,,*76", nmea::to_string(ttm).c_str());
}
}
