#include <gtest/gtest.h>
#include <marnav/nmea/apa.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{
using namespace marnav;

class Test_nmea_apa : public ::testing::Test
{
};

TEST_F(Test_nmea_apa, contruction)
{
	EXPECT_NO_THROW(nmea::apa apa);
}

TEST_F(Test_nmea_apa, properties)
{
	nmea_sentence_traits<nmea::apa>();
}

TEST_F(Test_nmea_apa, parse)
{
	auto s = nmea::make_sentence("$GPAPA,A,A,0.10,R,N,V,V,011,M,DEST*3F");
	ASSERT_NE(nullptr, s);

	auto apa = nmea::sentence_cast<nmea::apa>(s);
	ASSERT_NE(nullptr, apa);
}

TEST_F(Test_nmea_apa, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::apa>(nmea::talker_id::none, {9, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::apa>(nmea::talker_id::none, {11, "@"}));
}

TEST_F(Test_nmea_apa, empty_to_string)
{
	nmea::apa apa;

	EXPECT_STREQ("$GPAPA,,,,,,,,,,*47", nmea::to_string(apa).c_str());
}

TEST_F(Test_nmea_apa, set_waypoint)
{
	nmea::apa apa;
	apa.set_waypoint_id(nmea::waypoint{"ABC"});

	EXPECT_STREQ("$GPAPA,,,,,,,,,,ABC*07", nmea::to_string(apa).c_str());
}

TEST_F(Test_nmea_apa, set_bearing_origin_to_destination)
{
	nmea::apa apa;
	apa.set_bearing_origin_to_destination(11, nmea::reference::MAGNETIC);
	EXPECT_STREQ("$GPAPA,,,,,,,,11.0,M,*14", nmea::to_string(apa).c_str());
}

TEST_F(Test_nmea_apa, get_bearing_origin_to_destination)
{
	auto s = nmea::make_sentence("$GPAPA,A,A,0.10,R,N,V,V,011,M,DEST*3F");
	ASSERT_NE(nullptr, s);

	auto apa = nmea::sentence_cast<nmea::apa>(s);
	ASSERT_NE(nullptr, apa);

	EXPECT_NEAR(11.0, *apa->get_bearing_origin_to_destination(), 1.0e-4);
	EXPECT_EQ(nmea::reference::MAGNETIC, *apa->get_bearing_origin_to_destination_ref());
}
}
