#include <marnav/nmea/mss.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_mss : public ::testing::Test
{
};

TEST_F(test_nmea_mss, contruction)
{
	EXPECT_NO_THROW(nmea::mss mss);
}

TEST_F(test_nmea_mss, properties)
{
	nmea_sentence_traits<nmea::mss>();
}

TEST_F(test_nmea_mss, parse)
{
	auto s = nmea::make_sentence("$GPMSS,12,34,123,456,1*44");
	ASSERT_NE(nullptr, s);

	auto mss = nmea::sentence_cast<nmea::mss>(s);
	ASSERT_NE(nullptr, mss);
}

TEST_F(test_nmea_mss, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mss>(nmea::talker::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mss>(nmea::talker::none, {6, "@"}));
}

TEST_F(test_nmea_mss, empty_to_string)
{
	nmea::mss mss;

	EXPECT_STREQ("$GPMSS,00,00,000,000,0*46", nmea::to_string(mss).c_str());
}
}
