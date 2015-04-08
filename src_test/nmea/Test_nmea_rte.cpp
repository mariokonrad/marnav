#include <gtest/gtest.h>
#include <marnav/nmea/rte.hpp>

namespace
{

using namespace marnav;

class Test_nmea_rte : public ::testing::Test
{
};

TEST_F(Test_nmea_rte, contruction) { nmea::rte rte; }

// TODO: implementation
}
