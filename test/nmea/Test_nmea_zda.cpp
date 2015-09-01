#include <gtest/gtest.h>
#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_zda : public ::testing::Test
{
};

TEST_F(Test_nmea_zda, contruction) { EXPECT_NO_THROW(nmea::zda zda); }

TEST_F(Test_nmea_zda, parse)
{
	auto s = nmea::make_sentence("$GPZDA,160012.71,11,03,2004,-1,00*7D");
	ASSERT_NE(nullptr, s);

	auto zda = nmea::sentence_cast<nmea::zda>(s);
	ASSERT_NE(nullptr, zda);
}

TEST_F(Test_nmea_zda, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::zda::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::zda::parse("@@", {7, "@"}));
}

TEST_F(Test_nmea_zda, empty_to_string)
{
	nmea::zda zda;

	EXPECT_STREQ("$GPZDA,,,,,,*48", nmea::to_string(zda).c_str());
}

TEST_F(Test_nmea_zda, set_time_utc)
{
	nmea::zda zda;
	zda.set_time_utc(nmea::time{1, 2, 3});

	EXPECT_STREQ("$GPZDA,010203,,,,,*48", nmea::to_string(zda).c_str());
}

TEST_F(Test_nmea_zda, set_date)
{
	nmea::zda zda;
	zda.set_date(2015, 6, 28);

	EXPECT_STREQ("$GPZDA,,28,06,2015,,*42", nmea::to_string(zda).c_str());
}

TEST_F(Test_nmea_zda, set_local_zone)
{
	nmea::zda zda;
	zda.set_local_zone(10, 0);

	EXPECT_STREQ("$GPZDA,,,,,10,00*49", nmea::to_string(zda).c_str());
}

}

