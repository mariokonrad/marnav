#include <gtest/gtest.h>
#include <marnav/nmea/rot.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rot : public ::testing::Test
{
};

TEST_F(Test_nmea_rot, contruction)
{
	EXPECT_NO_THROW(nmea::rot rot);
}

TEST_F(Test_nmea_rot, properties)
{
	nmea_sentence_traits<nmea::rot>();
}

TEST_F(Test_nmea_rot, parse)
{
	auto s = nmea::make_sentence("$GPROT,1.0,A*30");
	ASSERT_NE(nullptr, s);

	auto rot = nmea::sentence_cast<nmea::rot>(s);
	ASSERT_NE(nullptr, rot);
}

TEST_F(Test_nmea_rot, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rot>(nmea::talker_id::none, {1, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rot>(nmea::talker_id::none, {3, "@"}));
}

TEST_F(Test_nmea_rot, empty_to_string)
{
	nmea::rot rot;

	EXPECT_STREQ("$GPROT,,*5E", nmea::to_string(rot).c_str());
}

TEST_F(Test_nmea_rot, set_deg_per_minute)
{
	nmea::rot rot;
	rot.set_deg_per_minute(1.0);

	EXPECT_STREQ("$GPROT,1.0,*71", nmea::to_string(rot).c_str());
}

TEST_F(Test_nmea_rot, set_data_valid)
{
	nmea::rot rot;
	rot.set_data_valid(nmea::status::ok);

	EXPECT_STREQ("$GPROT,,A*1F", nmea::to_string(rot).c_str());
}
}
