#include <marnav/nmea/waypoint.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_waypoint : public ::testing::Test
{
};

TEST_F(Test_nmea_waypoint, default_construction)
{
	nmea::waypoint wp;

	EXPECT_EQ(0u, wp.size());
	EXPECT_TRUE(wp.empty());
	EXPECT_STREQ("", wp.c_str());
}

TEST_F(Test_nmea_waypoint, normal_construction)
{
	nmea::waypoint wp{"abc"};

	EXPECT_STREQ("abc", wp.get().c_str());
}

TEST_F(Test_nmea_waypoint, construction_too_large_string)
{
	EXPECT_ANY_THROW(nmea::waypoint{"123456789"});
}

TEST_F(Test_nmea_waypoint, size)
{
	nmea::waypoint wp{"ABC"};

	EXPECT_EQ(3u, wp.size());
}

TEST_F(Test_nmea_waypoint, c_str)
{
	nmea::waypoint wp{"ABC"};

	EXPECT_STREQ("ABC", wp.c_str());
}
}
