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

TEST_F(Test_ais_message_18, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_18::parse(ais::raw{167}));
	EXPECT_ANY_THROW(ais::message_18::parse(ais::raw{169}));
}

TEST_F(Test_ais_message_18, encode_default_values)
{
	ais::message_18 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B000000003?8mP=18D3Y3wv00000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_18, set_latitude)
{
	ais::message_18 m;
	m.set_latitude(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B000000003?8mP0;C33Y3wv00000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_18, get_latitude)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("B000000003?8mP0;C33Y3wv00000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_18>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::latitude expected{12.34};
	const geo::latitude decoded = m->get_latitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

TEST_F(Test_ais_message_18, set_longitude)
{
	ais::message_18 m;
	m.set_longitude(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("B000000000>8;<=18D3Y3wv00000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_18, get_longitude)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("B000000000>8;<=18D3Y3wv00000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_18>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::longitude expected{123.45};
	const geo::longitude decoded = m->get_longitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

}
