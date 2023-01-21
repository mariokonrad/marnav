#include <marnav/ais/message_13.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_ais_message_13 : public ::testing::Test
{
};

TEST_F(test_ais_message_13, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v{{"=39UOj0jFs9R", 0}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_13>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(test_ais_message_13, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_13>(ais::raw(71)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_13>(ais::raw(169)));
}

TEST_F(test_ais_message_13, test_data)
{
	// see: https://fossies.org/linux/gpsd/test/sample.aivdm

	std::vector<std::pair<std::string, uint32_t>> v{{"=39UOj0jFs9R", 0}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_13>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(211378120u, m->get_mmsi());
	EXPECT_EQ(211217560u, m->get_mmsi_1());
}
}
