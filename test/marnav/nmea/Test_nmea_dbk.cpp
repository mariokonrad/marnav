#include <marnav/nmea/dbk.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_dbk : public ::testing::Test
{
};

TEST_F(test_nmea_dbk, contruction)
{
	EXPECT_NO_THROW(nmea::dbk dbk);
}

TEST_F(test_nmea_dbk, properties)
{
	nmea_sentence_traits<nmea::dbk>();
}

TEST_F(test_nmea_dbk, parse)
{
	auto s = nmea::make_sentence("$IIDBK,9.3,f,1.2,M,3.4,F*00");
	ASSERT_NE(nullptr, s);

	auto dbk = nmea::sentence_cast<nmea::dbk>(s);
	ASSERT_NE(nullptr, dbk);
}

TEST_F(test_nmea_dbk, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::dbk>(nmea::talker::none, {5, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::dbk>(nmea::talker::none, {7, "@"}));
}

TEST_F(test_nmea_dbk, empty_to_string)
{
	nmea::dbk dbk;

	EXPECT_STREQ("$IIDBK,,,,,,*4D", nmea::to_string(dbk).c_str());
}

TEST_F(test_nmea_dbk, set_depth_feet)
{
	nmea::dbk dbk;
	dbk.set_depth_feet(units::feet{12.5});

	EXPECT_STREQ("$IIDBK,12.5,f,,,,*33", nmea::to_string(dbk).c_str());
}

TEST_F(test_nmea_dbk, set_depth_meter)
{
	nmea::dbk dbk;
	dbk.set_depth_meter(units::meters{12.5});

	EXPECT_STREQ("$IIDBK,,,12.5,M,,*18", nmea::to_string(dbk).c_str());
}

TEST_F(test_nmea_dbk, set_depth_fathom)
{
	nmea::dbk dbk;
	dbk.set_depth_fathom(units::fathoms{12.5});

	EXPECT_STREQ("$IIDBK,,,,,12.5,F*13", nmea::to_string(dbk).c_str());
}
}
