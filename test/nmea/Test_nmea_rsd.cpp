#include <gtest/gtest.h>
#include <marnav/nmea/rsd.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_rsd : public ::testing::Test
{
};

TEST_F(Test_nmea_rsd, contruction) { EXPECT_NO_THROW(nmea::rsd rsd); }

TEST_F(Test_nmea_rsd, parse)
{
	auto s = nmea::make_sentence("$IIRSD,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,A,A*47");
	ASSERT_NE(nullptr, s);

	auto rsd = nmea::sentence_cast<nmea::rsd>(s);
	ASSERT_NE(nullptr, rsd);
}

TEST_F(Test_nmea_rsd, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::rsd::parse("@@", {12, "@"}));
	EXPECT_ANY_THROW(nmea::rsd::parse("@@", {14, "@"}));
}

TEST_F(Test_nmea_rsd, empty_to_string)
{
	nmea::rsd rsd;

	EXPECT_STREQ("$IIRSD,0,0,0,0,0,0,0,0,0,0,0,V,V*59",
		nmea::to_string(rsd).c_str());
}

}
