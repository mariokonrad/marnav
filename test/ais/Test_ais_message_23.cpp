#include <gtest/gtest.h>
#include <marnav/ais/message_23.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_23 : public ::testing::Test
{
};

TEST_F(Test_ais_message_23, parse)
{
	static const std::vector<std::vector<std::pair<std::string, int>>> TESTS = {
		{{"G00000000000000000000000000", 2}},
	};

	for (const auto & test : TESTS) {
		auto result = ais::make_message(test);
		EXPECT_TRUE(result != nullptr);
		if (result) {
			auto m = ais::message_cast<ais::message_23>(result);
			EXPECT_TRUE(m != nullptr);
		}
	}
}

TEST_F(Test_ais_message_23, encode_default_values)
{
	ais::message_23 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("G00000000000000000000000000", v[0].first.c_str());
	EXPECT_EQ(2, v[0].second);
}
}
