#include <gtest/gtest.h>
#include <marnav/ais/message_04.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_04 : public ::testing::Test
{
};

TEST_F(Test_ais_message_04, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("4020ssAuho;N?PeNwjOAp<70089A", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_04>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_04, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_04>(ais::raw(167)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_04>(ais::raw(169)));
}

TEST_F(Test_ais_message_04, encode_default_values)
{
	ais::message_04 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("4000000000Htt<tSF0l4Q@000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_04, set_latitude)
{
	ais::message_04 m;
	m.set_latitude(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("4000000000Htt<tSF073qp000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_04, get_latitude)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("4000000000Htt<tSF073qp000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_04>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::latitude expected{12.34};
	const geo::latitude decoded = *m->get_latitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

TEST_F(Test_ais_message_04, set_longitude)
{
	ais::message_04 m;
	m.set_longitude(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("4000000000Htt8m6wPl4Q@000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_04, get_longitude)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("4000000000Htt8m6wPl4Q@000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_04>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::longitude expected{123.45};
	const geo::longitude decoded = *m->get_longitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}
}
