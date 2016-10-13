#include <gtest/gtest.h>
#include <marnav/nmea/rpm.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rpm : public ::testing::Test
{
};

TEST_F(Test_nmea_rpm, contruction) { EXPECT_NO_THROW(nmea::rpm rpm); }

TEST_F(Test_nmea_rpm, properties) { nmea_sentence_traits<nmea::rpm>(); }

TEST_F(Test_nmea_rpm, parse)
{
	auto s = nmea::make_sentence("$IIRPM,S,1,1800.0,5.0,A*7C");
	ASSERT_NE(nullptr, s);

	auto rpm = nmea::sentence_cast<nmea::rpm>(s);
	ASSERT_NE(nullptr, rpm);
}

TEST_F(Test_nmea_rpm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::rpm>(nmea::talker_id::none, {4, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::rpm>(nmea::talker_id::none, {6, "@"}));
}

TEST_F(Test_nmea_rpm, empty_to_string)
{
	nmea::rpm rpm;

	EXPECT_STREQ("$IIRPM,,,,,*63", nmea::to_string(rpm).c_str());
}

TEST_F(Test_nmea_rpm, set_source)
{
	nmea::rpm rpm;
	rpm.set_source(nmea::rpm::source_id::shaft, 1);

	EXPECT_STREQ("$IIRPM,S,1,,,*01", nmea::to_string(rpm).c_str());
}

TEST_F(Test_nmea_rpm, set_revolutions)
{
	nmea::rpm rpm;
	rpm.set_revolutions(1800.0);

	EXPECT_STREQ("$IIRPM,,,1800.0,,*74", nmea::to_string(rpm).c_str());
}

TEST_F(Test_nmea_rpm, set_propeller_pitch_positive)
{
	nmea::rpm rpm;
	rpm.set_propeller_pitch(10.0);

	EXPECT_STREQ("$IIRPM,,,,10.0,*7C", nmea::to_string(rpm).c_str());
}

TEST_F(Test_nmea_rpm, set_propeller_pitch_negative)
{
	nmea::rpm rpm;
	rpm.set_propeller_pitch(-10.0);

	EXPECT_STREQ("$IIRPM,,,,-10.0,*51", nmea::to_string(rpm).c_str());
}

TEST_F(Test_nmea_rpm, set_data_valid)
{
	nmea::rpm rpm;
	rpm.set_data_valid(nmea::status::ok);

	EXPECT_STREQ("$IIRPM,,,,,A*22", nmea::to_string(rpm).c_str());
}
}
