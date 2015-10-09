#include <gtest/gtest.h>
#include <marnav/nmea/gst.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_gst : public ::testing::Test
{
};

TEST_F(Test_nmea_gst, contruction) { EXPECT_NO_THROW(nmea::gst gst); }

TEST_F(Test_nmea_gst, properties) { nmea_sentence_traits<nmea::gst>(); }

TEST_F(Test_nmea_gst, parse)
{
	auto s = nmea::make_sentence("$GPGST,123456.34,1.0,2.1,3.2,4.3,5.4,6.5,7.6*50");
	ASSERT_NE(nullptr, s);

	auto gst = nmea::sentence_cast<nmea::gst>(s);
	ASSERT_NE(nullptr, gst);
}

TEST_F(Test_nmea_gst, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::gst::parse("@@", {7, "@"}));
	EXPECT_ANY_THROW(nmea::gst::parse("@@", {9, "@"}));
}

TEST_F(Test_nmea_gst, empty_to_string)
{
	nmea::gst gst;

	EXPECT_STREQ("$GPGST,000000.00,0,0,0,0,0,0,0*49", nmea::to_string(gst).c_str());
}
}
