#include <marnav/nmea/ack.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_ack : public ::testing::Test
{
};

TEST_F(Test_nmea_ack, contruction)
{
	EXPECT_NO_THROW(nmea::ack ack);
}

TEST_F(Test_nmea_ack, properties)
{
	nmea_sentence_traits<nmea::ack>();
}

TEST_F(Test_nmea_ack, parse)
{
	auto s = nmea::make_sentence("$INACK,123*52");
	ASSERT_NE(nullptr, s);

	auto ack = nmea::sentence_cast<nmea::ack>(s);
	ASSERT_NE(nullptr, ack);
}

TEST_F(Test_nmea_ack, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::ack>(nmea::talker::none, {2, "@"}));
}

TEST_F(Test_nmea_ack, empty_to_string)
{
	nmea::ack ack;

	EXPECT_STREQ("$INACK,0*52", nmea::to_string(ack).c_str());
}

TEST_F(Test_nmea_ack, set_number)
{
	nmea::ack ack;
	ack.set_number(321);

	EXPECT_STREQ("$INACK,321*52", nmea::to_string(ack).c_str());
}

TEST_F(Test_nmea_ack, get_number)
{
	auto s = nmea::make_sentence("$INACK,123*52");
	ASSERT_NE(nullptr, s);

	auto ack = nmea::sentence_cast<nmea::ack>(s);
	ASSERT_NE(nullptr, ack);

	EXPECT_EQ(123u, ack->get_number());
}
}

