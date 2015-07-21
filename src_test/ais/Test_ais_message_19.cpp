#include <gtest/gtest.h>
#include <marnav/ais/message_19.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_19 : public ::testing::Test
{
};

TEST_F(Test_ais_message_19, parse)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("C000000000H0htY08D41qwv0000000000000000000000000000@", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_19>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_19, encode_default_values)
{
	ais::message_19 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("C000000003?8mP=18D3Y3wv0000000000000000000000000000@", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_19, set_latitude)
{
	ais::message_19 m;
	m.set_latitude(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("C000000003?8mP0;C33Y3wv0000000000000000000000000000@", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_19, get_latitude)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("C000000003?8mP0;C33Y3wv0000000000000000000000000000@", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_19>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::latitude expected{12.34};
	const geo::latitude decoded = m->get_latitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

TEST_F(Test_ais_message_19, set_longitude)
{
	ais::message_19 m;
	m.set_longitude(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("C000000000>8;<=18D3Y3wv0000000000000000000000000000@", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_19, get_longitude)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("C000000000>8;<=18D3Y3wv0000000000000000000000000000@", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_19>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::longitude expected{123.45};
	const geo::longitude decoded = m->get_longitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

}
