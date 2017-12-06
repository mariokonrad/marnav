#include <gtest/gtest.h>
#include <marnav/ais/message_03.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_03 : public ::testing::Test
{
};

TEST_F(Test_ais_message_03, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("333m@ogP00PD;88MD5MTDww@2D7k", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_03>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(205344990u, m->get_mmsi());
	EXPECT_NEAR(0.0, *m->get_rot(), 1e-4);
	EXPECT_NEAR(0.0, *m->get_sog(), 1e-4);
	EXPECT_EQ(true, m->get_position_accuracy());
	const auto lon = m->get_longitude();
	EXPECT_TRUE(!!lon);
	EXPECT_NEAR(4.40705, lon.value(), 4e-5);
	const auto lat = m->get_latitude();
	EXPECT_TRUE(!!lat);
	EXPECT_NEAR(51.2296, lat.value(), 4e-5);
	EXPECT_NEAR(110.7, *m->get_cog(), 1e-4);
	EXPECT_TRUE(!m->get_hdg());
	EXPECT_EQ(52u, m->get_timestamp());
	EXPECT_EQ(ais::maneuver_indicator_id::not_available, m->get_maneuver_indicator());
	EXPECT_EQ(true, m->get_raim());
	EXPECT_EQ(82419u, m->get_radio_status());
}

TEST_F(Test_ais_message_03, encode_default_values)
{
	ais::message_03 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("300000?P?w<tSF0l4Q@>4?wh0000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_03, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_03>(ais::raw(167)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_03>(ais::raw(169)));
}
}
