#include <gtest/gtest.h>
#include <marnav/nmea/pgrmz.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_pgrmz : public ::testing::Test
{
};

TEST_F(Test_nmea_pgrmz, contruction)
{
	nmea::pgrmz pgrmz;
}

TEST_F(Test_nmea_pgrmz, properties)
{
	nmea_sentence_traits<nmea::pgrmz>();
}

TEST_F(Test_nmea_pgrmz, parse)
{
	auto s = nmea::make_sentence("$PGRMZ,1494,f,*10");
	ASSERT_NE(nullptr, s);

	auto pgrmz = nmea::sentence_cast<nmea::pgrmz>(s);
	ASSERT_NE(nullptr, pgrmz);
}

TEST_F(Test_nmea_pgrmz, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::pgrmz>(nmea::talker_id::none, {2, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::pgrmz>(nmea::talker_id::none, {4, "@"}));
}

TEST_F(Test_nmea_pgrmz, empty_to_string)
{
	nmea::pgrmz pgrmz;

	EXPECT_STREQ("$PGRMZ,0,f,*28", nmea::to_string(pgrmz).c_str());
}

TEST_F(Test_nmea_pgrmz, set_altitude)
{
	nmea::pgrmz pgrmz;
	pgrmz.set_altitude(units::feet{100});

	EXPECT_STREQ("$PGRMZ,100,f,*29", nmea::to_string(pgrmz).c_str());
}

TEST_F(Test_nmea_pgrmz, set_fix_nofix)
{
	nmea::pgrmz pgrmz;
	pgrmz.set_fix(nmea::pgrmz::fix_type::no_fix);

	EXPECT_STREQ("$PGRMZ,0,f,1*19", nmea::to_string(pgrmz).c_str());
}

TEST_F(Test_nmea_pgrmz, set_fix_2d)
{
	nmea::pgrmz pgrmz;
	pgrmz.set_fix(nmea::pgrmz::fix_type::d2fix);

	EXPECT_STREQ("$PGRMZ,0,f,2*1A", nmea::to_string(pgrmz).c_str());
}

TEST_F(Test_nmea_pgrmz, set_fix_3d)
{
	nmea::pgrmz pgrmz;
	pgrmz.set_fix(nmea::pgrmz::fix_type::d3fix);

	EXPECT_STREQ("$PGRMZ,0,f,3*1B", nmea::to_string(pgrmz).c_str());
}
}
