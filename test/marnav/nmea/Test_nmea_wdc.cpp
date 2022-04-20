#include <marnav/nmea/wdc.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_wdc : public ::testing::Test
{
};

TEST_F(Test_nmea_wdc, contruction)
{
	EXPECT_NO_THROW(nmea::wdc wdc);
}

TEST_F(Test_nmea_wdc, properties)
{
	nmea_sentence_traits<nmea::wdc>();
}

TEST_F(Test_nmea_wdc, parse)
{
	auto s = nmea::make_sentence("$GPWDC,23.4,N,POINT1*43");
	ASSERT_NE(nullptr, s);

	auto wdc = nmea::sentence_cast<nmea::wdc>(s);
	ASSERT_NE(nullptr, wdc);

	auto distance = wdc->get_distance();
	EXPECT_NEAR(23.4, distance.value(), 1e-8);
	EXPECT_STREQ("POINT1", wdc->get_waypoint_id().c_str());
}

TEST_F(Test_nmea_wdc, parse_invalid_distance_unit)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPWDC,23.4,C,POINT1*00"));
}

TEST_F(Test_nmea_wdc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::wdc>(nmea::talker::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::wdc>(nmea::talker::none, {4, "@"}));
}

TEST_F(Test_nmea_wdc, empty_to_string)
{
	nmea::wdc wdc;

	EXPECT_STREQ("$GPWDC,0.0,N,*0B", nmea::to_string(wdc).c_str());
}

TEST_F(Test_nmea_wdc, set_distance)
{
	{
		nmea::wdc wdc;
		wdc.set_distance(units::nautical_miles{12.7});
		EXPECT_STREQ("$GPWDC,12.7,N,*3F", nmea::to_string(wdc).c_str());
	}
	{
		nmea::wdc wdc;
		wdc.set_distance(units::nautical_miles{0.0});
		EXPECT_STREQ("$GPWDC,0.0,N,*0B", nmea::to_string(wdc).c_str());
	}
}

TEST_F(Test_nmea_wdc, get_distance)
{
	{
		const auto wdc = nmea::create_sentence<nmea::wdc>("$GPWDC,12.7,N,POINT1*42");
		EXPECT_NEAR(12.7, wdc.get_distance().value(), 1e-8);
	}
	{
		const auto wdc = nmea::create_sentence<nmea::wdc>("$GPWDC,0.0,N,POINT1*76");
		EXPECT_NEAR(0.0, wdc.get_distance().value(), 1e-8);
	}
	{
		const auto wdc = nmea::create_sentence<nmea::wdc>("$GPWDC,12.7,N,*3F");
		EXPECT_NEAR(12.7, wdc.get_distance().value(), 1e-8);
	}
	{
		const auto wdc = nmea::create_sentence<nmea::wdc>("$GPWDC,0.0,N,*0B");
		EXPECT_NEAR(0.0, wdc.get_distance().value(), 1e-8);
	}
}

TEST_F(Test_nmea_wdc, set_waypoint)
{
	nmea::wdc wdc;
	wdc.set_waypoint_id(nmea::waypoint("POINT1"));
	EXPECT_STREQ("$GPWDC,0.0,N,POINT1*76", nmea::to_string(wdc).c_str());
}
}
