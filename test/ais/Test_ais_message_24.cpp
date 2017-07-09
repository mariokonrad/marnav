#include <gtest/gtest.h>
#include <marnav/ais/message_24.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_24 : public ::testing::Test
{
};

TEST_F(Test_ais_message_24, parse_part_a)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("H000000000000000000000000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_24>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_24, parse_part_b_normal)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("H000004000000000000000000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_24>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_24, parse_part_b_auxiliary)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("H<?2hN\\000000000000000000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_24>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_24, is_auxiliary_vessel)
{
	{
		ais::message_24 m;
		m.set_mmsi(utils::mmsi{2691119999});
		EXPECT_FALSE(m.is_auxiliary_vessel());
	}

	{
		ais::message_24 m;
		m.set_mmsi(utils::mmsi{981119999});
		EXPECT_TRUE(m.is_auxiliary_vessel());
	}
}

TEST_F(Test_ais_message_24, encode_default_values_part_a)
{
	ais::message_24 m;
	m.set_part_number(ais::message_24::part::A);

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("H000000000000000000000000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_24, encode_default_values_part_b_normal)
{
	ais::message_24 m;
	m.set_part_number(ais::message_24::part::B);

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("H000004000000000000000000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_24, encode_default_values_part_b_auxiliary)
{
	ais::message_24 m;
	m.set_mmsi(utils::mmsi{981119999});
	m.set_part_number(ais::message_24::part::B);

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("H>Wbkwl000000000000000000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_24, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_24>(ais::raw(167)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_24>(ais::raw(169)));
}
}
