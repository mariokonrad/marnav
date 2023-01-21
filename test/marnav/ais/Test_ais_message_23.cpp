#include <marnav/ais/message_23.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_ais_message_23 : public ::testing::Test
{
};

TEST_F(test_ais_message_23, parse)
{
	static const std::vector<std::vector<std::pair<std::string, uint32_t>>> TESTS = {
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

TEST_F(test_ais_message_23, encode_default_values)
{
	ais::message_23 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("G000001b3Qba3D73EB000000000", v[0].first.c_str());
	EXPECT_EQ(2u, v[0].second);
}
}
