#include <marnav/nmea/zlz.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_zlz : public ::testing::Test
{
};

TEST_F(test_nmea_zlz, contruction)
{
	EXPECT_NO_THROW(nmea::zlz zlz);
}

TEST_F(test_nmea_zlz, properties)
{
	nmea_sentence_traits<nmea::zlz>();
}

TEST_F(test_nmea_zlz, parse)
{
	auto s = nmea::make_sentence("$GPZLZ,123456.1,133456.1,01*77");
	ASSERT_NE(nullptr, s);

	auto zlz = nmea::sentence_cast<nmea::zlz>(s);
	ASSERT_NE(nullptr, zlz);

	EXPECT_EQ(nmea::time(12, 34, 56, 100), zlz->get_time_utc());
	EXPECT_EQ(nmea::time(13, 34, 56, 100), zlz->get_time_local());
	EXPECT_EQ(1, zlz->get_local_zone_description());
}

TEST_F(test_nmea_zlz, parse_large_zone_desc)
{
	auto s = nmea::make_sentence("$GPZLZ,123456.1,133456.1,09*7F");
	ASSERT_NE(nullptr, s);

	auto zlz = nmea::sentence_cast<nmea::zlz>(s);
	ASSERT_NE(nullptr, zlz);

	EXPECT_EQ(nmea::time(12, 34, 56, 100), zlz->get_time_utc());
	EXPECT_EQ(nmea::time(13, 34, 56, 100), zlz->get_time_local());
	EXPECT_EQ(9, zlz->get_local_zone_description());
}

TEST_F(test_nmea_zlz, parse_negative_zone_desc)
{
	auto s = nmea::make_sentence("$GPZLZ,123456.1,133456.1,-01*5A");
	ASSERT_NE(nullptr, s);

	auto zlz = nmea::sentence_cast<nmea::zlz>(s);
	ASSERT_NE(nullptr, zlz);

	EXPECT_EQ(nmea::time(12, 34, 56, 100), zlz->get_time_utc());
	EXPECT_EQ(nmea::time(13, 34, 56, 100), zlz->get_time_local());
	EXPECT_EQ(-1, zlz->get_local_zone_description());
}

TEST_F(test_nmea_zlz, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zlz>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::zlz>(nmea::talker::none, {4, "@"}));
}

TEST_F(test_nmea_zlz, empty_to_string)
{
	nmea::zlz zlz;

	EXPECT_STREQ("$GPZLZ,000000,000000,00*77", nmea::to_string(zlz).c_str());
}

TEST_F(test_nmea_zlz, set_time_utc)
{
	nmea::zlz zlz;
	zlz.set_time_utc(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZLZ,123456,000000,00*70", nmea::to_string(zlz).c_str());
}

TEST_F(test_nmea_zlz, set_time_local)
{
	nmea::zlz zlz;
	zlz.set_time_local(nmea::time{12, 34, 56});

	EXPECT_STREQ("$GPZLZ,000000,123456,00*70", nmea::to_string(zlz).c_str());
}

TEST_F(test_nmea_zlz, set_local_zone_description)
{
	{
		nmea::zlz zlz;
		zlz.set_local_zone_description(0);
		EXPECT_STREQ("$GPZLZ,000000,000000,00*77", nmea::to_string(zlz).c_str());
	}
	{
		nmea::zlz zlz;
		zlz.set_local_zone_description(1);
		EXPECT_STREQ("$GPZLZ,000000,000000,01*76", nmea::to_string(zlz).c_str());
	}
	{
		nmea::zlz zlz;
		zlz.set_local_zone_description(12);
		EXPECT_STREQ("$GPZLZ,000000,000000,12*74", nmea::to_string(zlz).c_str());
	}
	{
		nmea::zlz zlz;
		zlz.set_local_zone_description(-1);
		EXPECT_STREQ("$GPZLZ,000000,000000,-01*5B", nmea::to_string(zlz).c_str());
	}
	{
		nmea::zlz zlz;
		zlz.set_local_zone_description(-12);
		EXPECT_STREQ("$GPZLZ,000000,000000,-12*59", nmea::to_string(zlz).c_str());
	}
}

TEST_F(test_nmea_zlz, set_local_zone_description_invalid)
{
	nmea::zlz zlz;
	EXPECT_ANY_THROW(zlz.set_local_zone_description(-13));
	EXPECT_NO_THROW(zlz.set_local_zone_description(-12));
	EXPECT_NO_THROW(zlz.set_local_zone_description(+12));
	EXPECT_ANY_THROW(zlz.set_local_zone_description(+13));
}
}
