#include <gtest/gtest.h>
#include <nmea/gsv.hpp>

namespace
{
class Test_nmea_gsv : public ::testing::Test
{
};

TEST_F(Test_nmea_gsv, contruction)
{
	nmea::gsv gsv;
}

// TODO: implementation
}
