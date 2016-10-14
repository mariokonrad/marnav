#include <gtest/gtest.h>
#include <marnav/nmea/tds.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_tds : public ::testing::Test
{
};

TEST_F(Test_nmea_tds, contruction)
{
	EXPECT_NO_THROW(nmea::tds tds);
}

TEST_F(Test_nmea_tds, properties)
{
	nmea_sentence_traits<nmea::tds>();
}

TEST_F(Test_nmea_tds, parse)
{
	auto s = nmea::make_sentence("$GPTDS,12.3,M*07");
	ASSERT_NE(nullptr, s);

	auto tds = nmea::sentence_cast<nmea::tds>(s);
	ASSERT_NE(nullptr, tds);
}

TEST_F(Test_nmea_tds, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::tds>(nmea::talker_id::none, {1, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::tds>(nmea::talker_id::none, {3, "@"}));
}

TEST_F(Test_nmea_tds, empty_to_string)
{
	nmea::tds tds;

	EXPECT_STREQ("$GPTDS,0,M*29", nmea::to_string(tds).c_str());
}
}
