#include <gtest/gtest.h>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rmc : public ::testing::Test
{
};

TEST_F(Test_nmea_rmc, contruction)
{
	EXPECT_NO_THROW(nmea::rmc rmc);
}

TEST_F(Test_nmea_rmc, properties)
{
	nmea_sentence_traits<nmea::rmc>();
}

TEST_F(Test_nmea_rmc, parse)
{
	auto s = nmea::make_sentence("$GPRMC,,V,,,,,,,300510,0.6,E,N*39");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	auto date = rmc->get_date();
	EXPECT_TRUE(date.available());
	EXPECT_EQ(10u, date.value().year());
	EXPECT_EQ(nmea::month::may, date.value().mon());
	EXPECT_EQ(30u, date.value().day());
}

TEST_F(Test_nmea_rmc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rmc>(nmea::talker_id::none, {10, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rmc>(nmea::talker_id::none, {13, "@"}));
}

TEST_F(Test_nmea_rmc, empty_to_string)
{
	nmea::rmc rmc;

	EXPECT_STREQ("$GPRMC,,,,,,,,,,,,*4B", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, get_lat_north)
{
	auto s = nmea::make_sentence("$GPRMC,,,1234.9333,N,,,,,,,,*25");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	const auto lat = *rmc->get_lat();
	EXPECT_NEAR(12.5822, lat.get(), 1e-4);
	EXPECT_EQ(12u, lat.degrees());
	EXPECT_EQ(34u, lat.minutes());
	EXPECT_NEAR(56.0, lat.seconds(), 1e-2);
	EXPECT_EQ(geo::latitude::hemisphere::north, lat.hem());
}

TEST_F(Test_nmea_rmc, set_lat_north)
{
	nmea::rmc rmc;
	rmc.set_lat(geo::latitude{12, 34, 56, geo::latitude::hemisphere::north});

	EXPECT_STREQ("$GPRMC,,,1234.9333,N,,,,,,,,*25", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, get_lat_south)
{
	auto s = nmea::make_sentence("$GPRMC,,,1234.9333,S,,,,,,,,*38");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	const auto lat = *rmc->get_lat();
	EXPECT_NEAR(-12.5822, lat.get(), 1e-4);
	EXPECT_EQ(12u, lat.degrees());
	EXPECT_EQ(34u, lat.minutes());
	EXPECT_NEAR(56.0, lat.seconds(), 1e-2);
	EXPECT_EQ(geo::latitude::hemisphere::south, lat.hem());
}

TEST_F(Test_nmea_rmc, set_lat_south)
{
	nmea::rmc rmc;
	rmc.set_lat(geo::latitude{12, 34, 56, geo::latitude::hemisphere::south});

	EXPECT_STREQ("$GPRMC,,,1234.9333,S,,,,,,,,*38", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, get_lon_east)
{
	auto s = nmea::make_sentence("$GPRMC,,,,,12345.9333,E,,,,,,*1B");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	const auto lon = *rmc->get_lon();
	EXPECT_NEAR(123.7656, lon.get(), 1e-4);
	EXPECT_EQ(123u, lon.degrees());
	EXPECT_EQ(45u, lon.minutes());
	EXPECT_NEAR(56.0, lon.seconds(), 1e-2);
	EXPECT_EQ(geo::longitude::hemisphere::east, lon.hem());
}

TEST_F(Test_nmea_rmc, set_lon_east)
{
	nmea::rmc rmc;
	rmc.set_lon(geo::longitude{123, 45, 56, geo::longitude::hemisphere::east});

	EXPECT_STREQ("$GPRMC,,,,,12345.9333,E,,,,,,*1B", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, get_lon_west)
{
	auto s = nmea::make_sentence("$GPRMC,,,,,12345.9333,W,,,,,,*09");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	const auto lon = *rmc->get_lon();
	EXPECT_NEAR(-123.7656, lon.get(), 1e-4);
	EXPECT_EQ(123u, lon.degrees());
	EXPECT_EQ(45u, lon.minutes());
	EXPECT_NEAR(56.0, lon.seconds(), 1e-2);
	EXPECT_EQ(geo::longitude::hemisphere::west, lon.hem());
}

TEST_F(Test_nmea_rmc, set_lon_west)
{
	nmea::rmc rmc;
	rmc.set_lon(geo::longitude{123, 45, 56, geo::longitude::hemisphere::west});

	EXPECT_STREQ("$GPRMC,,,,,12345.9333,W,,,,,,*09", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, set_sog)
{
	{
		nmea::rmc rmc;
		rmc.set_sog(marnav::units::knots{4});

		EXPECT_STREQ("$GPRMC,,,,,,,4,,,,,*7F", nmea::to_string(rmc).c_str());
	}
	{
		nmea::rmc rmc;
		rmc.set_sog(marnav::units::knots{4.5});

		EXPECT_STREQ("$GPRMC,,,,,,,4.5,,,,,*64", nmea::to_string(rmc).c_str());
	}
}

TEST_F(Test_nmea_rmc, get_sog)
{
	auto s = nmea::make_sentence("$GPRMC,,,,,,,4.5,,,,,*64");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	auto sog = rmc->get_sog();
	ASSERT_TRUE(sog.available());

	EXPECT_NEAR(4.5, sog->get<marnav::units::knots>().value(), 1e-8);
}
}
