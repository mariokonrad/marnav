#include <gtest/gtest.h>
#include <marnav/nmea/gbs.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gbs : public ::testing::Test
{
};

TEST_F(Test_nmea_gbs, contruction) { EXPECT_NO_THROW(nmea::gbs gbs); }

TEST_F(Test_nmea_gbs, parse)
{
	auto s = nmea::make_sentence("$GPGBS,123456.32,1.0,2.0,3.0,034,0.1,1.2,0.6*5A");
	ASSERT_NE(nullptr, s);

	auto gbs = nmea::sentence_cast<nmea::gbs>(s);
	ASSERT_NE(nullptr, gbs);
}

TEST_F(Test_nmea_gbs, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::gbs::parse("@@", {7, "@"}));
	EXPECT_ANY_THROW(nmea::gbs::parse("@@", {9, "@"}));
}

TEST_F(Test_nmea_gbs, empty_to_string)
{
	nmea::gbs gbs;

	EXPECT_STREQ("$GPGBS,000000.00,0,0,0,000,0,0,0*5F", nmea::to_string(gbs).c_str());
}

}
