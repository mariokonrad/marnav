#include <gtest/gtest.h>
#include <marnav/ais/message_08.hpp>
#include <marnav/ais/binary_001_11.hpp>
#include <marnav/ais/binary_200_10.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_08 : public ::testing::Test
{
};

TEST_F(Test_ais_message_08, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(
		std::make_pair("802R5Ph0BkEachFWA2GaOwwwwwwwwwwwwkBwwwwwwwwwwwwwwwwwwwwwwwu", 2));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_08>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_08, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_08>(ais::raw{55}));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_08>(ais::raw{1009}));
}

TEST_F(Test_ais_message_08, encode_default_values)
{
	ais::message_08 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("8000000000", v[0].first.c_str());
	EXPECT_EQ(4u, v[0].second);
}

TEST_F(Test_ais_message_08, get_binary_001_11)
{
	static const std::vector<std::pair<std::string, uint32_t>> v
		= {{"802R5Ph0BkEachFWA2GaOwwwwwwwwwwwwkBwwwwwwwwwwwwwwwwwwwwwwwu", 2}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_08>(result);
	ASSERT_TRUE(m != nullptr);

	{
		ais::binary_001_11 b;
		EXPECT_NO_THROW(m->read_binary(b));
	}
	{
		ais::binary_200_10 b;
		EXPECT_ANY_THROW(m->read_binary(b));
	}
}

TEST_F(Test_ais_message_08, set_binary_001_11)
{
	ais::message_08 m;
	ais::binary_001_11 b;

	EXPECT_NO_THROW(m.write_binary(b));
}

TEST_F(Test_ais_message_08, get_binary_200_10)
{
	static const std::vector<std::pair<std::string, uint32_t>> v
		= {{"83aGF=hj2P00000001>hj@QU6SL0", 0}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_08>(result);
	ASSERT_TRUE(m != nullptr);

	{
		ais::binary_200_10 b;
		EXPECT_NO_THROW(m->read_binary(b));
	}
	{
		ais::binary_001_11 b;
		EXPECT_ANY_THROW(m->read_binary(b));
	}
}

TEST_F(Test_ais_message_08, set_binary_200_10)
{
	ais::message_08 m;
	ais::binary_200_10 b;

	EXPECT_NO_THROW(m.write_binary(b));
}
}
