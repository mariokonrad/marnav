#include <marnav/nmea/alm.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_alm : public ::testing::Test
{
};

TEST_F(test_nmea_alm, contruction)
{
	EXPECT_NO_THROW(nmea::alm alm);
}

TEST_F(test_nmea_alm, properties)
{
	nmea_sentence_traits<nmea::alm>();
}

TEST_F(test_nmea_alm, parse)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);

	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);
}

TEST_F(test_nmea_alm, parse_invalid_satellite_prn)
{
	EXPECT_ANY_THROW(nmea::make_sentence(
		"$GPALM,1,1,33,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*73"));
}

TEST_F(test_nmea_alm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::alm>(nmea::talker::none, {14, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::alm>(nmea::talker::none, {16, "@"}));
}

TEST_F(test_nmea_alm, empty_to_string)
{
	nmea::alm alm;

	EXPECT_STREQ("$GPALM,0,0,00,0,00,0,0,0,0,0,0,0,0,0,0*4B", nmea::to_string(alm).c_str());
}

TEST_F(test_nmea_alm, get_number_of_messages)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(1u, alm->get_number_of_messages());
}

TEST_F(test_nmea_alm, get_message_number)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(1u, alm->get_message_number());
}

TEST_F(test_nmea_alm, get_satellite_prn)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(15u, alm->get_satellite_prn());
}

TEST_F(test_nmea_alm, get_gps_week_number)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(1159u, alm->get_gps_week_number());
}

TEST_F(test_nmea_alm, get_sv_health)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0u, alm->get_sv_health());
}

TEST_F(test_nmea_alm, get_eccentricity)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x441du, alm->get_eccentricity());
}

TEST_F(test_nmea_alm, get_almanac_reference_time)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x4eu, alm->get_almanac_reference_time());
}

TEST_F(test_nmea_alm, get_inclination_angle)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x16beu, alm->get_inclination_angle());
}

TEST_F(test_nmea_alm, get_rate_of_right_ascension)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0xfd5eu, alm->get_rate_of_right_ascension());
}

TEST_F(test_nmea_alm, get_root_of_semimajor_axis)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0xa10c9fu, alm->get_root_of_semimajor_axis());
}

TEST_F(test_nmea_alm, get_argument_of_perigee)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x4a2da4u, alm->get_argument_of_perigee());
}

TEST_F(test_nmea_alm, get_longitude_of_ascension_node)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x686e81u, alm->get_longitude_of_ascension_node());
}

TEST_F(test_nmea_alm, get_mean_anomaly)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x58cbe1u, alm->get_mean_anomaly());
}

TEST_F(test_nmea_alm, get_f0_clock_parameter)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0xa4u, alm->get_f0_clock_parameter());
}

TEST_F(test_nmea_alm, get_f1_clock_parameter)
{
	auto s = nmea::make_sentence(
		"$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77");
	ASSERT_NE(nullptr, s);
	auto alm = nmea::sentence_cast<nmea::alm>(s);
	ASSERT_NE(nullptr, alm);

	EXPECT_EQ(0x001u, alm->get_f1_clock_parameter());
}
}
