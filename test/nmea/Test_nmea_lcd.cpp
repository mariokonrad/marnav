#include <gtest/gtest.h>
#include <marnav/nmea/lcd.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_lcd : public ::testing::Test
{
};

TEST_F(Test_nmea_lcd, contruction) { nmea::lcd lcd; }

TEST_F(Test_nmea_lcd, parse)
{
	auto s = nmea::make_sentence("$GPLCD,1,1,A,1,A,2,A,3,A,4,V,,*22");
	ASSERT_NE(nullptr, s);

	auto lcd = nmea::sentence_cast<nmea::lcd>(s);
	ASSERT_NE(nullptr, lcd);
}

TEST_F(Test_nmea_lcd, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::lcd::parse("@@", {12, "@"}));
	EXPECT_ANY_THROW(nmea::lcd::parse("@@", {14, "@"}));
}

TEST_F(Test_nmea_lcd, empty_to_string)
{
	nmea::lcd lcd;

	EXPECT_STREQ("$GPLCD,0,0,0,,,,,,,,,,*40", nmea::to_string(lcd).c_str());
}

TEST_F(Test_nmea_lcd, set_time_diff_invalid_index)
{
	nmea::lcd lcd;

	EXPECT_ANY_THROW(lcd.set_time_diff(-1, {0.0, nmea::status::OK}));
	EXPECT_ANY_THROW(lcd.set_time_diff(5, {0.0, nmea::status::OK}));
}

TEST_F(Test_nmea_lcd, get_time_diff_invalid_index)
{
	nmea::lcd lcd;

	EXPECT_ANY_THROW(lcd.get_time_diff(-1));
	EXPECT_ANY_THROW(lcd.get_time_diff(5));
}

}
