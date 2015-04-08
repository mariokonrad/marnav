#include <gtest/gtest.h>
#include <marnav/nmea/gsv.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gsv : public ::testing::Test
{
};

TEST_F(Test_nmea_gsv, contruction) { nmea::gsv gsv; }

// TODO: implementation
}
