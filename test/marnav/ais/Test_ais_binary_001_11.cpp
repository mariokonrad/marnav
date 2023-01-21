#include <marnav/ais/binary_001_11.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav::ais;

class test_ais_binary_001_11 : public ::testing::Test
{
};

TEST_F(test_ais_binary_001_11, default_values)
{
	binary_001_11 b;
	raw r;

	b.write_to(r);

	EXPECT_EQ(352 - 56, r.size());
}

TEST_F(test_ais_binary_001_11, day)
{
	binary_001_11 b;

	EXPECT_TRUE(!b.get_day());
	b.set_day(0);
	EXPECT_TRUE(!!b.get_day());
	b.set_day(32);
	EXPECT_TRUE(!b.get_day());
}

TEST_F(test_ais_binary_001_11, hour)
{
	binary_001_11 b;

	EXPECT_TRUE(!b.get_hour());
	b.set_hour(0);
	EXPECT_TRUE(!!b.get_hour());
	b.set_hour(24);
	EXPECT_TRUE(!b.get_hour());
}

TEST_F(test_ais_binary_001_11, minute)
{
	binary_001_11 b;

	EXPECT_TRUE(!b.get_minute());
	b.set_minute(0);
	EXPECT_TRUE(!!b.get_minute());
	b.set_minute(60);
	EXPECT_TRUE(!b.get_minute());
}
}
