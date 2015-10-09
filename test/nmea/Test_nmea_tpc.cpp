#include <gtest/gtest.h>
#include <marnav/nmea/tpc.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_tpc : public ::testing::Test
{
};

TEST_F(Test_nmea_tpc, contruction) { EXPECT_NO_THROW(nmea::tpc tpc); }

TEST_F(Test_nmea_tpc, properties) { nmea_sentence_traits<nmea::tpc>(); }

TEST_F(Test_nmea_tpc, parse)
{
	auto s = nmea::make_sentence("$GPTPC,1.0,M,2.0,M,3.0,M*33");
	ASSERT_NE(nullptr, s);

	auto tpc = nmea::sentence_cast<nmea::tpc>(s);
	ASSERT_NE(nullptr, tpc);
}

TEST_F(Test_nmea_tpc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::tpc::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::tpc::parse("@@", {7, "@"}));
}

TEST_F(Test_nmea_tpc, empty_to_string)
{
	nmea::tpc tpc;

	EXPECT_STREQ("$GPTPC,0,M,0,M,0,M*2D", nmea::to_string(tpc).c_str());
}
}
