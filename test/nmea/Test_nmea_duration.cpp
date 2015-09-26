#include <gtest/gtest.h>
#include <marnav/nmea/time.hpp>
#include <sstream>

namespace
{

using namespace marnav;

class Test_nmea_duration : public ::testing::Test
{
};

TEST_F(Test_nmea_duration, explicit_construction)
{
	EXPECT_ANY_THROW((nmea::duration{100, 0, 0, 0}));
	EXPECT_ANY_THROW((nmea::duration{0, 60, 0, 0}));
	EXPECT_ANY_THROW((nmea::duration{0, 0, 60, 0}));
	EXPECT_ANY_THROW((nmea::duration{0, 0, 0, 1000}));
}

TEST_F(Test_nmea_duration, hour)
{
	nmea::duration t{1, 2, 3, 4};

	EXPECT_EQ(1u, t.hour());
}

TEST_F(Test_nmea_duration, minutes)
{
	nmea::duration t{1, 2, 3, 4};

	EXPECT_EQ(2u, t.minutes());
}

TEST_F(Test_nmea_duration, seconds)
{
	nmea::duration t{1, 2, 3, 4};

	EXPECT_EQ(3u, t.seconds());
}

TEST_F(Test_nmea_duration, milliseconds)
{
	nmea::duration t{1, 2, 3, 4};

	EXPECT_EQ(4u, t.milliseconds());
}

TEST_F(Test_nmea_duration, comparison_equal)
{
	nmea::duration t0{1, 2, 3, 4};
	nmea::duration t1{1, 2, 3, 4};

	EXPECT_TRUE(t0 == t1);
}

TEST_F(Test_nmea_duration, invalid_format_for_double)
{
	EXPECT_ANY_THROW(nmea::duration::parse("123.455.6"));
}

TEST_F(Test_nmea_duration, to_string)
{
	nmea::duration t{99, 2, 3, 4};

	using namespace marnav::nmea;
	const std::string s = to_string(t);

	EXPECT_STREQ("990203", s.c_str());
}

TEST_F(Test_nmea_duration, stream)
{
	nmea::duration t{99, 2, 3, 4};

	using namespace marnav::nmea;
	std::ostringstream os;
	os << t;

	EXPECT_STREQ("990203", os.str().c_str());
}
}
