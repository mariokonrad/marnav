#include <gtest/gtest.h>
#include <marnav/nmea/rsa.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rsa : public ::testing::Test
{
};

TEST_F(Test_nmea_rsa, contruction)
{
	EXPECT_NO_THROW(nmea::rsa rsa);
}

TEST_F(Test_nmea_rsa, properties)
{
	nmea_sentence_traits<nmea::rsa>();
}

TEST_F(Test_nmea_rsa, parse)
{
	auto s = nmea::make_sentence("$IIRSA,1.0,A,,*2E");
	ASSERT_NE(nullptr, s);

	auto rsa = nmea::sentence_cast<nmea::rsa>(s);
	ASSERT_NE(nullptr, rsa);
}

TEST_F(Test_nmea_rsa, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rsa>(nmea::talker::none, {3, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rsa>(nmea::talker::none, {5, "@"}));
}

TEST_F(Test_nmea_rsa, empty_to_string)
{
	nmea::rsa rsa;

	EXPECT_STREQ("$IIRSA,,,,*40", nmea::to_string(rsa).c_str());
}

TEST_F(Test_nmea_rsa, set_rudder_and_status_1)
{
	nmea::rsa rsa;
	rsa.set_rudder1(1.0);

	EXPECT_STREQ("$IIRSA,1.0,A,,*2E", nmea::to_string(rsa).c_str());
}

TEST_F(Test_nmea_rsa, set_rudder_and_status_2)
{
	nmea::rsa rsa;
	rsa.set_rudder2(2.0);

	EXPECT_STREQ("$IIRSA,,,2.0,A*2D", nmea::to_string(rsa).c_str());
}

TEST_F(Test_nmea_rsa, get_rudder_and_status_1)
{
	auto s = nmea::make_sentence("$IIRSA,1.0,A,,*2E");
	ASSERT_NE(nullptr, s);
	auto rsa = nmea::sentence_cast<nmea::rsa>(s);
	ASSERT_NE(nullptr, rsa);

	EXPECT_NEAR(1.0, *rsa->get_rudder1(), 1e-5);
	EXPECT_EQ(nmea::status::ok, *rsa->get_rudder1_valid());
}

TEST_F(Test_nmea_rsa, get_rudder_and_status_2)
{
	auto s = nmea::make_sentence("$IIRSA,,,2.0,A*2D");
	ASSERT_NE(nullptr, s);
	auto rsa = nmea::sentence_cast<nmea::rsa>(s);
	ASSERT_NE(nullptr, rsa);

	EXPECT_NEAR(2.0, *rsa->get_rudder2(), 1e-5);
	EXPECT_EQ(nmea::status::ok, *rsa->get_rudder2_valid());
}
}
