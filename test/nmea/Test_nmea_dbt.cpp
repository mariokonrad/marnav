#include <gtest/gtest.h>
#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_dbt : public ::testing::Test
{
};

TEST_F(Test_nmea_dbt, contruction)
{
	EXPECT_NO_THROW(nmea::dbt dbt);
}

TEST_F(Test_nmea_dbt, properties)
{
	nmea_sentence_traits<nmea::dbt>();
}

TEST_F(Test_nmea_dbt, parse)
{
	auto s = nmea::make_sentence("$IIDBT,9.3,f,2.84,M,1.55,F*14");
	ASSERT_NE(nullptr, s);

	auto dbt = nmea::sentence_cast<nmea::dbt>(s);
	ASSERT_NE(nullptr, dbt);
}

TEST_F(Test_nmea_dbt, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::dbt>(nmea::talker_id::none, {5, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::dbt>(nmea::talker_id::none, {7, "@"}));
}

TEST_F(Test_nmea_dbt, empty_to_string)
{
	nmea::dbt dbt;

	EXPECT_STREQ("$IIDBT,,,,,,*52", nmea::to_string(dbt).c_str());
}

TEST_F(Test_nmea_dbt, set_depth_feet)
{
	nmea::dbt dbt;
	dbt.set_depth_feet(12.5);

	EXPECT_STREQ("$IIDBT,12.5,f,,,,*2C", nmea::to_string(dbt).c_str());
}

TEST_F(Test_nmea_dbt, set_depth_meter)
{
	nmea::dbt dbt;
	dbt.set_depth_meter(12.5);

	EXPECT_STREQ("$IIDBT,,,12.5,M,,*07", nmea::to_string(dbt).c_str());
}

TEST_F(Test_nmea_dbt, set_depth_fathom)
{
	nmea::dbt dbt;
	dbt.set_depth_fathom(12.5);

	EXPECT_STREQ("$IIDBT,,,,,12.5,F*0C", nmea::to_string(dbt).c_str());
}
}
