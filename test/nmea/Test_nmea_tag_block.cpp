#include <gtest/gtest.h>
#include <marnav/nmea/tag_block.hpp>

namespace
{
using namespace marnav;

class Test_nmea_tag_block : public ::testing::Test
{
};

TEST_F(Test_nmea_tag_block, default_construction)
{
	nmea::tag_block b;

	EXPECT_EQ(0u, b.get_unix_time());
	EXPECT_EQ(0u, b.get_line_count());
	EXPECT_EQ(0u, b.get_relative_time());
	EXPECT_EQ(0u, b.get_group().number);
	EXPECT_EQ(0u, b.get_group().total_number);
	EXPECT_EQ(0u, b.get_group().id);
	EXPECT_TRUE(b.get_destination().empty());
	EXPECT_TRUE(b.get_source().empty());
	EXPECT_TRUE(b.get_text().empty());
}

TEST_F(Test_nmea_tag_block, empty_string)
{
	EXPECT_ANY_THROW(nmea::make_tag_block(""));
}

TEST_F(Test_nmea_tag_block, checksum_correct)
{
	EXPECT_NO_THROW(nmea::make_tag_block("g:1-2-73874,n:157036,s:r003669945,c:1241544035*4A"));
}

TEST_F(Test_nmea_tag_block, invalid_checksum)
{
	EXPECT_ANY_THROW(nmea::make_tag_block("g:1-2-73874,n:157036,s:r003669945,c:1241544035*40"));
}

TEST_F(Test_nmea_tag_block, parse)
{
	const auto b = nmea::make_tag_block("g:1-2-73874,n:157036,s:r003669945,c:1241544035*4A");

	EXPECT_EQ(1241544035, b.get_unix_time());
	EXPECT_TRUE(b.get_destination().empty());
	EXPECT_EQ(1, b.get_group().number);
	EXPECT_EQ(2, b.get_group().total_number);
	EXPECT_EQ(73874, b.get_group().id);
	EXPECT_EQ(157036, b.get_line_count());
	EXPECT_EQ(0, b.get_relative_time());
	EXPECT_STREQ("r003669945", b.get_source().c_str());
	EXPECT_TRUE(b.get_text().empty());
}

TEST_F(Test_nmea_tag_block, parse_invalid_field)
{
	EXPECT_ANY_THROW(nmea::make_tag_block("x:1-2-73874,n:157036,s:r003669945,c:1241544035*4A"));
}

TEST_F(Test_nmea_tag_block, default_to_string)
{
	nmea::tag_block b;

	const auto s = to_string(b);

	EXPECT_TRUE(s.empty());
}

TEST_F(Test_nmea_tag_block, single_data_to_string)
{
	{
		nmea::tag_block b;
		b.set_unix_time(1);
		EXPECT_STREQ("c:1", to_string(b).c_str());
	}
	{
		nmea::tag_block b;
		b.set_line_count(1);
		EXPECT_STREQ("n:1", to_string(b).c_str());
	}
	{
		nmea::tag_block b;
		b.set_relative_time(1);
		EXPECT_STREQ("r:1", to_string(b).c_str());
	}
	{
		nmea::tag_block b;
		b.set_destination("269104520");
		EXPECT_STREQ("d:269104520", to_string(b).c_str());
	}
	{
		nmea::tag_block b;
		b.set_source("269104520");
		EXPECT_STREQ("s:269104520", to_string(b).c_str());
	}
	{
		nmea::tag_block b;
		b.set_text("269104520");
		EXPECT_STREQ("t:269104520", to_string(b).c_str());
	}
	{
		nmea::tag_block b;
		b.set_group({1, 2, 3});
		EXPECT_STREQ("g:1-2-3", to_string(b).c_str());
	}
}

TEST_F(Test_nmea_tag_block, multiple_data_to_string)
{
	nmea::tag_block b;
	b.set_unix_time(1);
	b.set_line_count(2);
	b.set_relative_time(3);
	EXPECT_STREQ("n:2,r:3,c:1", to_string(b).c_str());
}
}
