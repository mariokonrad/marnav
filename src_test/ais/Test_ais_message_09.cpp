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
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("91b55vRAQwOnDE<M05ICOp0208CM", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_09>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_09, encode_default_values)
{
	ais::message_09 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("900000?www<t[F0l4Y@00?000000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_09, set_latitude)
{
	ais::message_09 m;
	m.set_latitude(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("900000?www<t[F00e<<00?000000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_09, get_latitude)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("900000?www<t[F00e<<00?000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_09>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::latitude expected{12.34};
	const geo::latitude decoded = m->get_latitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

TEST_F(Test_ais_message_09, set_longitude)
{
	ais::message_09 m;
	m.set_longitude(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("900000?www0pPdhl4Y@00?000000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
}

TEST_F(Test_ais_message_09, get_longitude)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("900000?www0pPdhl4Y@00?000000", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_09>(result);
	ASSERT_TRUE(m != nullptr);

	const geo::longitude expected{123.45};
	const geo::longitude decoded = m->get_longitude();

	EXPECT_EQ(expected, decoded) << "expected value:" << static_cast<double>(expected)
								 << ", decoded value:" << static_cast<double>(decoded);
}

}
