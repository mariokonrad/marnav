#include <gtest/gtest.h>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_mwv : public ::testing::Test
{
};

TEST_F(Test_nmea_mwv, contruction) { nmea::mwv mwv; }

TEST_F(Test_nmea_mwv, size) { EXPECT_EQ(72u, sizeof(nmea::mwv)); }

TEST_F(Test_nmea_mwv, parse)
{
	auto s = nmea::make_sentence("$IIMWV,084.0,R,10.4,N,A*04");
	ASSERT_NE(nullptr, s);

	auto mwv = nmea::sentence_cast<nmea::mwv>(s);
	ASSERT_NE(nullptr, mwv);

	auto angle = mwv->get_angle();
	EXPECT_TRUE(angle.available());
	EXPECT_EQ(84.0, angle.value());

	auto speed = mwv->get_speed();
	EXPECT_TRUE(speed.available());
	EXPECT_EQ(10.4, speed.value());
}

TEST_F(Test_nmea_mwv, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::mwv::parse("@@", {4, "@"}));
	EXPECT_ANY_THROW(nmea::mwv::parse("@@", {6, "@"}));
}

TEST_F(Test_nmea_mwv, empty_to_string)
{
	nmea::mwv mwv;

	EXPECT_STREQ("$IIMWV,,,,,*60", nmea::to_string(mwv).c_str());
}

TEST_F(Test_nmea_mwv, set_angle)
{
	nmea::mwv mwv;
	mwv.set_angle(12.5, nmea::side::RIGHT);

	EXPECT_STREQ("$IIMWV,12.5,R,,,*2A", nmea::to_string(mwv).c_str());
}

TEST_F(Test_nmea_mwv, set_speed)
{
	nmea::mwv mwv;
	mwv.set_speed(22.5, nmea::unit::KNOT);

	EXPECT_STREQ("$IIMWV,,,22.5,N,*35", nmea::to_string(mwv).c_str());
}
}

