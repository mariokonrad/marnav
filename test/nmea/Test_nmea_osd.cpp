#include <gtest/gtest.h>
#include <marnav/nmea/osd.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_osd : public ::testing::Test
{
};

TEST_F(Test_nmea_osd, contruction) { EXPECT_NO_THROW(nmea::osd osd); }

TEST_F(Test_nmea_osd, parse)
{
	auto s = nmea::make_sentence("$IIOSD,123.4,A,,,,,,,*1F");
	ASSERT_NE(nullptr, s);

	auto osd = nmea::sentence_cast<nmea::osd>(s);
	ASSERT_NE(nullptr, osd);
}

TEST_F(Test_nmea_osd, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::osd::parse("@@", {8, "@"}));
	EXPECT_ANY_THROW(nmea::osd::parse("@@", {10, "@"}));
}

TEST_F(Test_nmea_osd, empty_to_string)
{
	nmea::osd osd;

	EXPECT_STREQ("$IIOSD,,,,,,,,,*74", nmea::to_string(osd).c_str());
}

TEST_F(Test_nmea_osd, set_heading)
{
	nmea::osd osd;
	osd.set_heading(123.4);

	EXPECT_STREQ("$IIOSD,123.4,,,,,,,,*5E", nmea::to_string(osd).c_str());
}

TEST_F(Test_nmea_osd, set_data_valid)
{
	nmea::osd osd;
	osd.set_data_valid(nmea::status::ok);

	EXPECT_STREQ("$IIOSD,,A,,,,,,,*35", nmea::to_string(osd).c_str());
}

TEST_F(Test_nmea_osd, set_course)
{
	nmea::osd osd;
	osd.set_course(123.4);

	EXPECT_STREQ("$IIOSD,,,123.4,T,,,,,*0A", nmea::to_string(osd).c_str());
}

TEST_F(Test_nmea_osd, set_speed)
{
	nmea::osd osd;
	osd.set_speed(5.4, nmea::unit::velocity::knot);

	EXPECT_STREQ("$IIOSD,,,,,5.4,N,,,*15", nmea::to_string(osd).c_str());
}

TEST_F(Test_nmea_osd, set_drift)
{
	nmea::osd osd;
	osd.set_drift(1.2, nmea::unit::velocity::knot);

	EXPECT_STREQ("$IIOSD,,,,,,,,1.2,N*17", nmea::to_string(osd).c_str());
}
}
