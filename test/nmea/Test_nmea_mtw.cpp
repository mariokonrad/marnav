#include <gtest/gtest.h>
#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_mtw : public ::testing::Test
{
};

TEST_F(Test_nmea_mtw, contruction)
{
	EXPECT_NO_THROW(nmea::mtw mtw);
}

TEST_F(Test_nmea_mtw, properties)
{
	nmea_sentence_traits<nmea::mtw>();
}

TEST_F(Test_nmea_mtw, parse)
{
	auto s = nmea::make_sentence("$IIMTW,9.5,C*2F");
	ASSERT_NE(nullptr, s);

	auto mtw = nmea::sentence_cast<nmea::mtw>(s);
	ASSERT_NE(nullptr, mtw);

	auto temperature = mtw->get_temperature();
	ASSERT_TRUE(temperature.available());
	EXPECT_NEAR(9.5, temperature.value(), 1e-8);

	auto unit = mtw->get_temperature_unit();
	ASSERT_TRUE(unit.available());
	EXPECT_EQ(nmea::unit::temperature::celsius, unit.value());
}

TEST_F(Test_nmea_mtw, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::mtw>(nmea::talker_id::none, {1, "@"}));
	EXPECT_ANY_THROW(nmea::sentence_parse<nmea::mtw>(nmea::talker_id::none, {3, "@"}));
}

TEST_F(Test_nmea_mtw, empty_to_string)
{
	nmea::mtw mtw;

	EXPECT_STREQ("$IIMTW,,*4E", nmea::to_string(mtw).c_str());
}

TEST_F(Test_nmea_mtw, set_temperature_to_string)
{
	nmea::mtw mtw;
	mtw.set_temperature(22.5);

	EXPECT_STREQ("$IIMTW,22.5,C*16", nmea::to_string(mtw).c_str());
}
}
