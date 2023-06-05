#include "marnav/nmea/nrx.hpp"
#include "type_traits_helper.hpp"
#include "marnav/nmea/nmea.hpp"
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_nrx : public ::testing::Test
{
};

TEST_F(test_nmea_nrx, contruction)
{
	EXPECT_NO_THROW(nmea::nrx nrx);
}

TEST_F(test_nmea_nrx, properties)
{
	nmea_sentence_traits<nmea::nrx>();
}

TEST_F(test_nmea_nrx, parse_complete_sample)
{
	const std::vector<const char *> msgs = {
		"$CRNRX,007,001,00,IE69,1,135600,27,06,2001,241,3,A,==========================*09",
		"$CRNRX,007,002,00,,,,,,,,,,========^0D^0AISSUED ON SATURDAY 06 JANUARY 2001.*29",
		"$CRNRX,007,003,00,,,,,,,,,,^0D^0AINSHORE WATERS FORECAST TO 12 MILES^0D^0AOFF*0D",
		"$CRNRX,007,004,00,,,,,,,,,,SHORE FROM 1700 UTC TO 0500 UTC.^0D^0A^0D^0ANORT*1E",
		"$CRNRX,007,005,00,,,,,,,,,,H FORELAND TO SELSEY BILL.^0D^0A12 HOURS FOREC*09",
		"$CRNRX,007,006,00,,,,,,,,,,AST:^0D^0A^0ASHOWERY WINDS^2C "
		"STRONGEST IN NORTH.^0D*16",
		"$CRNRX,007,007,00,,,,,,,,,,^0A^0A*79",
	};

	std::for_each(std::begin(msgs), std::end(msgs), [](const char * msg) {
		auto s = nmea::make_sentence(msg);
		auto nrx = nmea::sentence_cast<nmea::nrx>(s);
		ASSERT_NE(nullptr, nrx);
		ASSERT_EQ(msg, nmea::to_string(*nrx));
	});
}

TEST_F(test_nmea_nrx, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::nrx>(nmea::talker::none, {12, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::nrx>(nmea::talker::none, {14, "@"}));
}

TEST_F(test_nmea_nrx, empty_to_string)
{
	nmea::nrx nrx;

	EXPECT_STREQ("$CRNRX,000,000,00,,,,,,,,,,*79", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_number_sentences)
{
	nmea::nrx nrx;
	nrx.set_number_sentences(999);

	EXPECT_STREQ("$CRNRX,999,000,00,,,,,,,,,,*70", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_sentence_number)
{
	nmea::nrx nrx;
	nrx.set_sentence_number(66);

	EXPECT_STREQ("$CRNRX,000,066,00,,,,,,,,,,*79", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_sequential_id)
{
	nmea::nrx nrx;
	nrx.set_sequential_id(10);

	EXPECT_STREQ("$CRNRX,000,000,10,,,,,,,,,,*78", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_message_code)
{
	nmea::nrx nrx;
	nrx.set_message_code({'T', 'D', 6});

	EXPECT_STREQ("$CRNRX,000,000,00,TD06,,,,,,,,,*6F", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_frequency_index)
{
	nmea::nrx nrx;
	nrx.set_frequency_index(nmea::frequency_index::f_518_khz);

	EXPECT_STREQ("$CRNRX,000,000,00,,2,,,,,,,,*4B", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_time_utc)
{
	nmea::nrx nrx;
	nrx.set_time_utc(nmea::time{14, 57, 6});

	EXPECT_STREQ("$CRNRX,000,000,00,,,145706,,,,,,,*78", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_date)
{
	nmea::nrx nrx;
	nrx.set_date(nmea::date{2023, nmea::month::april, 7});

	EXPECT_STREQ("$CRNRX,000,000,00,,,,07,04,2023,,,,*79", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_total_characters)
{
	nmea::nrx nrx;
	nrx.set_total_characters(156);

	EXPECT_STREQ("$CRNRX,000,000,00,,,,,,,156,,,*4B", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_total_bad_characters)
{
	nmea::nrx nrx;
	nrx.set_total_bad_characters(61);

	EXPECT_STREQ("$CRNRX,000,000,00,,,,,,,,61,,*7E", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_status)
{
	nmea::nrx nrx;
	nrx.set_status(nmea::status::ok);

	EXPECT_STREQ("$CRNRX,000,000,00,,,,,,,,,A,*38", nmea::to_string(nrx).c_str());
}

TEST_F(test_nmea_nrx, set_message)
{
	nmea::nrx nrx;
	nrx.set_message("IB45\r\n260909 UTC MAR 07\r\nWWJP83");

	EXPECT_STREQ("$CRNRX,000,000,00,,,,,,,,,,IB45^0D^0A260909 UTC MAR 07^0D^0AWWJP83*5D",
		nmea::to_string(nrx).c_str());
}
}
