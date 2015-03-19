#include <gtest/gtest.h>
#include <nmea/vwr.hpp>
#include <nmea/nmea.hpp>

namespace
{

class Test_nmea_vwr : public ::testing::Test
{
};

TEST_F(Test_nmea_vwr, contruction)
{
	nmea::vwr vwr;
}

TEST_F(Test_nmea_vwr, size)
{
	EXPECT_EQ(120u, sizeof(nmea::vwr));
}

TEST_F(Test_nmea_vwr, parse)
{
	auto s = nmea::make_sentence("$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*4A");
	ASSERT_NE(nullptr, s);

	auto vwr = nmea::sentence_cast<nmea::vwr>(s);
	ASSERT_NE(nullptr, vwr);

	auto angle = vwr->get_angle();
	EXPECT_TRUE(angle.available());
	EXPECT_EQ(84.0, angle.value());

	auto side = vwr->get_side();
	EXPECT_TRUE(side.available());
	EXPECT_EQ(nmea::side::RIGHT, side.value());
}

TEST_F(Test_nmea_vwr, empty_to_string)
{
	nmea::vwr vwr;

	EXPECT_STREQ("$IIVWR,,,,,,,,*53", nmea::to_string(vwr).c_str());
}

TEST_F(Test_nmea_vwr, set_angle_to_string)
{
	nmea::vwr vwr;
	vwr.set_angle(22.5, nmea::side::LEFT);

	EXPECT_STREQ("$IIVWR,22.5,L,,,,,,*04", nmea::to_string(vwr).c_str());
}

}

