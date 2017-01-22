#include <gtest/gtest.h>
#include <marnav/ais/binary_001_11.hpp>

namespace
{
using namespace marnav::ais;

class Test_ais_binary_001_11 : public ::testing::Test
{
};

TEST_F(Test_ais_binary_001_11, default_values)
{
	binary_001_11 b;
	raw r;

	b.write_to(r);

	EXPECT_EQ(352 - 56, r.size());
}
}
