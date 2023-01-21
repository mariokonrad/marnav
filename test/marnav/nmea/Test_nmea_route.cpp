#include <marnav/nmea/route.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_route : public ::testing::Test
{
};

TEST_F(test_nmea_route, default_construction)
{
	nmea::route wp;

	EXPECT_EQ(0u, wp.size());
	EXPECT_TRUE(wp.empty());
	EXPECT_STREQ("", wp.c_str());
}

TEST_F(test_nmea_route, normal_construction)
{
	nmea::route wp{"abc"};

	EXPECT_STREQ("abc", wp.get().c_str());
}

TEST_F(test_nmea_route, construction_too_large_string)
{
	EXPECT_ANY_THROW(nmea::route{"123456789"});
}

TEST_F(test_nmea_route, size)
{
	nmea::route wp{"ABC"};

	EXPECT_EQ(3u, wp.size());
}

TEST_F(test_nmea_route, c_str)
{
	nmea::route wp{"ABC"};

	EXPECT_STREQ("ABC", wp.c_str());
}
}
