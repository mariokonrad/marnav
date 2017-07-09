#include <gtest/gtest.h>
#include <marnav/ais/message_20.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_20 : public ::testing::Test
{
};

TEST_F(Test_ais_message_20, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("D030p8@2tN?b<`O6DmQO6D0", 2));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_20>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_20, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_20>(ais::raw(69)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_20>(ais::raw(161)));
}

TEST_F(Test_ais_message_20, get_entry_invalid_offset)
{
	ais::message_20 m;

	EXPECT_ANY_THROW(m.get_entry(-1));
	EXPECT_ANY_THROW(m.get_entry(4));
}

TEST_F(Test_ais_message_20, set_entry_invalid_offset)
{
	ais::message_20 m;
	ais::message_20::entry entry;

	EXPECT_ANY_THROW(m.set_entry(-1, entry));
	EXPECT_ANY_THROW(m.set_entry(4, entry));
}

TEST_F(Test_ais_message_20, read_fields)
{
	// see: https://fossies.org/linux/gpsd/test/sample.aivdm

	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("D030p8@2tN?b<`O6DmQO6D0", 2));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_20>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(3160097u, m->get_mmsi());

	{
		auto e = m->get_entry(0);
		EXPECT_EQ(47u, e.offset);
		EXPECT_EQ(1u, e.slots);
		EXPECT_EQ(7u, e.timeout);
		EXPECT_EQ(250u, e.increment);
	}
	{
		auto e = m->get_entry(1);
		EXPECT_EQ(2250u, e.offset);
		EXPECT_EQ(1u, e.slots);
		EXPECT_EQ(7u, e.timeout);
		EXPECT_EQ(1125u, e.increment);
	}
	{
		auto e = m->get_entry(2);
		EXPECT_EQ(856u, e.offset);
		EXPECT_EQ(5u, e.slots);
		EXPECT_EQ(7u, e.timeout);
		EXPECT_EQ(1125u, e.increment);
	}
	{
		auto e = m->get_entry(3);
		EXPECT_EQ(0u, e.offset);
		EXPECT_EQ(0u, e.slots);
		EXPECT_EQ(0u, e.timeout);
		EXPECT_EQ(0u, e.increment);
	}
}
}
