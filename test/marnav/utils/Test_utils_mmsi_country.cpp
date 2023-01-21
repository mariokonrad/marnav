#include <marnav/utils/mmsi_country.hpp>
#include <marnav/utils/mmsi.hpp>
#include <gtest/gtest.h>

namespace
{
using marnav::utils::mmsi;

class test_utils_mmsi_country : public ::testing::Test
{
};

TEST_F(test_utils_mmsi_country, invalid_code)
{
	const auto info = marnav::utils::mmsi_country(mmsi{});

	EXPECT_EQ(0u, info.mid);
	EXPECT_TRUE(info.code.empty());
	EXPECT_TRUE(info.name.empty());
}

TEST_F(test_utils_mmsi_country, valid_code)
{
	const auto info = marnav::utils::mmsi_country(mmsi{269104520});

	EXPECT_EQ(269u, info.mid);
	EXPECT_STREQ("CH", info.code.c_str());
	EXPECT_STREQ("Switzerland", info.name.c_str());
}
}
