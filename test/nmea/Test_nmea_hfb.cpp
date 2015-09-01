#include <gtest/gtest.h>
#include <marnav/nmea/hfb.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_hfb : public ::testing::Test
{
};

TEST_F(Test_nmea_hfb, contruction) { EXPECT_NO_THROW(nmea::hfb hfb); }

TEST_F(Test_nmea_hfb, parse)
{
	auto s = nmea::make_sentence("$GPHFB,1.0,M,2.0,M*58");
	ASSERT_NE(nullptr, s);

	auto hfb = nmea::sentence_cast<nmea::hfb>(s);
	ASSERT_NE(nullptr, hfb);
}

TEST_F(Test_nmea_hfb, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::hfb::parse("@@", {3, "@"}));
	EXPECT_ANY_THROW(nmea::hfb::parse("@@", {5, "@"}));
}

TEST_F(Test_nmea_hfb, empty_to_string)
{
	nmea::hfb hfb;

	EXPECT_STREQ("$GPHFB,0,M,0,M*5B", nmea::to_string(hfb).c_str());
}

}
