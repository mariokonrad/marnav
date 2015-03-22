#include <gtest/gtest.h>
#include <nmea/gsa.hpp>

namespace
{
class Test_nmea_gsa : public ::testing::Test
{
};

TEST_F(Test_nmea_gsa, contruction)
{
	nmea::gsa gsa;
}

// TODO: implementation
}
