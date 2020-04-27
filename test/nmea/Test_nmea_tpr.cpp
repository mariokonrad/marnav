#include <gtest/gtest.h>
#include <marnav/nmea/tpr.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_tpr : public ::testing::Test
{
};

TEST_F(Test_nmea_tpr, contruction)
{
	EXPECT_NO_THROW(nmea::tpr tpr);
}

TEST_F(Test_nmea_tpr, properties)
{
	nmea_sentence_traits<nmea::tpr>();
}

TEST_F(Test_nmea_tpr, parse)
{
	auto s = nmea::make_sentence("$GPTPR,1.0,M,2.0,P,3.0,M*3F");
	ASSERT_NE(nullptr, s);

	auto tpr = nmea::sentence_cast<nmea::tpr>(s);
	ASSERT_NE(nullptr, tpr);
}

TEST_F(Test_nmea_tpr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::tpr>(nmea::talker::none, {5, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::tpr>(nmea::talker::none, {7, "@"}));
}

TEST_F(Test_nmea_tpr, empty_to_string)
{
	nmea::tpr tpr;

	EXPECT_STREQ("$GPTPR,0,M,0,P,0,M*21", nmea::to_string(tpr).c_str());
}
}
