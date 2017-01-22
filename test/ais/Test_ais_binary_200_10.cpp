#include <gtest/gtest.h>
#include <marnav/ais/binary_200_10.hpp>

namespace
{
using namespace marnav::ais;

class Test_ais_binary_200_10 : public ::testing::Test
{
};

TEST_F(Test_ais_binary_200_10, default_values)
{
	binary_200_10 b;
	raw r;

	b.write_to(r);

	EXPECT_EQ(168 - 56, r.size());
}
}
