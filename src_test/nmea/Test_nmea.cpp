#include <gtest/gtest.h>
#include <nmea/nmea.hpp>

namespace
{
class Test_nmea : public ::testing::Test
{
};

TEST_F(Test_nmea, make_sentence_empty_string)
{
	EXPECT_ANY_THROW(nmea::make_sentence(""));
}

TEST_F(Test_nmea, make_sentence_no_start_token)
{
	EXPECT_ANY_THROW(nmea::make_sentence("1234567890"));
}

TEST_F(Test_nmea, make_sentence_to_short)
{
	EXPECT_ANY_THROW(nmea::make_sentence("12"));
}

TEST_F(Test_nmea, make_sentence_no_end_token)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPMTW,,1E"));
}

TEST_F(Test_nmea, make_sentence_invalid_checksum)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPMTW,,*1E"));
}

}
