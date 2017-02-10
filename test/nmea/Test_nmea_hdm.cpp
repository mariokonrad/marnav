#include <gtest/gtest.h>
#include <marnav/nmea/hdm.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_hdm : public ::testing::Test
{
};

TEST_F(Test_nmea_hdm, contruction)
{
	EXPECT_NO_THROW(nmea::hdm hdm);
}

TEST_F(Test_nmea_hdm, properties)
{
	nmea_sentence_traits<nmea::hdm>();
}

TEST_F(Test_nmea_hdm, parse)
{
	auto s = nmea::make_sentence("$HCHDM,45.8,M*10");
	ASSERT_NE(nullptr, s);

	auto hdm = nmea::sentence_cast<nmea::hdm>(s);
	ASSERT_NE(nullptr, hdm);

	auto heading = hdm->get_heading();
	EXPECT_TRUE(heading.available());
	EXPECT_NEAR(45.8, heading.value(), 1e-8);
}

TEST_F(Test_nmea_hdm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::hdm>(nmea::talker_id::none, {1, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::hdm>(nmea::talker_id::none, {3, "@"}));
}

TEST_F(Test_nmea_hdm, empty_to_string)
{
	nmea::hdm hdm;

	EXPECT_STREQ("$HCHDM,,*4A", nmea::to_string(hdm).c_str());
}

TEST_F(Test_nmea_hdm, set_heading)
{
	nmea::hdm hdm;
	hdm.set_heading(45.8);

	EXPECT_STREQ("$HCHDM,45.8,M*10", nmea::to_string(hdm).c_str());
}
}
