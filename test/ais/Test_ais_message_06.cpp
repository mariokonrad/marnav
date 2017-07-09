#include <gtest/gtest.h>
#include <marnav/ais/message_06.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_06 : public ::testing::Test
{
};

TEST_F(Test_ais_message_06, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("6h2E:p66B2SR04<0@00000000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_06>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_06, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_06>(ais::raw(87)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_06>(ais::raw(1009)));
}
}
