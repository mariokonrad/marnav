#include <gtest/gtest.h>
#include <marnav/ais/message_10.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_10 : public ::testing::Test
{
};

TEST_F(Test_ais_message_10, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair(":81:Jf1D02J0", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_10>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_10, encode_default_values)
{
	ais::message_10 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ(":00000000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_10, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_10>(ais::raw(71)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_10>(ais::raw(73)));
}
}
