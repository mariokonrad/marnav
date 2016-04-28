#include <gtest/gtest.h>
#include <marnav/ais/message_22.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_22 : public ::testing::Test
{
};

TEST_F(Test_ais_message_22, parse)
{
	static const std::vector<std::vector<std::pair<std::string, uint32_t>>> TESTS = {
		{{"F000000000000000000000000000", 0}}, {{"F0000000000000000000000@0000", 0}},
	};

	for (const auto & test : TESTS) {
		auto result = ais::make_message(test);
		EXPECT_TRUE(result != nullptr);
		if (result) {
			auto m = ais::message_cast<ais::message_22>(result);
			EXPECT_TRUE(m != nullptr);
		}
	}
}

TEST_F(Test_ais_message_22, encode_default_values_broadcast)
{
	ais::message_22 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("F000000000000000000000000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_22, encode_default_values_addressed)
{
	ais::message_22 m;
	m.set_addressed(true);

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("F0000000000000000000000@0000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}
}
