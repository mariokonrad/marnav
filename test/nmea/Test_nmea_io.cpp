#include <gtest/gtest.h>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/angle.hpp>

namespace
{

using namespace marnav;

class Test_nmea_io : public ::testing::Test
{
};

TEST_F(Test_nmea_io, read_empty_latitude_string)
{
	geo::latitude lat{12.3};
	nmea::read("", lat);

	EXPECT_EQ(geo::latitude{}, lat);
}

TEST_F(Test_nmea_io, read_empty_longitude_string)
{
	geo::longitude lon{123.4};
	nmea::read("", lon);

	EXPECT_EQ(geo::longitude{}, lon);
}

TEST_F(Test_nmea_io, read_int32_positive_hex)
{
	const std::string s{"abc"};
	int32_t val = 0;

	read(s, val, nmea::data_format::hex);

	EXPECT_EQ(0xabc, val);
}

TEST_F(Test_nmea_io, read_int32_negative_hex)
{
	const std::string s{"-abc"};
	int32_t val = 0;

	read(s, val, nmea::data_format::hex);

	EXPECT_EQ(-0xabc, val);
}

TEST_F(Test_nmea_io, format_int32_hex)
{
	const int32_t val = 0xabcd;
	auto s = nmea::format(val, 1, nmea::data_format::hex);

	EXPECT_STREQ("abcd", s.c_str());
}

TEST_F(Test_nmea_io, format_int32_none)
{
	const int32_t val = -10;
	auto s = nmea::format(val, 1, nmea::data_format::none);

	EXPECT_STREQ("-10", s.c_str());
}

TEST_F(Test_nmea_io, format_uint32_none)
{
	const uint32_t val = 10;
	auto s = nmea::format(val, 1, nmea::data_format::none);

	EXPECT_STREQ("10", s.c_str());
}
}
