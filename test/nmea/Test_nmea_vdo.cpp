#include <gtest/gtest.h>
#include <marnav/nmea/vdo.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_vdo : public ::testing::Test
{
};

TEST_F(Test_nmea_vdo, contruction) { EXPECT_NO_THROW(nmea::vdo vdo); }

TEST_F(Test_nmea_vdo, parse)
{
	auto s = nmea::make_sentence("!AIVDO,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5E");
	ASSERT_NE(nullptr, s);

	auto vdo = nmea::sentence_cast<nmea::vdo>(s);
	ASSERT_NE(nullptr, vdo);

	auto fragments = vdo->get_n_fragments();
	EXPECT_EQ(1u, fragments);

	auto fragment = vdo->get_fragment();
	EXPECT_EQ(1u, fragment);
}

TEST_F(Test_nmea_vdo, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::vdo::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::vdo::parse("@@", {7, "@"}));
}
}
