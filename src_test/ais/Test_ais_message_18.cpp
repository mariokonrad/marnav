#include <gtest/gtest.h>
#include <marnav/ais/message_18.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_18 : public ::testing::Test
{
};

TEST_F(Test_ais_message_18, parse)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("B000000000H0htY08D41qwv00000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_18>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_18, encode_default_values)
{
	ais::message_18 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B000000000H0htY08D41qwv00000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}
}
