#include <gtest/gtest.h>
#include <ais/message_05.hpp>
#include <ais/ais.hpp>

namespace
{

class Test_ais_message_05 : public ::testing::Test
{
};

TEST_F(Test_ais_message_05, parse)
{
	std::vector<std::pair<std::string, int>> v;
	v.push_back(std::make_pair("55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0));
	v.push_back(std::make_pair("1@0000000000000", 2));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_05>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(369190000u, m->get_mmsi());
	EXPECT_EQ(0u, m->get_ais_version());
	EXPECT_EQ(6710932u, m->get_imo_number());
	EXPECT_STREQ("WDA9674", m->get_callsign().c_str());
	EXPECT_STREQ("MT.MITCHELL@@@@@@@@@", m->get_shipname().c_str());
	EXPECT_EQ(ais::ship_type::other_no_info, m->get_shiptype());
	EXPECT_EQ(90u, m->get_to_bow());
	EXPECT_EQ(90u, m->get_to_stern());
	EXPECT_EQ(81u, m->get_to_port());
	EXPECT_EQ(80u, m->get_to_starboard());
	EXPECT_EQ(ais::epfd_fix_type::gps, m->get_epfd_fix());
	EXPECT_EQ(1u, m->get_eta_month());
	EXPECT_EQ(2u, m->get_eta_day());
	EXPECT_EQ(8u, m->get_eta_hour());
	EXPECT_EQ(0u, m->get_eta_minute());
	EXPECT_EQ(60u, m->get_draught());
	EXPECT_STREQ("SEATTLE@@@@@@@@@@@@@", m->get_destination().c_str());
	EXPECT_FALSE(m->get_dte());
}

TEST_F(Test_ais_message_05, encode_default_values)
{
	ais::message_05 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(2u, v.size());
	EXPECT_STREQ("50000000000000000000000000000000000000000000000Hh0000000", v[0].first.c_str());
	EXPECT_EQ(0, v[0].second);
	EXPECT_STREQ("000000000000008", v[1].first.c_str());
	EXPECT_EQ(2, v[1].second);
}

}
