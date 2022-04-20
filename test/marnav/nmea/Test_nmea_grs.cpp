#include <marnav/nmea/grs.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_nmea_grs : public ::testing::Test
{
};

TEST_F(Test_nmea_grs, contruction)
{
	EXPECT_NO_THROW(nmea::grs grs);
}

TEST_F(Test_nmea_grs, properties)
{
	nmea_sentence_traits<nmea::grs>();
}

TEST_F(Test_nmea_grs, parse)
{
	auto s = nmea::make_sentence("$GPGRS,024603.00,1,-1.8,-2.7,0.3,,,,,,,,,*6C");
	ASSERT_NE(nullptr, s);

	auto grs = nmea::sentence_cast<nmea::grs>(s);
	ASSERT_NE(nullptr, grs);
}

TEST_F(Test_nmea_grs, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::grs>(nmea::talker::none, {13, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::grs>(nmea::talker::none, {15, "@"}));
}

TEST_F(Test_nmea_grs, empty_to_string)
{
	nmea::grs grs;

	EXPECT_STREQ("$GPGRS,000000.00,0,0,0,0,,,,,,,,,*7F", nmea::to_string(grs).c_str());
}
}
