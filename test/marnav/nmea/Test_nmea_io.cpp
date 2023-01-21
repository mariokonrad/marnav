#include <marnav/nmea/io.hpp>
#include <marnav/nmea/angle.hpp>
#include <gtest/gtest.h>
#include <locale>

namespace
{
using namespace marnav;

class test_nmea_io : public ::testing::Test
{
};

TEST_F(test_nmea_io, read_empty_latitude_string)
{
	geo::latitude lat{12.3};
	nmea::read("", lat);

	EXPECT_DOUBLE_EQ(geo::latitude{}, lat);
}

TEST_F(test_nmea_io, read_empty_longitude_string)
{
	geo::longitude lon{123.4};
	nmea::read("", lon);

	EXPECT_DOUBLE_EQ(geo::longitude{}, lon);
}

TEST_F(test_nmea_io, read_int32_positive_hex)
{
	const std::string s{"abc"};
	int32_t val = 0;

	read(s, val, nmea::data_format::hex);

	EXPECT_EQ(0xabc, val);
}

TEST_F(test_nmea_io, read_int32_negative_hex)
{
	const std::string s{"-abc"};
	int32_t val = 0;

	read(s, val, nmea::data_format::hex);

	EXPECT_EQ(-0xabc, val);
}

TEST_F(test_nmea_io, format_int32_hex)
{
	const int32_t val = 0xabcd;
	auto s = nmea::format(val, 1, nmea::data_format::hex);

	EXPECT_STREQ("abcd", s.c_str());
}

TEST_F(test_nmea_io, format_int32_none)
{
	const int32_t val = -10;
	auto s = nmea::format(val, 1, nmea::data_format::none);

	EXPECT_STREQ("-10", s.c_str());
}

TEST_F(test_nmea_io, format_uint32_none)
{
	const uint32_t val = 10;
	auto s = nmea::format(val, 1, nmea::data_format::none);

	EXPECT_STREQ("10", s.c_str());
}

TEST_F(test_nmea_io, read_double_classic_locale)
{
	auto old_locale = std::locale::global(std::locale::classic());

	double result = 0.0;
	marnav::nmea::read("3.14159", result);

	EXPECT_DOUBLE_EQ(3.14159, result);

	std::locale::global(old_locale);
}

TEST_F(test_nmea_io, read_double_french_locale)
{
	std::locale old_locale;

	try {
		old_locale = std::locale::global(std::locale("fr_FR.UTF-8"));
	} catch (...) {
		// locale not supported, disabling the test

		// locale needs to be supported by the system, example for ubuntu:
		// $ sudo locale-gen fr_FR.UTF-8

		return; // TODO: use GTEST_SKIP() after upgrade to googletest >= 1.10.0
	}

	double result = 0.0;
	marnav::nmea::read("3.14159", result);

	EXPECT_DOUBLE_EQ(3.14159, result);

	std::locale::global(old_locale);
}

TEST_F(test_nmea_io, format_double_classic_locale)
{
	auto old_locale = std::locale::global(std::locale::classic());

	EXPECT_STREQ("3.142", marnav::nmea::format(3.14159, 3).c_str());
	EXPECT_STREQ("3.1416", marnav::nmea::format(3.14159, 4).c_str());
	EXPECT_STREQ("3.14159", marnav::nmea::format(3.14159, 5).c_str());
	EXPECT_STREQ("33.66", marnav::nmea::format(33.66, 2).c_str());
	EXPECT_STREQ("33.660", marnav::nmea::format(33.66, 3).c_str());

	std::locale::global(old_locale);
}

TEST_F(test_nmea_io, format_double_french_locale)
{
	std::locale old_locale;

	try {
		old_locale = std::locale::global(std::locale("fr_FR.UTF-8"));
	} catch (...) {
		// locale not supported, disabling the test

		// locale needs to be supported by the system, example for ubuntu:
		// $ sudo locale-gen fr_FR.UTF-8

		return; // TODO: use GTEST_SKIP() after upgrade to googletest >= 1.10.0
	}

	EXPECT_STREQ("3.142", marnav::nmea::format(3.14159, 3).c_str());
	EXPECT_STREQ("3.1416", marnav::nmea::format(3.14159, 4).c_str());
	EXPECT_STREQ("3.14159", marnav::nmea::format(3.14159, 5).c_str());
	EXPECT_STREQ("33.66", marnav::nmea::format(33.66, 2).c_str());
	EXPECT_STREQ("33.660", marnav::nmea::format(33.66, 3).c_str());

	std::locale::global(old_locale);
	std::locale::global(old_locale);
}
}
