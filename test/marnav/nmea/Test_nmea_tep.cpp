#include <marnav/nmea/tep.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_tep : public ::testing::Test
{
};

TEST_F(test_nmea_tep, contruction)
{
	EXPECT_NO_THROW(nmea::tep tep);
}

TEST_F(test_nmea_tep, properties)
{
	nmea_sentence_traits<nmea::tep>();
}

TEST_F(test_nmea_tep, parse)
{
	auto s = nmea::make_sentence("$GPTEP,0.0,D*3C");
	ASSERT_NE(nullptr, s);

	auto tep = nmea::sentence_cast<nmea::tep>(s);
	ASSERT_NE(nullptr, tep);
}

TEST_F(test_nmea_tep, create_sentence)
{
	const auto s = nmea::create_sentence<nmea::tep>("$GPTEP,1.5,D*38");
	EXPECT_EQ(nmea::sentence_id::TEP, s.id());
}

TEST_F(test_nmea_tep, create_sentence_exception)
{
	EXPECT_ANY_THROW(nmea::create_sentence<nmea::tep>(""));
	EXPECT_ANY_THROW(nmea::create_sentence<nmea::tep>("$IIMWV,084.0,R,10.4,N,A*04"));
}

TEST_F(test_nmea_tep, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::tep>(nmea::talker::none, {1, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::tep>(nmea::talker::none, {3, "@"}));
}

TEST_F(test_nmea_tep, empty_to_string)
{
	nmea::tep tep;

	EXPECT_STREQ("$GPTEP,0.0,D*3C", nmea::to_string(tep).c_str());
}

TEST_F(test_nmea_tep, set_elevation)
{
	nmea::tep tep;
	tep.set_elevation(12.5);

	EXPECT_STREQ("$GPTEP,12.5,D*0A", nmea::to_string(tep).c_str());
}

TEST_F(test_nmea_tep, get_elevation)
{
	auto s = nmea::make_sentence("$GPTEP,12.5,D*0A");
	ASSERT_NE(nullptr, s);

	auto tep = nmea::sentence_cast<nmea::tep>(s);
	ASSERT_NE(nullptr, tep);

	EXPECT_NEAR(12.5, tep->get_elevation(), 1e-5);
}
}
