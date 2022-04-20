#include <marnav/nmea/pgrmm.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_nmea_pgrmm : public ::testing::Test
{
};

TEST_F(Test_nmea_pgrmm, contruction)
{
	nmea::pgrmm pgrmm;
}

TEST_F(Test_nmea_pgrmm, properties)
{
	nmea_sentence_traits<nmea::pgrmm>();
}

TEST_F(Test_nmea_pgrmm, parse)
{
	auto s = nmea::make_sentence("$PGRMM,WGS 84*06");
	ASSERT_NE(nullptr, s);

	auto pgrmm = nmea::sentence_cast<nmea::pgrmm>(s);
	ASSERT_NE(nullptr, pgrmm);
}

TEST_F(Test_nmea_pgrmm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::pgrmm>(nmea::talker::none, {2, "@"}));
}

TEST_F(Test_nmea_pgrmm, empty_to_string)
{
	nmea::pgrmm pgrmm;

	EXPECT_STREQ("$PGRMM,*69", nmea::to_string(pgrmm).c_str());
}

TEST_F(Test_nmea_pgrmm, set_map_datum)
{
	nmea::pgrmm pgrmm;
	pgrmm.set_map_datum("WGS 84");

	EXPECT_STREQ("$PGRMM,WGS 84*06", nmea::to_string(pgrmm).c_str());
}

TEST_F(Test_nmea_pgrmm, set_map_datum_empty)
{
	nmea::pgrmm pgrmm;
	pgrmm.set_map_datum("");

	EXPECT_STREQ("$PGRMM,*69", nmea::to_string(pgrmm).c_str());
}

TEST_F(Test_nmea_pgrmm, set_map_datum_too_large)
{
	nmea::pgrmm pgrmm;
	pgrmm.set_map_datum(
		"012345678901234567890123456789012345678901234567890123456789012345678901234567890");

	const auto s = nmea::to_string(pgrmm);

	EXPECT_EQ(nmea::sentence::max_length, s.size());
	EXPECT_STREQ(
		"$PGRMM,012345678901234567890123456789012345678901234567890123456789012345678901*69",
		s.c_str());
}
}
