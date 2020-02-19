#include <gtest/gtest.h>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_vtg : public ::testing::Test
{
};

TEST_F(Test_nmea_vtg, contruction)
{
	EXPECT_NO_THROW(nmea::vtg vtg);
}

TEST_F(Test_nmea_vtg, properties)
{
	nmea_sentence_traits<nmea::vtg>();
}

TEST_F(Test_nmea_vtg, parse)
{
	auto s = nmea::make_sentence("$GPVTG,,T,,M,,N,,K,N*2C");
	ASSERT_NE(nullptr, s);

	auto vtg = nmea::sentence_cast<nmea::vtg>(s);
	ASSERT_NE(nullptr, vtg);
}

TEST_F(Test_nmea_vtg, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vtg>(nmea::talker_id::none, {7, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vtg>(nmea::talker_id::none, {10, "@"}));
}

TEST_F(Test_nmea_vtg, empty_to_string)
{
	nmea::vtg vtg;

	EXPECT_STREQ("$GPVTG,,,,,,,,,*7E", nmea::to_string(vtg).c_str());
}

TEST_F(Test_nmea_vtg, set_speed_kn)
{
	nmea::vtg vtg;
	vtg.set_speed_kn(units::knots{12.5});

	EXPECT_STREQ("$GPVTG,,,,,12.5,N,,,*28", nmea::to_string(vtg).c_str());
}

TEST_F(Test_nmea_vtg, set_speed_kmh)
{
	nmea::vtg vtg;
	vtg.set_speed_kmh(units::kilometers_per_hour{22.5});

	EXPECT_STREQ("$GPVTG,,,,,,,22.5,K,*2E", nmea::to_string(vtg).c_str());
}

TEST_F(Test_nmea_vtg, set_track_magn)
{
	nmea::vtg vtg;
	vtg.set_track_magn(12.5);

	EXPECT_STREQ("$GPVTG,,,12.5,M,,,,,*2B", nmea::to_string(vtg).c_str());
}

TEST_F(Test_nmea_vtg, set_track_true)
{
	nmea::vtg vtg;
	vtg.set_track_true(12.5);

	EXPECT_STREQ("$GPVTG,12.5,T,,,,,,,*32", nmea::to_string(vtg).c_str());
}
}
