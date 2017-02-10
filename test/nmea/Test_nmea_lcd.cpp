#include <gtest/gtest.h>
#include <marnav/nmea/lcd.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_lcd : public ::testing::Test
{
};

TEST_F(Test_nmea_lcd, contruction)
{
	EXPECT_NO_THROW(nmea::lcd lcd);
}

TEST_F(Test_nmea_lcd, properties)
{
	nmea_sentence_traits<nmea::lcd>();
}

TEST_F(Test_nmea_lcd, parse)
{
	auto s = nmea::make_sentence("$GPLCD,1,001,000,001,000,002,000,003,000,004,000,,*44");
	ASSERT_NE(nullptr, s);

	auto lcd = nmea::sentence_cast<nmea::lcd>(s);
	ASSERT_NE(nullptr, lcd);
}

TEST_F(Test_nmea_lcd, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::lcd>(nmea::talker_id::none, {12, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::lcd>(nmea::talker_id::none, {14, "@"}));
}

TEST_F(Test_nmea_lcd, empty_to_string)
{
	nmea::lcd lcd;

	EXPECT_STREQ("$GPLCD,0,000,000,,,,,,,,,,*40", nmea::to_string(lcd).c_str());
}

TEST_F(Test_nmea_lcd, set_time_diff_invalid_index)
{
	nmea::lcd lcd;

	EXPECT_ANY_THROW(lcd.set_time_diff(-1, {0, 0}));
	EXPECT_ANY_THROW(lcd.set_time_diff(5, {0, 0}));
	EXPECT_ANY_THROW(lcd.set_time_diff(nmea::lcd::max_differences, {0, 0}));
}

TEST_F(Test_nmea_lcd, get_time_diff_invalid_index)
{
	nmea::lcd lcd;

	EXPECT_ANY_THROW(lcd.get_time_diff(-1));
	EXPECT_ANY_THROW(lcd.get_time_diff(5));
	EXPECT_ANY_THROW(lcd.get_time_diff(nmea::lcd::max_differences));
}
}
