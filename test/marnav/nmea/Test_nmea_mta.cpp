#include <marnav/nmea/mta.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_mta : public ::testing::Test
{
};

TEST_F(Test_nmea_mta, contruction)
{
	EXPECT_NO_THROW(nmea::mta mta);
}

TEST_F(Test_nmea_mta, properties)
{
	nmea_sentence_traits<nmea::mta>();
}

TEST_F(Test_nmea_mta, parse)
{
	auto s = nmea::make_sentence("$IIMTA,23.4,C*00");
	ASSERT_NE(nullptr, s);

	auto mta = nmea::sentence_cast<nmea::mta>(s);
	ASSERT_NE(nullptr, mta);

	auto temperature = mta->get_temperature();
	EXPECT_NEAR(23.4, temperature.value(), 1e-8);
}

TEST_F(Test_nmea_mta, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mta>(nmea::talker::none, {1, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mta>(nmea::talker::none, {3, "@"}));
}

TEST_F(Test_nmea_mta, empty_to_string)
{
	nmea::mta mta;

	EXPECT_STREQ("$IIMTA,0.0,C*35", nmea::to_string(mta).c_str());
}

TEST_F(Test_nmea_mta, set_temperature)
{
	{
		nmea::mta mta;
		mta.set_temperature(units::celsius{12.7});
		EXPECT_STREQ("$IIMTA,12.7,C*01", nmea::to_string(mta).c_str());
	}
	{
		nmea::mta mta;
		mta.set_temperature(units::celsius{0.0});
		EXPECT_STREQ("$IIMTA,0.0,C*35", nmea::to_string(mta).c_str());
	}
	{
		nmea::mta mta;
		mta.set_temperature(units::celsius{12.66});
		EXPECT_STREQ("$IIMTA,12.7,C*01", nmea::to_string(mta).c_str());
	}
	{
		nmea::mta mta;
		mta.set_temperature(units::celsius{-12.6});
		EXPECT_STREQ("$IIMTA,-12.6,C*2D", nmea::to_string(mta).c_str());
	}
}

TEST_F(Test_nmea_mta, get_temperature)
{
	{
		const auto mta = nmea::create_sentence<nmea::mta>("$IIMTA,12.7,C*01");
		EXPECT_NEAR(12.7, mta.get_temperature().value(), 1e-8);
	}
	{
		const auto mta = nmea::create_sentence<nmea::mta>("$IIMTA,0.0,C*35");
		EXPECT_NEAR(0.0, mta.get_temperature().value(), 1e-8);
	}
	{
		const auto mta = nmea::create_sentence<nmea::mta>("$IIMTA,12.7,C*01");
		EXPECT_NEAR(12.7, mta.get_temperature().value(), 1e-8);
	}
	{
		const auto mta = nmea::create_sentence<nmea::mta>("$IIMTA,-12.6,C*2D");
		EXPECT_NEAR(-12.6, mta.get_temperature().value(), 1e-8);
	}
}
}
