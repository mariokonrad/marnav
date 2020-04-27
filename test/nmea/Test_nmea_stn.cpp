#include <gtest/gtest.h>
#include <marnav/nmea/stn.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_stn : public ::testing::Test
{
};

TEST_F(Test_nmea_stn, contruction)
{
	EXPECT_NO_THROW(nmea::stn stn);
}

TEST_F(Test_nmea_stn, properties)
{
	nmea_sentence_traits<nmea::stn>();
}

TEST_F(Test_nmea_stn, parse)
{
	auto s = nmea::make_sentence("$GPSTN,10*73");
	ASSERT_NE(nullptr, s);

	auto stn = nmea::sentence_cast<nmea::stn>(s);
	ASSERT_NE(nullptr, stn);
}

TEST_F(Test_nmea_stn, create_sentence)
{
	const auto s = nmea::create_sentence<nmea::stn>("$GPSTN,0*42");
	EXPECT_EQ(nmea::sentence_id::STN, s.id());
}

TEST_F(Test_nmea_stn, create_sentence_exception)
{
	EXPECT_ANY_THROW(nmea::create_sentence<nmea::stn>(""));
	EXPECT_ANY_THROW(nmea::create_sentence<nmea::stn>("$IIMWV,084.0,R,10.4,N,A*04"));
}

TEST_F(Test_nmea_stn, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::stn>(nmea::talker::none, {2, "@"}));
}

TEST_F(Test_nmea_stn, empty_to_string)
{
	nmea::stn stn;

	EXPECT_STREQ("$GPSTN,0*42", nmea::to_string(stn).c_str());
}

TEST_F(Test_nmea_stn, set_number)
{
	nmea::stn stn;
	stn.set_number(666);

	EXPECT_STREQ("$GPSTN,666*44", nmea::to_string(stn).c_str());
}

TEST_F(Test_nmea_stn, get_number)
{
	auto s = nmea::make_sentence("$GPSTN,10*73");
	ASSERT_NE(nullptr, s);

	auto stn = nmea::sentence_cast<nmea::stn>(s);
	ASSERT_NE(nullptr, stn);

	EXPECT_EQ(10u, stn->get_number());
}
}
