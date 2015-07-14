#include <gtest/gtest.h>
#include <marnav/ais/message_04.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_04 : public ::testing::Test
{
};

TEST_F(Test_ais_message_04, parse)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("4020ssAuho;N?PeNwjOAp<70089A", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_04>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_04, encode_default_values)
{
	ais::message_04 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("4000000000Htt<t[F0l4Y@000000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}
}
