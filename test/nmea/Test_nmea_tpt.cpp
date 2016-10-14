#include <gtest/gtest.h>
#include <marnav/nmea/tpt.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_tpt : public ::testing::Test
{
};

TEST_F(Test_nmea_tpt, contruction)
{
	EXPECT_NO_THROW(nmea::tpt tpt);
}

TEST_F(Test_nmea_tpt, properties)
{
	nmea_sentence_traits<nmea::tpt>();
}

TEST_F(Test_nmea_tpt, parse)
{
	auto s = nmea::make_sentence("$GPTPT,1.0,M,2.0,P,3.0,M*39");
	ASSERT_NE(nullptr, s);

	auto tpt = nmea::sentence_cast<nmea::tpt>(s);
	ASSERT_NE(nullptr, tpt);
}

TEST_F(Test_nmea_tpt, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::tpt>(nmea::talker_id::none, {5, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::tpt>(nmea::talker_id::none, {7, "@"}));
}

TEST_F(Test_nmea_tpt, empty_to_string)
{
	nmea::tpt tpt;

	EXPECT_STREQ("$GPTPT,0,M,0,P,0,M*27", nmea::to_string(tpt).c_str());
}
}
