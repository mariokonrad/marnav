#include <marnav/nmea/fsi.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_fsi : public ::testing::Test
{
};

TEST_F(test_nmea_fsi, contruction)
{
	EXPECT_NO_THROW(nmea::fsi fsi);
}

TEST_F(test_nmea_fsi, properties)
{
	nmea_sentence_traits<nmea::fsi>();
}

TEST_F(test_nmea_fsi, parse)
{
	auto s = nmea::make_sentence("$GPFSI,156000,156025,,,*60");
	ASSERT_NE(nullptr, s);

	auto fsi = nmea::sentence_cast<nmea::fsi>(s);
	ASSERT_NE(nullptr, fsi);
}

TEST_F(test_nmea_fsi, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::fsi>(nmea::talker::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::fsi>(nmea::talker::none, {6, "@"}));
}

TEST_F(test_nmea_fsi, empty_to_string)
{
	nmea::fsi fsi;

	EXPECT_STREQ("$GPFSI,,,,,*67", nmea::to_string(fsi).c_str());
}

TEST_F(test_nmea_fsi, set_power_level)
{
	std::vector<std::pair<uint32_t, std::string>> TEST = {
		{0, "$GPFSI,,,,0,*57"},
		{1, "$GPFSI,,,,1,*56"},
		{2, "$GPFSI,,,,2,*55"},
		{3, "$GPFSI,,,,3,*54"},
		{4, "$GPFSI,,,,4,*53"},
		{5, "$GPFSI,,,,5,*52"},
		{6, "$GPFSI,,,,6,*51"},
		{7, "$GPFSI,,,,7,*50"},
		{8, "$GPFSI,,,,8,*5F"},
		{9, "$GPFSI,,,,9,*5E"},
	};

	for (const auto test : TEST) {
		nmea::fsi fsi;
		fsi.set_power_level(test.first);
		EXPECT_STREQ(test.second.c_str(), nmea::to_string(fsi).c_str());
	}
}

TEST_F(test_nmea_fsi, set_power_level_invalid)
{
	nmea::fsi fsi;
	EXPECT_ANY_THROW(fsi.set_power_level(10));
}

TEST_F(test_nmea_fsi, set_sentence_status)
{
	{
		nmea::fsi fsi;
		fsi.set_sentence_status('R');
		EXPECT_STREQ("$GPFSI,,,,,R*35", nmea::to_string(fsi).c_str());
	}
	{
		nmea::fsi fsi;
		fsi.set_sentence_status('C');
		EXPECT_STREQ("$GPFSI,,,,,C*24", nmea::to_string(fsi).c_str());
	}
	{
		nmea::fsi fsi;
		EXPECT_ANY_THROW(fsi.set_sentence_status('A'));
	}
}
}
