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
	EXPECT_STREQ("E000000000000000000000000000000000000000000000", v[0].first.c_str());
	EXPECT_EQ(4, v[0].second);
}

}
