#include <gtest/gtest.h>
#include <nmea/vhw.hpp>
#include <nmea/nmea.hpp>

namespace
{

class Test_vhw : public ::testing::Test
{
};

TEST_F(Test_vhw, contruction)
{
	nmea::vhw vhw;
}

TEST_F(Test_vhw, size)
{
	EXPECT_EQ(96u, sizeof(nmea::vhw));
}

TEST_F(Test_vhw, parse)
{
	auto s = nmea::make_sentence("$IIVHW,,T,211.0,M,0.00,N,0.00,K*79");
	ASSERT_NE(nullptr, s);

	auto vhw = nmea::sentence_cast<nmea::vhw>(s);
	ASSERT_NE(nullptr, vhw);

	auto heading = vhw->get_heading();
	EXPECT_TRUE(heading.available());
	EXPECT_EQ(211.0, heading.value());
}

TEST_F(Test_vhw, empty_to_string)
{
	nmea::vhw vhw;

	EXPECT_STREQ("$IIVHW,,T,,,,,,*1D", nmea::to_string(vhw).c_str());
}

TEST_F(Test_vhw, set_temperature_to_string)
{
	nmea::vhw vhw;
	vhw.set_heading(45.8);

	EXPECT_STREQ("$IIVHW,,T,45.8,M,,,,*47", nmea::to_string(vhw).c_str());
}

}

