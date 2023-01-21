#include <marnav/ais/message_07.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_ais_message_07 : public ::testing::Test
{
};

TEST_F(test_ais_message_07, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.emplace_back("702R5`hwCjq8", 0);

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_07>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(test_ais_message_07, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_07>(ais::raw(71)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_07>(ais::raw(169)));
}

TEST_F(test_ais_message_07, test_data_from_kurt_schwer)
{
	// see: https://fossies.org/linux/gpsd/test/sample.aivdm

	std::vector<std::pair<std::string, uint32_t>> v;
	v.emplace_back("7IiQ4T`UjA9lC;b:M<MWE@", 4);

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_07>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(655901842u, m->get_mmsi());
	EXPECT_EQ(158483613u, m->get_mmsi_1());
	EXPECT_EQ(321823389u, m->get_mmsi_2());
	// @todo Investigate this, it cannot be because raw data is 128 bits, which cuts MMSI_3
	// EXPECT_EQ(836359488u, m->get_mmsi_3());
	EXPECT_EQ(0u, m->get_mmsi_4());
}

TEST_F(test_ais_message_07, test_data_from_mike_green)
{
	// see: https://fossies.org/linux/gpsd/test/sample.aivdm

	std::vector<std::pair<std::string, uint32_t>> v;
	v.emplace_back("7`0Pv1L:Ac8rbgPKHA8`P", 2);

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_07>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(2u, m->get_repeat_indicator());
	EXPECT_EQ(537411077u, m->get_mmsi());
	EXPECT_EQ(43101326u, m->get_mmsi_1());
	EXPECT_EQ(717096664u, m->get_mmsi_2());
	// @todo Investigate this, it cannot be because raw data is 124 bits, which cuts MMSI_3
	// EXPECT_EQ(76161024u, m->get_mmsi_3());
	EXPECT_EQ(0u, m->get_mmsi_4());
}
}
