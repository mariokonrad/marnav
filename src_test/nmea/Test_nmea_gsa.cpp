#include <gtest/gtest.h>
#include <marnav/nmea/gsa.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gsa : public ::testing::Test
{
};

TEST_F(Test_nmea_gsa, contruction) { nmea::gsa gsa; }

// TODO: implementation
}
