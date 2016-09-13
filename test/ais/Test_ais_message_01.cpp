#include <gtest/gtest.h>
#include <marnav/ais/message_01.hpp>
#include <marnav/ais/ais.hpp>

#include <marnav/nmea/vdm.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_01 : public ::testing::Test
{
};

TEST_F(Test_ais_message_01, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("133m@ogP00PD;88MD5MTDww@2D7k", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_01>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(205344990u, m->get_mmsi());
	EXPECT_EQ(ais::rot_not_available, m->get_rot());
	EXPECT_EQ(0u, m->get_sog());
	EXPECT_EQ(true, m->get_position_accuracy());
	auto lon = m->get_longitude();
	EXPECT_TRUE(!!lon);
	EXPECT_NEAR(4.40705, lon.value(), 4e-5);
	auto lat = m->get_latitude();
	EXPECT_TRUE(!!lat);
	EXPECT_NEAR(51.2296, lat.value(), 4e-5);
	EXPECT_EQ(1107u, m->get_cog());
	EXPECT_EQ(511u, m->get_hdg());
	EXPECT_EQ(52u, m->get_timestamp());
	EXPECT_EQ(0u, m->get_maneuver_indicator());
	EXPECT_EQ(true, m->get_raim());
	EXPECT_EQ(82419u, m->get_radio_status());
}

TEST_F(Test_ais_message_01, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_01>(ais::raw{167}));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_01>(ais::raw{169}));
}

TEST_F(Test_ais_message_01, encode_default_values)
{
	ais::message_01 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("100000?P?w<tSF0l4Q@>4?wh0000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_01, set_latitude)
{
	ais::message_01 m;
	m.set_latitude(geo::latitude{12.34});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("100000?P?w<tSF073qp>4?wh0000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_01, set_longitude)
{
	ais::message_01 m;
	m.set_longitude(geo::longitude{123.45});

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("100000?P?w8m6wPl4Q@>4?wh0000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_01, github_issue_2)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("15RTgt0PAso;90TKcjM8h6g208CQ", 0));

	const auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	const auto m = ais::message_cast<ais::message_01>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_NEAR(-123.3954, *m->get_longitude(), 1e-4);
	EXPECT_NEAR(48.3816, *m->get_latitude(), 1e-4);
}
}
