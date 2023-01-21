#include <marnav/nmea/dbt.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_dbt : public ::testing::Test
{
};

TEST_F(test_nmea_dbt, contruction)
{
	EXPECT_NO_THROW(nmea::dbt dbt);
}

TEST_F(test_nmea_dbt, properties)
{
	nmea_sentence_traits<nmea::dbt>();
}

TEST_F(test_nmea_dbt, parse)
{
	auto s = nmea::make_sentence("$IIDBT,9.3,f,2.84,M,1.55,F*14");
	ASSERT_NE(nullptr, s);

	auto dbt = nmea::sentence_cast<nmea::dbt>(s);
	ASSERT_NE(nullptr, dbt);
}

TEST_F(test_nmea_dbt, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::dbt>(nmea::talker::none, {5, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::dbt>(nmea::talker::none, {7, "@"}));
}

TEST_F(test_nmea_dbt, empty_to_string)
{
	nmea::dbt dbt;

	EXPECT_STREQ("$IIDBT,,,,,,*52", nmea::to_string(dbt).c_str());
}

TEST_F(test_nmea_dbt, get_depth_feet)
{
	auto s = nmea::make_sentence("$IIDBT,9.3,f,,,,*10");
	ASSERT_NE(nullptr, s);

	auto dbt = nmea::sentence_cast<nmea::dbt>(s);
	ASSERT_NE(nullptr, dbt);

	ASSERT_TRUE(dbt->get_depth_feet().has_value());
	ASSERT_FALSE(dbt->get_depth_meter().has_value());
	ASSERT_FALSE(dbt->get_depth_fathom().has_value());

	const auto d = dbt->get_depth_feet();
	EXPECT_EQ(units::length{units::feet{9.3}}, d.value());
	EXPECT_EQ(units::length{units::feet{9.3}}, *d);
}

TEST_F(test_nmea_dbt, set_depth_feet)
{
	nmea::dbt dbt;
	dbt.set_depth_feet(units::feet{12.5});

	EXPECT_STREQ("$IIDBT,12.5,f,,,,*2C", nmea::to_string(dbt).c_str());
}

TEST_F(test_nmea_dbt, get_depth_meter)
{
	auto s = nmea::make_sentence("$IIDBT,,,2.84,M,,*0F");
	ASSERT_NE(nullptr, s);

	auto dbt = nmea::sentence_cast<nmea::dbt>(s);
	ASSERT_NE(nullptr, dbt);

	ASSERT_FALSE(dbt->get_depth_feet().has_value());
	ASSERT_TRUE(dbt->get_depth_meter().has_value());
	ASSERT_FALSE(dbt->get_depth_fathom().has_value());

	const auto d = dbt->get_depth_meter();
	EXPECT_EQ(units::length{units::meters{2.84}}, d.value());
	EXPECT_EQ(units::length{units::meters{2.84}}, *d);
}

TEST_F(test_nmea_dbt, set_depth_meter)
{
	nmea::dbt dbt;
	dbt.set_depth_meter(units::meters{12.5});

	EXPECT_STREQ("$IIDBT,,,12.5,M,,*07", nmea::to_string(dbt).c_str());
}

TEST_F(test_nmea_dbt, get_depth_fathom)
{
	auto s = nmea::make_sentence("$IIDBT,,,,,1.55,F*0B");
	ASSERT_NE(nullptr, s);

	auto dbt = nmea::sentence_cast<nmea::dbt>(s);
	ASSERT_NE(nullptr, dbt);

	ASSERT_FALSE(dbt->get_depth_feet().has_value());
	ASSERT_FALSE(dbt->get_depth_meter().has_value());
	ASSERT_TRUE(dbt->get_depth_fathom().has_value());

	const auto d = dbt->get_depth_fathom();
	EXPECT_EQ(units::length{units::fathoms{1.55}}, d.value());
	EXPECT_EQ(units::length{units::fathoms{1.55}}, *d);
}

TEST_F(test_nmea_dbt, set_depth_fathom)
{
	nmea::dbt dbt;
	dbt.set_depth_fathom(units::fathoms{12.5});

	EXPECT_STREQ("$IIDBT,,,,,12.5,F*0C", nmea::to_string(dbt).c_str());
}

TEST_F(test_nmea_dbt, set_depth_meter_different_unit)
{
	nmea::dbt dbt;
	dbt.set_depth_meter(units::feet{41.0105});

	EXPECT_STREQ("$IIDBT,,,12.5,M,,*07", nmea::to_string(dbt).c_str());
}
}
