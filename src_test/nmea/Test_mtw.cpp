#include <gtest/gtest.h>
#include <nmea/mtw.hpp>

namespace
{

class Test_mtw : public ::testing::Test
{
};

TEST_F(Test_mtw, contruction)
{
	nmea::mtw mtw;
}

TEST_F(Test_mtw, empty_to_string)
{
	nmea::mtw mtw;

	EXPECT_STREQ("$IIMTW,,*4E", nmea::to_string(mtw).c_str());
}

TEST_F(Test_mtw, set_temperature_to_string)
{
	nmea::mtw mtw;
	mtw.set_temperature(22.5);

	EXPECT_STREQ("$IIMTW,22.5,C*16", nmea::to_string(mtw).c_str());
}

}

