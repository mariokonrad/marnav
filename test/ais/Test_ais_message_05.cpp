#include <gtest/gtest.h>
#include <marnav/ais/message_05.hpp>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais_message_05 : public ::testing::Test
{
};

TEST_F(Test_ais_message_05, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0));
	v.push_back(std::make_pair("1@0000000000000", 2));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_05>(result);
	ASSERT_TRUE(m != nullptr);

	const auto dim = m->get_vessel_dimension();

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(369190000u, m->get_mmsi());
	EXPECT_EQ(0u, m->get_ais_version());
	EXPECT_EQ(6710932u, m->get_imo_number());
	EXPECT_STREQ("WDA9674", m->get_callsign().c_str());
	EXPECT_STREQ("MT.MITCHELL", m->get_shipname().c_str());
	EXPECT_EQ(ais::ship_type::other_no_info, m->get_shiptype());
	EXPECT_EQ(units::meters{90}, dim.get_to_bow());
	EXPECT_EQ(units::meters{90}, dim.get_to_stern());
	EXPECT_EQ(units::meters{10}, dim.get_to_port());
	EXPECT_EQ(units::meters{10}, dim.get_to_starboard());
	EXPECT_EQ(ais::epfd_fix_type::gps, m->get_epfd_fix());
	EXPECT_EQ(1u, m->get_eta_month());
	EXPECT_EQ(2u, m->get_eta_day());
	EXPECT_EQ(8u, m->get_eta_hour());
	EXPECT_EQ(0u, m->get_eta_minute());
	EXPECT_EQ(units::meters{6.0}, m->get_draught());
	EXPECT_STREQ("SEATTLE", m->get_destination().c_str());
	EXPECT_EQ(ais::data_terminal::ready, m->get_dte());
}

TEST_F(Test_ais_message_05, parse_422)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.push_back(std::make_pair("55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0));
	v.push_back(std::make_pair("1@0000000000000", 4));

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_05>(result);
	ASSERT_TRUE(m != nullptr);

	const auto dim = m->get_vessel_dimension();

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(369190000u, m->get_mmsi());
	EXPECT_EQ(0u, m->get_ais_version());
	EXPECT_EQ(6710932u, m->get_imo_number());
	EXPECT_STREQ("WDA9674", m->get_callsign().c_str());
	EXPECT_STREQ("MT.MITCHELL", m->get_shipname().c_str());
	EXPECT_EQ(ais::ship_type::other_no_info, m->get_shiptype());
	EXPECT_EQ(units::meters{90}, dim.get_to_bow());
	EXPECT_EQ(units::meters{90}, dim.get_to_stern());
	EXPECT_EQ(units::meters{10}, dim.get_to_port());
	EXPECT_EQ(units::meters{10}, dim.get_to_starboard());
	EXPECT_EQ(ais::epfd_fix_type::gps, m->get_epfd_fix());
	EXPECT_EQ(1u, m->get_eta_month());
	EXPECT_EQ(2u, m->get_eta_day());
	EXPECT_EQ(8u, m->get_eta_hour());
	EXPECT_EQ(0u, m->get_eta_minute());
	EXPECT_EQ(units::meters{6.0}, m->get_draught());
	EXPECT_STREQ("SEATTLE", m->get_destination().c_str());

	// the default value, because the raw message was 2 bits short (dte and spare bit)
	EXPECT_EQ(ais::data_terminal::not_ready, m->get_dte());
}

TEST_F(Test_ais_message_05, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_05>(ais::raw(421)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_05>(ais::raw(425)));
}

TEST_F(Test_ais_message_05, encode_default_values)
{
	ais::message_05 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(2u, v.size());
	EXPECT_STREQ(
		"50000000000000000000000000000000000000000000000Ht0000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
	EXPECT_STREQ("000000000000008", v[1].first.c_str());
	EXPECT_EQ(2u, v[1].second);
}

TEST_F(Test_ais_message_05, set_callsign)
{
	ais::message_05 m;
	m.set_callsign("1234567");

	auto v = ais::encode_message(m);

	ASSERT_EQ(2u, v.size());
	EXPECT_STREQ(
		"5000000000037;?CGKL0000000000000000000000000000Ht0000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_05, set_callsign_too_large)
{
	ais::message_05 m;
	m.set_callsign("123456789012345678901234567890");

	EXPECT_STREQ("1234567", m.get_callsign().c_str());
}

TEST_F(Test_ais_message_05, set_shipname)
{
	ais::message_05 m;
	m.set_shipname("1234567");

	auto v = ais::encode_message(m);

	ASSERT_EQ(2u, v.size());
	EXPECT_STREQ(
		"50000000000000000037;?CGKL000000000000000000000Ht0000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_05, set_shipname_too_large)
{
	ais::message_05 m;
	m.set_shipname("123456789012345678901234567890");

	EXPECT_STREQ("12345678901234567890", m.get_shipname().c_str());
}

TEST_F(Test_ais_message_05, set_destination)
{
	ais::message_05 m;
	m.set_destination("1234567");

	auto v = ais::encode_message(m);

	ASSERT_EQ(2u, v.size());
	EXPECT_STREQ(
		"50000000000000000000000000000000000000000000000Ht0<Ldu=M", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(Test_ais_message_05, set_destination_too_large)
{
	ais::message_05 m;
	m.set_destination("123456789012345678901234567890");

	EXPECT_STREQ("12345678901234567890", m.get_destination().c_str());
}

TEST_F(Test_ais_message_05, set_to_bow_exact)
{
	const ais::vessel_dimension d(units::meters{4.0}, {}, {}, {});
	ais::message_05 m;

	EXPECT_NO_THROW(m.set_vessel_dimension(d));
	EXPECT_EQ(units::meters{4.0}, m.get_vessel_dimension().get_to_bow());
}

TEST_F(Test_ais_message_05, set_to_bow_rounded_up)
{
	const ais::vessel_dimension d(units::meters{4.6}, {}, {}, {});
	ais::message_05 m;

	EXPECT_NO_THROW(m.set_vessel_dimension(d));
	EXPECT_EQ(units::meters{5.0}, m.get_vessel_dimension().get_to_bow());
}

TEST_F(Test_ais_message_05, set_to_bow_rounded_down)
{
	const ais::vessel_dimension d(units::meters{4.1}, {}, {}, {});
	ais::message_05 m;

	EXPECT_NO_THROW(m.set_vessel_dimension(d));
	EXPECT_EQ(units::meters{4.0}, m.get_vessel_dimension().get_to_bow());
}

TEST_F(Test_ais_message_05, set_get_drought_meters)
{
	ais::message_05 m;

	EXPECT_NO_THROW(m.set_draught(units::meters{1.5}));
	EXPECT_EQ(units::meters{1.5}, m.get_draught());
}

TEST_F(Test_ais_message_05, set_get_drought_meters_truncating_resolution)
{
	ais::message_05 m;

	// note: message_05: resolution of draught in 0.1m

	EXPECT_NO_THROW(m.set_draught(units::meters{1.51}));
	EXPECT_EQ(units::meters{1.6}, m.get_draught());
}

TEST_F(Test_ais_message_05, set_get_drought_feet)
{
	ais::message_05 m;

	// note: message_05: resolution of draught in 0.1m

	EXPECT_NO_THROW(m.set_draught(units::feet{3}));
	EXPECT_EQ(units::meters{1.0}, m.get_draught());
}

TEST_F(Test_ais_message_05, set_invalid_draught)
{
	ais::message_05 m;

	EXPECT_ANY_THROW(m.set_draught(units::meters{-1.5}));
}
}
