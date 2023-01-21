#include <marnav/nmea/io.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace
{
using namespace marnav;

class test_nmea_format : public ::testing::Test
{
};

TEST_F(test_nmea_format, format_dec_uint32)
{
	struct entry {
		uint32_t value;
		unsigned int width;
		const char * expected;
	};

	// clang-format off
	static const std::vector<entry> cases = {
		{      0, 5,  "00000" },
		{      1, 5,  "00001" },
		{     12, 5,  "00012" },
		{    123, 5,  "00123" },
		{   1234, 5,  "01234" },
		{  12345, 5,  "12345" },
		{ 123456, 5, "123456" },
	};
	// clang-format off

	for (const auto & e : cases) {
		const auto result = nmea::format(e.value, e.width, nmea::data_format::dec);
		EXPECT_STREQ(e.expected, result.c_str());
	}
}

TEST_F(test_nmea_format, format_hex_uint32)
{
	struct entry {
		uint32_t value;
		unsigned int width;
		const char * expected;
	};

	// clang-format off
	static const std::vector<entry> cases = {
		{      0x0, 5,  "00000" },
		{      0x1, 5,  "00001" },
		{     0x12, 5,  "00012" },
		{    0x123, 5,  "00123" },
		{   0x1234, 5,  "01234" },
		{  0x12345, 5,  "12345" },
		{ 0x123456, 5, "123456" },
	};
	// clang-format off

	for (const auto & e : cases) {
		const auto result = nmea::format(e.value, e.width, nmea::data_format::hex);
		EXPECT_STREQ(e.expected, result.c_str());
	}
}

TEST_F(test_nmea_format, format_dec_uint64)
{
	struct entry {
		uint64_t value;
		unsigned int width;
		const char * expected;
	};

	// clang-format off
	static const std::vector<entry> cases = {
		{          0, 8,   "00000000" },
		{          1, 8,   "00000001" },
		{         12, 8,   "00000012" },
		{        123, 8,   "00000123" },
		{       1234, 8,   "00001234" },
		{      12345, 8,   "00012345" },
		{     123456, 8,   "00123456" },
		{    1234567, 8,   "01234567" },
		{   12345678, 8,   "12345678" },
		{  123456789, 8,  "123456789" },
		{ 1234567890, 8, "1234567890" },
	};
	// clang-format off

	for (const auto & e : cases) {
		const auto result = nmea::format(e.value, e.width, nmea::data_format::dec);
		EXPECT_STREQ(e.expected, result.c_str());
	}
}

TEST_F(test_nmea_format, format_hex_uint64)
{
	struct entry {
		uint64_t value;
		unsigned int width;
		const char * expected;
	};

	// clang-format off
	static const std::vector<entry> cases = {
		{          0x0, 8,   "00000000" },
		{          0x1, 8,   "00000001" },
		{         0x12, 8,   "00000012" },
		{        0x123, 8,   "00000123" },
		{       0x1234, 8,   "00001234" },
		{      0x12345, 8,   "00012345" },
		{     0x123456, 8,   "00123456" },
		{    0x1234567, 8,   "01234567" },
		{   0x12345678, 8,   "12345678" },
		{  0x123456789, 8,  "123456789" },
		{ 0x1234567890, 8, "1234567890" },
	};
	// clang-format off

	for (const auto & e : cases) {
		const auto result = nmea::format(e.value, e.width, nmea::data_format::hex);
		EXPECT_STREQ(e.expected, result.c_str());
	}
}
}

