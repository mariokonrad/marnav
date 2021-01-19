#include <gtest/gtest.h>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_gsv : public ::testing::Test
{
};

TEST_F(Test_nmea_gsv, contruction)
{
	EXPECT_NO_THROW(nmea::gsv gsv);
}

TEST_F(Test_nmea_gsv, properties)
{
	nmea_sentence_traits<nmea::gsv>();
}

TEST_F(Test_nmea_gsv, parse)
{
	auto s = nmea::make_sentence(
		"$GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74");
	ASSERT_NE(nullptr, s);

	auto gsv = nmea::sentence_cast<nmea::gsv>(s);
	ASSERT_NE(nullptr, gsv);
}

TEST_F(Test_nmea_gsv, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::gsv>(nmea::talker::none, {18, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::gsv>(nmea::talker::none, {20, "@"}));
}

TEST_F(Test_nmea_gsv, empty_to_string)
{
	nmea::gsv gsv;

	EXPECT_STREQ("$GPGSV,1,1,0,,,,,,,,,,,,,,,,*49", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_message)
{
	nmea::gsv gsv;
	gsv.set_n_messages(2);
	gsv.set_message_number(1);

	EXPECT_STREQ("$GPGSV,2,1,0,,,,,,,,,,,,,,,,*4A", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_n_satellites_in_view)
{
	nmea::gsv gsv;
	gsv.set_n_satellites_in_view(1);

	EXPECT_STREQ("$GPGSV,1,1,1,,,,,,,,,,,,,,,,*48", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_0)
{
	nmea::gsv gsv;
	gsv.set_sat(0, {1, 2, 3, 4});

	EXPECT_STREQ("$GPGSV,1,1,0,01,02,003,04,,,,,,,,,,,,*7D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_1)
{
	nmea::gsv gsv;
	gsv.set_sat(1, {1, 2, 3, 4});

	EXPECT_STREQ("$GPGSV,1,1,0,,,,,01,02,003,04,,,,,,,,*7D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_2)
{
	nmea::gsv gsv;
	gsv.set_sat(2, {1, 2, 3, 4});

	EXPECT_STREQ("$GPGSV,1,1,0,,,,,,,,,01,02,003,04,,,,*7D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_3)
{
	nmea::gsv gsv;
	gsv.set_sat(3, {1, 2, 3, 4});

	EXPECT_STREQ("$GPGSV,1,1,0,,,,,,,,,,,,,01,02,003,04*7D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_invalid_index)
{
	nmea::gsv gsv;

	EXPECT_ANY_THROW(gsv.set_sat(99, {1, 2, 3, 4}));
	EXPECT_ANY_THROW(gsv.set_sat(-1, {1, 2, 3, 4}));
}

TEST_F(Test_nmea_gsv, get_sat_invalid_index)
{
	nmea::gsv gsv;

	EXPECT_ANY_THROW(gsv.get_sat(-1));
	EXPECT_ANY_THROW(gsv.get_sat(4));
}

TEST_F(Test_nmea_gsv, get_sat)
{
	auto s = nmea::make_sentence(
		"$GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74");
	ASSERT_NE(nullptr, s);

	auto gsv = nmea::sentence_cast<nmea::gsv>(s);
	ASSERT_NE(nullptr, gsv);

	EXPECT_EQ(3u, gsv->get_n_messages());
	EXPECT_EQ(1u, gsv->get_message_number());
	EXPECT_EQ(11u, gsv->get_n_satellites_in_view());

	{
		const auto sat = *gsv->get_sat(0);
		EXPECT_EQ(3u, sat.prn);
		EXPECT_EQ(3u, sat.elevation);
		EXPECT_EQ(111u, sat.azimuth);
		EXPECT_EQ(0u, *sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(1);
		EXPECT_EQ(4u, sat.prn);
		EXPECT_EQ(15u, sat.elevation);
		EXPECT_EQ(270u, sat.azimuth);
		EXPECT_EQ(0u, *sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(2);
		EXPECT_EQ(6u, sat.prn);
		EXPECT_EQ(1u, sat.elevation);
		EXPECT_EQ(10u, sat.azimuth);
		EXPECT_EQ(0u, *sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(3);
		EXPECT_EQ(13u, sat.prn);
		EXPECT_EQ(6u, sat.elevation);
		EXPECT_EQ(292u, sat.azimuth);
		EXPECT_EQ(0u, *sat.snr);
	}
}

TEST_F(Test_nmea_gsv, get_sat_missing_snr_github_issue_35)
{
	// thanks to github.com/norton-dev for providing this example

	auto s = nmea::make_sentence(
		"$GPGSV,3,1,09,09,74,265,,04,63,066,14,06,50,261,,03,32,123,31*7B");
	ASSERT_NE(nullptr, s);

	auto gsv = nmea::sentence_cast<nmea::gsv>(s);
	ASSERT_NE(nullptr, gsv);

	EXPECT_EQ(3u, gsv->get_n_messages());
	EXPECT_EQ(1u, gsv->get_message_number());
	EXPECT_EQ(9u, gsv->get_n_satellites_in_view());

	{
		const auto sat = *gsv->get_sat(0);
		EXPECT_EQ(9u, sat.prn);
		EXPECT_EQ(74u, sat.elevation);
		EXPECT_EQ(265u, sat.azimuth);
		EXPECT_FALSE(sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(1);
		EXPECT_EQ(4u, sat.prn);
		EXPECT_EQ(63u, sat.elevation);
		EXPECT_EQ(66u, sat.azimuth);
		EXPECT_EQ(14u, *sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(2);
		EXPECT_EQ(6u, sat.prn);
		EXPECT_EQ(50u, sat.elevation);
		EXPECT_EQ(261u, sat.azimuth);
		EXPECT_FALSE(sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(3);
		EXPECT_EQ(3u, sat.prn);
		EXPECT_EQ(32u, sat.elevation);
		EXPECT_EQ(123u, sat.azimuth);
		EXPECT_EQ(31u, *sat.snr);
	}
}

TEST_F(Test_nmea_gsv, get_satinfo_missing_github_issue_37)
{
	// thanks to github.com/norton-dev for providing this example

	auto sentence = nmea::make_sentence(
		"$GLGSV,3,3,10,83,11,003,,83,11,003,,,,,,,,,*64");
	auto gsv = nmea::sentence_cast<nmea::gsv>(sentence);

	EXPECT_EQ(3u, gsv->get_n_messages());
	EXPECT_EQ(3u, gsv->get_message_number());
	EXPECT_EQ(10u, gsv->get_n_satellites_in_view());

	{
		const auto sat = *gsv->get_sat(0);
		EXPECT_EQ(83u, sat.prn);
		EXPECT_EQ(11u, sat.elevation);
		EXPECT_EQ(3u, sat.azimuth);
		EXPECT_FALSE(sat.snr);
	}
	{
		const auto sat = *gsv->get_sat(1);
		EXPECT_EQ(83u, sat.prn);
		EXPECT_EQ(11u, sat.elevation);
		EXPECT_EQ(3u, sat.azimuth);
		EXPECT_FALSE(sat.snr);
	}
	{
		const auto sat = gsv->get_sat(2);
		EXPECT_FALSE(sat.has_value());
	}
	{
		const auto sat = gsv->get_sat(3);
		EXPECT_FALSE(sat.has_value());
	}
}

TEST_F(Test_nmea_gsv, get_satinfo_missing_github_to_string_issue_37)
{
	nmea::gsv gsv;

	gsv.set_talker(nmea::talker::glonass);
	gsv.set_n_messages(3u);
	gsv.set_message_number(3u);
	gsv.set_n_satellites_in_view(10u);
	gsv.set_sat(0, { 83, 11, 3, {}});
	gsv.set_sat(1, { 83, 11, 3, {}});

	const auto s = to_string(gsv);

	EXPECT_STREQ("$GLGSV,3,3,10,83,11,003,,83,11,003,,,,,,,,,*64", s.c_str());
}
}

