#include <gtest/gtest.h>
#include <marnav/nmea/split.hpp>

namespace
{
class Test_nmea_split : public ::testing::Test
{
};

TEST_F(Test_nmea_split, field_1_with_leading_start_token)
{
	const auto result = marnav::nmea::detail::parse_fields("$A");

	ASSERT_EQ(1u, result.size());
	EXPECT_STREQ("A", result[0].c_str());
}

TEST_F(Test_nmea_split, field_1_without_leading_start_token)
{
	const auto result = marnav::nmea::detail::parse_fields("A");

	ASSERT_EQ(1u, result.size());
	EXPECT_STREQ("", result[0].c_str());
}

TEST_F(Test_nmea_split, field_2_with_start_token)
{
	const auto result = marnav::nmea::detail::parse_fields("$A,B");

	ASSERT_EQ(2u, result.size());
	EXPECT_STREQ("A", result[0].c_str());
	EXPECT_STREQ("B", result[1].c_str());
}

TEST_F(Test_nmea_split, field_1_terminated)
{
	const auto result = marnav::nmea::detail::parse_fields("$A*xx");

	ASSERT_EQ(2u, result.size());
	EXPECT_STREQ("A", result[0].c_str());
	EXPECT_STREQ("xx", result[1].c_str());
}

TEST_F(Test_nmea_split, field_2_terminated)
{
	const auto result = marnav::nmea::detail::parse_fields("$A,B*xx");

	ASSERT_EQ(3u, result.size());
	EXPECT_STREQ("A", result[0].c_str());
	EXPECT_STREQ("B", result[1].c_str());
	EXPECT_STREQ("xx", result[2].c_str());
}

TEST_F(Test_nmea_split, field_2_oneempty_terminated)
{
	const auto result = marnav::nmea::detail::parse_fields("$A,*xx");

	ASSERT_EQ(3u, result.size());
	EXPECT_STREQ("A", result[0].c_str());
	EXPECT_STREQ("", result[1].c_str());
	EXPECT_STREQ("xx", result[2].c_str());
}

TEST_F(Test_nmea_split, field_10_all_empty_terminated)
{
	const auto result = marnav::nmea::detail::parse_fields("$,,,,,,,,,*xx");

	ASSERT_EQ(11u, result.size());
}

TEST_F(Test_nmea_split, field_10_terminated)
{
	const auto result = marnav::nmea::detail::parse_fields("$0,1,2,3,4,5,6,7,8,9*xx");

	ASSERT_EQ(11u, result.size());
	EXPECT_STREQ("0", result[0].c_str());
	EXPECT_STREQ("1", result[1].c_str());
	EXPECT_STREQ("2", result[2].c_str());
	EXPECT_STREQ("3", result[3].c_str());
	EXPECT_STREQ("4", result[4].c_str());
	EXPECT_STREQ("5", result[5].c_str());
	EXPECT_STREQ("6", result[6].c_str());
	EXPECT_STREQ("7", result[7].c_str());
	EXPECT_STREQ("8", result[8].c_str());
	EXPECT_STREQ("9", result[9].c_str());
	EXPECT_STREQ("xx", result[10].c_str());
}

TEST_F(Test_nmea_split, only_terminator)
{
	const auto result = marnav::nmea::detail::parse_fields("$*xx");

	ASSERT_EQ(2u, result.size());
	EXPECT_STREQ("", result[0].c_str());
	EXPECT_STREQ("xx", result[1].c_str());
}

TEST_F(Test_nmea_split, empty_string)
{
	const auto result = marnav::nmea::detail::parse_fields("");

	ASSERT_EQ(0u, result.size());
}
}
