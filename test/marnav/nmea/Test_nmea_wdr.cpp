#include <marnav/nmea/wdr.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_wdr : public ::testing::Test
{
};

TEST_F(test_nmea_wdr, contruction)
{
	EXPECT_NO_THROW(nmea::wdr wdr);
}

TEST_F(test_nmea_wdr, properties)
{
	nmea_sentence_traits<nmea::wdr>();
}

TEST_F(test_nmea_wdr, parse)
{
	auto s = nmea::make_sentence("$GPWDR,23.4,N,POINT1*52");
	ASSERT_NE(nullptr, s);

	auto wdr = nmea::sentence_cast<nmea::wdr>(s);
	ASSERT_NE(nullptr, wdr);

	auto distance = wdr->get_distance();
	EXPECT_NEAR(23.4, distance.value(), 1e-8);
	EXPECT_STREQ("POINT1", wdr->get_waypoint_id().c_str());
}

TEST_F(test_nmea_wdr, parse_invalid_distance_unit)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPWDR,23.4,C,POINT1*00"));
}

TEST_F(test_nmea_wdr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::wdr>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::wdr>(nmea::talker::none, {4, "@"}));
}

TEST_F(test_nmea_wdr, empty_to_string)
{
	nmea::wdr wdr;

	EXPECT_STREQ("$GPWDR,0.0,N,*1A", nmea::to_string(wdr).c_str());
}

TEST_F(test_nmea_wdr, set_distance)
{
	{
		nmea::wdr wdr;
		wdr.set_distance(units::nautical_miles{12.7});
		EXPECT_STREQ("$GPWDR,12.7,N,*2E", nmea::to_string(wdr).c_str());
	}
	{
		nmea::wdr wdr;
		wdr.set_distance(units::nautical_miles{0.0});
		EXPECT_STREQ("$GPWDR,0.0,N,*1A", nmea::to_string(wdr).c_str());
	}
}

TEST_F(test_nmea_wdr, get_distance)
{
	{
		const auto wdr = nmea::create_sentence<nmea::wdr>("$GPWDR,12.7,N,POINT1*53");
		EXPECT_NEAR(12.7, wdr.get_distance().value(), 1e-8);
	}
	{
		const auto wdr = nmea::create_sentence<nmea::wdr>("$GPWDR,0.0,N,POINT1*67");
		EXPECT_NEAR(0.0, wdr.get_distance().value(), 1e-8);
	}
	{
		const auto wdr = nmea::create_sentence<nmea::wdr>("$GPWDR,12.7,N,*2E");
		EXPECT_NEAR(12.7, wdr.get_distance().value(), 1e-8);
	}
	{
		const auto wdr = nmea::create_sentence<nmea::wdr>("$GPWDR,0.0,N,*1A");
		EXPECT_NEAR(0.0, wdr.get_distance().value(), 1e-8);
	}
}

TEST_F(test_nmea_wdr, set_waypoint)
{
	nmea::wdr wdr;
	wdr.set_waypoint_id(nmea::waypoint("POINT1"));
	EXPECT_STREQ("$GPWDR,0.0,N,POINT1*67", nmea::to_string(wdr).c_str());
}
}
