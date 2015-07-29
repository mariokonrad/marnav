#include <gtest/gtest.h>
#include <marnav/nmea/dse.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_dse : public ::testing::Test
{
};

TEST_F(Test_nmea_dse, contruction) { nmea::dse dse; }

TEST_F(Test_nmea_dse, parse)
{
	static const std::vector<std::string> TESTS
		= {"$CDDSE,1,1,A,3664251410,00,47800350*1D", "$CDDSE,1,1,R,3380210040,00,46506420*0F"};

	for (const auto & test : TESTS) {
		auto s = nmea::make_sentence(test);
		EXPECT_NE(nullptr, s);
		if (s) {
			auto dse = nmea::sentence_cast<nmea::dse>(s);
			EXPECT_NE(nullptr, dse);
		}
	}
}

}
