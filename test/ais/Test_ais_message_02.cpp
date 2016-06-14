#include <gtest/gtest.h>
#include <marnav/ais/message_02.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_02 : public ::testing::Test
{
};

TEST_F(Test_ais_message_02, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("233m@ogP00PD;88MD5MTDww@2D7k", 0));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_02>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(205344990u, m->get_mmsi());
	EXPECT_EQ(-128, m->get_rot());
	EXPECT_EQ(0u, m->get_sog());
	EXPECT_EQ(true, m->get_position_accuracy());
	EXPECT_NEAR(4.40705, m->get_longitude(), 4e-5);
	EXPECT_NEAR(51.2296, m->get_latitude(), 4e-5);
	EXPECT_EQ(1107u, m->get_cog());
	EXPECT_EQ(511u, m->get_hdg());
	EXPECT_EQ(52u, m->get_timestamp());
	EXPECT_EQ(0u, m->get_maneuver_indicator());
	EXPECT_EQ(true, m->get_raim());
	EXPECT_EQ(82419u, m->get_radio_status());
}

TEST_F(Test_ais_message_02, encode_default_values)
{
	ais::message_02 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("200000?P?w<tSF0l4Q@>4?wh0000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_02, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_02::parse(ais::raw{167}));
	EXPECT_ANY_THROW(ais::message_02::parse(ais::raw{169}));
}
}
