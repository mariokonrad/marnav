#include <gtest/gtest.h>
#include <nmea/sentence.hpp>
#include <nmea/mtw.hpp>
#include <nmea/rmc.hpp>

namespace
{
class Test_nmea_sentence : public ::testing::Test
{
};

TEST_F(Test_nmea_sentence, sentence_is_null)
{
	std::unique_ptr<nmea::sentence> p;
	auto rc = nmea::sentence_cast<nmea::mtw>(p);

	EXPECT_EQ(nullptr, rc);
}

TEST_F(Test_nmea_sentence, sentence_wrong_id)
{
	std::unique_ptr<nmea::sentence> p(new nmea::rmc);
	auto rc = nmea::sentence_cast<nmea::mtw>(p);

	EXPECT_EQ(nullptr, rc);
}

}
