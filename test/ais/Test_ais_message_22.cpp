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
	EXPECT_STREQ("F00000000003D73EB6`>6bT00000", v[0].first.c_str());
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

TEST_F(Test_ais_message_22, error_invalid_position)
{
	static const std::vector<std::pair<std::string, uint32_t>> raw
		= {{"F030p?j2N2P73FiiNesU3FR10000", 0}};

	auto m = ais::make_message(raw);
	ASSERT_TRUE(m != nullptr);
	ASSERT_TRUE(m->type() == ais::message_id::channel_management);

	auto m22 = ais::message_cast<ais::message_22>(m);

	EXPECT_ANY_THROW(m22->get_position_ne());
	EXPECT_ANY_THROW(m22->get_position_sw());
}
}
