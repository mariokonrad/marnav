#include <marnav/nmea/time.hpp>
#include <gtest/gtest.h>

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

TEST_F(Test_nmea_duration, chrono_construction)
{
	using namespace std::chrono;

	EXPECT_EQ(nmea::duration(1, 0, 0, 0), nmea::duration(hours(1)));
	EXPECT_EQ(nmea::duration(0, 1, 0, 0), nmea::duration(minutes(1)));
	EXPECT_EQ(nmea::duration(0, 0, 1, 0), nmea::duration(seconds(1)));
	EXPECT_EQ(nmea::duration(0, 0, 0, 1), nmea::duration(milliseconds(1)));

	EXPECT_EQ(nmea::duration(10, 0, 0, 0), nmea::duration(hours(10)));
	EXPECT_EQ(nmea::duration(99, 0, 0, 0), nmea::duration(hours(99)));

	EXPECT_EQ(nmea::duration(0, 10, 0, 0), nmea::duration(minutes(10)));
	EXPECT_EQ(nmea::duration(0, 59, 0, 0), nmea::duration(minutes(59)));
	EXPECT_EQ(nmea::duration(1, 0, 0, 0), nmea::duration(minutes(60)));
	EXPECT_EQ(nmea::duration(1, 15, 0, 0), nmea::duration(minutes(75)));

	EXPECT_EQ(nmea::duration(0, 0, 10, 0), nmea::duration(seconds(10)));
	EXPECT_EQ(nmea::duration(0, 0, 59, 0), nmea::duration(seconds(59)));
	EXPECT_EQ(nmea::duration(0, 1, 0, 0), nmea::duration(seconds(60)));
	EXPECT_EQ(nmea::duration(0, 1, 1, 0), nmea::duration(seconds(61)));
	EXPECT_EQ(nmea::duration(0, 2, 0, 0), nmea::duration(seconds(120)));
	EXPECT_EQ(nmea::duration(1, 0, 0, 0), nmea::duration(seconds(3600)));

	EXPECT_EQ(nmea::duration(0, 0, 0, 10), nmea::duration(milliseconds(10)));
	EXPECT_EQ(nmea::duration(0, 0, 0, 100), nmea::duration(milliseconds(100)));
	EXPECT_EQ(nmea::duration(0, 0, 0, 999), nmea::duration(milliseconds(999)));
	EXPECT_EQ(nmea::duration(0, 0, 1, 0), nmea::duration(milliseconds(1000)));
	EXPECT_EQ(nmea::duration(0, 1, 0, 0), nmea::duration(milliseconds(60000)));
	EXPECT_EQ(nmea::duration(1, 0, 0, 0), nmea::duration(milliseconds(60 * 60000)));
	EXPECT_EQ(nmea::duration(99, 0, 0, 999), nmea::duration(hours(99) + milliseconds(999)));
}

TEST_F(Test_nmea_duration, chrono_conversion)
{
	using namespace std::chrono;

	EXPECT_EQ(hours(1), nmea::duration(1, 0, 0, 0).chrono());
	EXPECT_EQ(minutes(1), nmea::duration(0, 1, 0, 0).chrono());
	EXPECT_EQ(seconds(1), nmea::duration(0, 0, 1, 0).chrono());
	EXPECT_EQ(milliseconds(1), nmea::duration(0, 0, 0, 1).chrono());
	EXPECT_EQ(hours(99) + milliseconds(999), nmea::duration(99, 0, 0, 999).chrono());
}

TEST_F(Test_nmea_duration, duration_cast)
{
	using namespace std::chrono;

	EXPECT_EQ(hours(1), duration_cast<hours>(nmea::duration(1, 0, 0, 0)));
	EXPECT_EQ(minutes(1), duration_cast<minutes>(nmea::duration(0, 1, 0, 0)));
	EXPECT_EQ(seconds(1), duration_cast<seconds>(nmea::duration(0, 0, 1, 0)));
	EXPECT_EQ(milliseconds(1), duration_cast<milliseconds>(nmea::duration(0, 0, 0, 1)));

	EXPECT_EQ(hours(99) + milliseconds(999),
		duration_cast<milliseconds>(nmea::duration(99, 0, 0, 999)));

	EXPECT_EQ(hours(99) + minutes(59) + seconds(59) + milliseconds(999),
		duration_cast<milliseconds>(nmea::duration(99, 59, 59, 999)));
}
}
