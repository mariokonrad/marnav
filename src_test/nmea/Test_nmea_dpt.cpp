#include <gtest/gtest.h>
#include <nmea/dpt.hpp>
#include <nmea/nmea.hpp>

namespace
{

class Test_nmea_dpt : public ::testing::Test
{
};

TEST_F(Test_nmea_dpt, contruction)
{
	nmea::dpt dpt;
}

TEST_F(Test_nmea_dpt, size)
{
	EXPECT_EQ(56u, sizeof(nmea::dpt));
}

TEST_F(Test_nmea_dpt, parse)
{
	auto s = nmea::make_sentence("$IIDPT,9.3,1.0*4B");
	ASSERT_NE(nullptr, s);

	auto dpt = nmea::sentence_cast<nmea::dpt>(s);
	ASSERT_NE(nullptr, dpt);
}

TEST_F(Test_nmea_dpt, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::dpt::parse("@@", {1, "@"}));
	EXPECT_ANY_THROW(nmea::dpt::parse("@@", {3, "@"}));
}

TEST_F(Test_nmea_dpt, empty_to_string)
{
	nmea::dpt dpt;

	EXPECT_STREQ("$IIDPT,,*40", nmea::to_string(dpt).c_str());
}

TEST_F(Test_nmea_dpt, set_depth_feet)
{
	nmea::dpt dpt;
	dpt.set_depth_meter(12.5);

	EXPECT_STREQ("$IIDPT,12.5,*58", nmea::to_string(dpt).c_str());
}

TEST_F(Test_nmea_dpt, set_transducer_offset)
{
	nmea::dpt dpt;
	dpt.set_transducer_offset(12.5);

	EXPECT_STREQ("$IIDPT,,12.5*58", nmea::to_string(dpt).c_str());
}

}

