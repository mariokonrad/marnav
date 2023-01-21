#include <marnav/nmea/ttm.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_ttm : public ::testing::Test
{
};

TEST_F(test_nmea_ttm, contruction)
{
	EXPECT_NO_THROW(nmea::ttm ttm);
}

TEST_F(test_nmea_ttm, properties)
{
	nmea_sentence_traits<nmea::ttm>();
}

TEST_F(test_nmea_ttm, parse)
{
	auto s = nmea::make_sentence("$GPTTM,,,,,,,,,,,,,*76");
	ASSERT_NE(nullptr, s);

	auto ttm = nmea::sentence_cast<nmea::ttm>(s);
	ASSERT_NE(nullptr, ttm);
}

TEST_F(test_nmea_ttm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::ttm>(nmea::talker::none, {12, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::ttm>(nmea::talker::none, {16, "@"}));
}

TEST_F(test_nmea_ttm, empty_to_string)
{
	nmea::ttm ttm;

	EXPECT_STREQ("$GPTTM,,,,,,,,,,,,,*76", nmea::to_string(ttm).c_str());
}
}
