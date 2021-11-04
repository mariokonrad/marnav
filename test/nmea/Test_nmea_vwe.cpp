#include <marnav/nmea/vwe.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_vwe : public ::testing::Test
{
};

TEST_F(Test_nmea_vwe, contruction)
{
	EXPECT_NO_THROW(nmea::vwe vwe);
}

TEST_F(Test_nmea_vwe, properties)
{
	nmea_sentence_traits<nmea::vwe>();
}

TEST_F(Test_nmea_vwe, parse)
{
	auto s = nmea::make_sentence("$IIVWE,50.0*73");
	ASSERT_NE(nullptr, s);

	auto vwe = nmea::sentence_cast<nmea::vwe>(s);
	ASSERT_NE(nullptr, vwe);

	EXPECT_NEAR(50.0, vwe->get_efficiency(), 1e-8);
}

TEST_F(Test_nmea_vwe, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::vwe>(nmea::talker::none, {2, "@"}));
}

TEST_F(Test_nmea_vwe, empty_to_string)
{
	nmea::vwe vwe;

	EXPECT_STREQ("$IIVWE,0.0*46", nmea::to_string(vwe).c_str());
}

TEST_F(Test_nmea_vwe, set_efficiency)
{
	{
		nmea::vwe vwe;
		vwe.set_efficiency(10.0);
		EXPECT_STREQ("$IIVWE,10.0*77", nmea::to_string(vwe).c_str());
	}
	{
		nmea::vwe vwe;
		vwe.set_efficiency(25.1);
		EXPECT_STREQ("$IIVWE,25.1*70", nmea::to_string(vwe).c_str());
	}
	{
		nmea::vwe vwe;
		vwe.set_efficiency(100.0);
		EXPECT_STREQ("$IIVWE,100.0*47", nmea::to_string(vwe).c_str());
	}
}

TEST_F(Test_nmea_vwe, set_efficiency_invalid)
{
	nmea::vwe vwe;
	EXPECT_ANY_THROW(vwe.set_efficiency(-1.0));
	EXPECT_ANY_THROW(vwe.set_efficiency(100.1));
}

TEST_F(Test_nmea_vwe, get_efficiency)
{
	{
		const auto vwe = nmea::create_sentence<nmea::vwe>("$IIVWE,12.7*72");
		EXPECT_NEAR(12.7, vwe.get_efficiency(), 1e-8);
	}
	{
		const auto vwe = nmea::create_sentence<nmea::vwe>("$IIVWE,0.0*46");
		EXPECT_NEAR(0.0, vwe.get_efficiency(), 1e-8);
	}
	{
		const auto vwe = nmea::create_sentence<nmea::vwe>("$IIVWE,100.0*47");
		EXPECT_NEAR(100.0, vwe.get_efficiency(), 1e-8);
	}
}
}
