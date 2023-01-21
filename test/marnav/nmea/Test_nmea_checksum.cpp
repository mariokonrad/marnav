#include <marnav/nmea/checksum.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_checksum : public ::testing::Test
{
};

TEST_F(test_nmea_checksum, checksum_error_construction)
{
	EXPECT_NO_THROW(nmea::checksum_error e(0x12, 0x34));
}

TEST_F(test_nmea_checksum, checksum_compute_sum)
{
	struct test_case {
		uint8_t sum;
		std::string s;
	};

	const std::vector<test_case> cases{
		{0x01u, "0123456789"},
		{0x1bu, "abcdefghijklmnopqrstuvwxyz"},
		{0x1bu, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
	};

	for (auto const & test : cases) {
		EXPECT_EQ(test.sum, nmea::checksum(begin(test.s), end(test.s)));
	}
}
}
