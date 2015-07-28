#include <gtest/gtest.h>
#include <marnav/nmea/dsc.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_dsc : public ::testing::Test
{
};

TEST_F(Test_nmea_dsc, contruction) { nmea::dsc dsc; }

TEST_F(Test_nmea_dsc, parse)
{
	static const std::vector<std::string> TESTS
		= {"$CDDSC,20,3380210040,00,21,26,1394807410,2231,,,B,E*75",
			"$CDDSC,20,3380210040,00,21,26,1394807410,2242,,,B,E*71",
			"$CDDSC,20,3664251410,00,21,26,1335111802,0004,,,B,E*72",
			"$CDDSC,20,3380210040,00,21,26,1394807410,0021,,,B,E*74"};

	for (const auto & test : TESTS) {
		auto s = nmea::make_sentence(test);
		EXPECT_NE(nullptr, s);
		if (s) {
			auto dsc = nmea::sentence_cast<nmea::dsc>(s);
			EXPECT_NE(nullptr, dsc);
		}
	}
}

}
