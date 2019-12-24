#include <gtest/gtest.h>
#include <marnav/ais/message_09.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_09 : public ::testing::Test
{
};

TEST_F(Test_ais_message_09, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("91b55vRAQwOnDE<M05ICOp0208CM", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_09>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_09, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_09>(ais::raw(167)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_09>(ais::raw(169)));
}

TEST_F(Test_ais_message_09, encode_default_values)
{
	ais::message_09 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("900000?www<tSF0l4Q@>4?020000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_09, set_lat)
{
	ais::message_09 m;
	m.set_lat(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("900000?www<tSF073qp>4?020000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_09, get_lat)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("900000?www<tSF073qp>4?000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_09>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::latitude expected{12.34};
	const geo::latitude decoded = *m->get_lat();

	EXPECT_DOUBLE_EQ(expected, decoded);
}

TEST_F(Test_ais_message_09, set_lon)
{
	ais::message_09 m;
	m.set_lon(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("900000?www8m6wPl4Q@>4?020000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_09, get_lon)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("900000?www8m6wPl4Q@00?000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_09>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::longitude expected{123.45};
	const geo::longitude decoded = *m->get_lon();

	EXPECT_DOUBLE_EQ(expected, decoded);
}
}
