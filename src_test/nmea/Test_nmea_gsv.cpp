#include <gtest/gtest.h>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gsv : public ::testing::Test
{
};

TEST_F(Test_nmea_gsv, contruction) { nmea::gsv gsv; }

TEST_F(Test_nmea_gsv, size) { EXPECT_EQ(176u, sizeof(nmea::gsv)); }

TEST_F(Test_nmea_gsv, parse)
{
	auto s = nmea::make_sentence("$GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74");
	ASSERT_NE(nullptr, s);

	auto gsv = nmea::sentence_cast<nmea::gsv>(s);
	ASSERT_NE(nullptr, gsv);
}

TEST_F(Test_nmea_gsv, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::gsv::parse("@@", {18, "@"}));
	EXPECT_ANY_THROW(nmea::gsv::parse("@@", {20, "@"}));
}

TEST_F(Test_nmea_gsv, empty_to_string)
{
	nmea::gsv gsv;

	EXPECT_STREQ("$GPGSV,,,,,,,,,,,,,,,,,,,*79", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_message)
{
	nmea::gsv gsv;
	gsv.set_n_messages(2);
	gsv.set_message_number(1);

	EXPECT_STREQ("$GPGSV,2,1,,,,,,,,,,,,,,,,,*7A", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_n_satellites_in_view)
{
	nmea::gsv gsv;
	gsv.set_n_satellites_in_view(1);

	EXPECT_STREQ("$GPGSV,,,1,,,,,,,,,,,,,,,,*48", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_0)
{
	nmea::gsv gsv;
	gsv.set_sat_0(1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,01,02,003,04,,,,,,,,,,,,*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_1)
{
	nmea::gsv gsv;
	gsv.set_sat_1(1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,01,02,003,04,,,,,,,,*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_2)
{
	nmea::gsv gsv;
	gsv.set_sat_2(1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,,,,,01,02,003,04,,,,*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_3)
{
	nmea::gsv gsv;
	gsv.set_sat_3(1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,,,,,,,,,01,02,003,04*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_0_indexed)
{
	nmea::gsv gsv;
	gsv.set_sat(1, 1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,01,02,003,04,,,,,,,,,,,,*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_1_indexed)
{
	nmea::gsv gsv;
	gsv.set_sat(2, 1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,01,02,003,04,,,,,,,,*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_2_indexed)
{
	nmea::gsv gsv;
	gsv.set_sat(3, 1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,,,,,01,02,003,04,,,,*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_3_indexed)
{
	nmea::gsv gsv;
	gsv.set_sat(4, 1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,,,,,,,,,01,02,003,04*4D", nmea::to_string(gsv).c_str());
}

TEST_F(Test_nmea_gsv, set_sat_indexed_invalid_index)
{
	nmea::gsv gsv;
	gsv.set_sat(99, 1, 2, 3, 4);

	EXPECT_STREQ("$GPGSV,,,,,,,,,,,,,,,,,,,*79", nmea::to_string(gsv).c_str());
}

}
