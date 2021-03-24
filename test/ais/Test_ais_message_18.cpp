#include <marnav/ais/message_18.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_ais_message_18 : public ::testing::Test
{
};

TEST_F(Test_ais_message_18, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("B000000000H0htY08D41qwv00000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_18>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_18, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_18>(ais::raw(167)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_18>(ais::raw(169)));
}

TEST_F(Test_ais_message_18, encode_default_values)
{
	ais::message_18 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B0000003wk?8mP=18D3Q3wv00000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_18, set_lat)
{
	ais::message_18 m;
	m.set_lat(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B0000003wk?8mP1hvN3Q3wv00000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_18, get_lat)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("B000000003?8mP1hvN3Q3wv00000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_18>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::latitude expected{12.34};
	const geo::latitude decoded = *m->get_lat();

	EXPECT_DOUBLE_EQ(expected, decoded);
}

TEST_F(Test_ais_message_18, set_lon)
{
	ais::message_18 m;
	m.set_lon(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B0000003wj=Agp=18D3Q3wv00000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_18, get_lon)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("B000000002=Agp=18D3Q3wv00000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_18>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::longitude expected{123.45};
	const geo::longitude decoded = *m->get_lon();

	EXPECT_DOUBLE_EQ(expected, decoded);
}
}
