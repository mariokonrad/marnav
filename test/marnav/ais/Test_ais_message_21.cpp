#include <marnav/ais/message_21.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_ais_message_21 : public ::testing::Test
{
};

TEST_F(Test_ais_message_21, parse)
{
	static const std::vector<std::vector<std::pair<std::string, uint32_t>>> TESTS = {
		{{"E000000000000000000000000000000000000000000000", 0}},
		{{"E@28isPVa9Qh:0a90SWW0h@@@@@@2kJP;hHP@00003v0100", 2}},
		{{"E04<o5AaWdPnaGaP00000000000DPmI6:aCVH00000Wh20", 4}},
		{{"E>j9dhiQ0a2Hh;TW230a6h72P00@=igf?TQA000003vP10", 4}},
		{{"E04<o60;Rab?Pb7W00000000000DQiF0:ghTP00000`020", 4}},
	};

	for (const auto & test : TESTS) {
		auto result = ais::make_message(test);
		EXPECT_TRUE(result != nullptr);
		if (result) {
			auto m = ais::message_cast<ais::message_21>(result);
			EXPECT_TRUE(m != nullptr);
		}
	}
}

TEST_F(Test_ais_message_21, encode_default_values)
{
	ais::message_21 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("E000000000000000000000000006NAc0J2@`0000000@10", v[0].first.c_str());
	EXPECT_EQ(4u, v[0].second);
}

TEST_F(Test_ais_message_21, set_name_extension)
{
	{
		ais::message_21 m;

		m.set_name_extension("a");
		auto v = ais::encode_message(m);

		ASSERT_EQ(1u, v.size());
		EXPECT_STREQ("E000000000000000000000000006NAc0J2@`0000000@1?h", v[0].first.c_str());
		EXPECT_EQ(2u, v[0].second);
	}
	{
		ais::message_21 m;

		m.set_name_extension("HelloWorld");
		auto v = ais::encode_message(m);

		ASSERT_EQ(1u, v.size());
		EXPECT_STREQ(
			"E000000000000000000000000006NAc0J2@`0000000@12?wwwmwwwwh", v[0].first.c_str());
		EXPECT_EQ(0u, v[0].second);
	}
	{
		ais::message_21 m;

		m.set_name_extension("HelloWorldABCD");
		auto v = ais::encode_message(m);

		ASSERT_EQ(2u, v.size());
		EXPECT_STREQ(
			"E000000000000000000000000006NAc0J2@`0000000@12?wwwmwwwwh", v[0].first.c_str());
		EXPECT_EQ(0u, v[0].second);
		EXPECT_STREQ("@Pi0", v[1].first.c_str());
		EXPECT_EQ(0u, v[1].second);
	}
}
}
