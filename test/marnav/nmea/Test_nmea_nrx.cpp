#include <marnav/nmea/nrx.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
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

TEST_F(test_nmea_nrx, parse)
{
	auto s = nmea::make_sentence(
		"$CRNRX,007,001,00,TD02,1,135600,27,06,2001,241,3,A,==========================*09");
	ASSERT_NE(nullptr, s);

	auto nrx = nmea::sentence_cast<nmea::nrx>(s);
	ASSERT_NE(nullptr, nrx);
}

TEST_F(test_nmea_nrx, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::nrx>(nmea::talker::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::nrx>(nmea::talker::none, {6, "@"}));
}

TEST_F(test_nmea_nrx, empty_to_string)
{
	nmea::nrx nrx;

	EXPECT_STREQ("$CRNRX,,,,,,,,,,,,V,*09", nmea::to_string(nrx).c_str());
}
}
