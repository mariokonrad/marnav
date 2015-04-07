#include <gtest/gtest.h>
#include <nmea/rmb.hpp>

namespace
{

using namespace marnav;

class Test_nmea_rmb : public ::testing::Test
{
};

TEST_F(Test_nmea_rmb, contruction) { nmea::rmb rmb; }

// TODO: implementation
}
