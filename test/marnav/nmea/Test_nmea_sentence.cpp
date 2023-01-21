#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/rmc.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_sentence : public ::testing::Test
{
};

TEST_F(test_nmea_sentence, sentence_is_null)
{
	std::unique_ptr<nmea::sentence> p;
	auto rc = nmea::sentence_cast<nmea::mtw>(p);

	EXPECT_EQ(nullptr, rc);
}

TEST_F(test_nmea_sentence, sentence_wrong_id)
{
	std::unique_ptr<nmea::sentence> p(new nmea::rmc);

	EXPECT_ANY_THROW(nmea::sentence_cast<nmea::mtw>(p));
}
}
