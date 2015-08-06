#include <gtest/gtest.h>
#include <marnav/ais/message_21.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_21 : public ::testing::Test
{
};

TEST_F(Test_ais_message_21, parse)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("E000000000000000000000000000000000000000000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_21>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_21, encode_default_values)
{
	ais::message_21 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("E000000000000000000000000000000000000000000010", v[0].first.c_str());
	EXPECT_EQ(4, v[0].second);
}

TEST_F(Test_ais_message_21, set_name_extension)
{
	{
		ais::message_21 m;

		m.set_name_extension("a");
		auto v = ais::encode_message(m);

		ASSERT_EQ(1u, v.size());
		EXPECT_STREQ("E00000000000000000000000000000000000000000001?h", v[0].first.c_str());
		EXPECT_EQ(2, v[0].second);
	}
	{
		ais::message_21 m;

		m.set_name_extension("HelloWorld");
		auto v = ais::encode_message(m);

		ASSERT_EQ(1u, v.size());
		EXPECT_STREQ(
			"E000000000000000000000000000000000000000000012?wwwmwwwwh", v[0].first.c_str());
		EXPECT_EQ(0, v[0].second);
	}
	{
		ais::message_21 m;

		m.set_name_extension("HelloWorldABCD");
		auto v = ais::encode_message(m);

		ASSERT_EQ(2u, v.size());
		EXPECT_STREQ(
			"E000000000000000000000000000000000000000000012?wwwmwwwwh", v[0].first.c_str());
		EXPECT_EQ(0, v[0].second);
		EXPECT_STREQ("@Pi0", v[1].first.c_str());
		EXPECT_EQ(0, v[1].second);
	}
}
}
