#include <marnav/nmea/mob.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_mob : public ::testing::Test
{
};

TEST_F(test_nmea_mob, construction)
{
	EXPECT_NO_THROW(nmea::mob mob);
}

TEST_F(test_nmea_mob, properties)
{
	nmea_sentence_traits<nmea::mob>();
}

TEST_F(test_nmea_mob, parse)
{
	auto s = nmea::make_sentence("$INMOB,ABCDE,V,123456.987,0,311219,132456.876,12.34,N,123.45,"
								 "E,12.34,23.45,269104520,0*53");
	ASSERT_NE(nullptr, s);

	auto mob = nmea::sentence_cast<nmea::mob>(s);
	ASSERT_NE(nullptr, mob);
}

TEST_F(test_nmea_mob, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mob>(nmea::talker::none, {13, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mob>(nmea::talker::none, {15, "@"}));
}

TEST_F(test_nmea_mob, empty_to_string)
{
	nmea::mob mob;

	EXPECT_STREQ("$INMOB,,E,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*09",
		nmea::to_string(mob).c_str());
}

TEST_F(test_nmea_mob, get_emitter_id_default_value)
{
	ASSERT_FALSE(nmea::mob{}.get_emitter_id().has_value());
}

TEST_F(test_nmea_mob, set_emitter_id_empty_string)
{
	nmea::mob mob;

	EXPECT_NO_THROW(mob.set_emitter_id(""));
	const auto id = mob.get_emitter_id();
	ASSERT_FALSE(id.has_value());
}

TEST_F(test_nmea_mob, set_emitter_id_large_string)
{
	nmea::mob mob;

	EXPECT_ANY_THROW(mob.set_emitter_id("012345"));
}

TEST_F(test_nmea_mob, set_emitter_id_invalid_string_content)
{
	nmea::mob mob;

	EXPECT_ANY_THROW(mob.set_emitter_id("xyz"));
	EXPECT_ANY_THROW(mob.set_emitter_id("hello"));
	EXPECT_ANY_THROW(mob.set_emitter_id("foobar"));
}

TEST_F(test_nmea_mob, set_emitter_id_valid_max_size_string)
{
	nmea::mob mob;

	EXPECT_NO_THROW(mob.set_emitter_id("fffff"));

	const auto id = mob.get_emitter_id();
	ASSERT_TRUE(id.has_value());
	EXPECT_STREQ("FFFFF", id->c_str());
}

TEST_F(test_nmea_mob, set_emitter_id_valid_short_string)
{
	nmea::mob mob;

	EXPECT_NO_THROW(mob.set_emitter_id("fff"));
	const auto id = mob.get_emitter_id();
	ASSERT_TRUE(id.has_value());
	EXPECT_STREQ("00FFF", id->c_str());
}

TEST_F(test_nmea_mob, mob_status_default)
{
	EXPECT_EQ(nmea::mob::mob_status::error, nmea::mob{}.get_mob_status());
}

TEST_F(test_nmea_mob, set_and_mob_status)
{
	{
		nmea::mob mob;
		mob.set_mob_status(nmea::mob::mob_status::mob_activated);
		EXPECT_STREQ(
			"$INMOB,,A,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*0D",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_status(nmea::mob::mob_status::test_mode);
		EXPECT_STREQ(
			"$INMOB,,T,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*18",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_status(nmea::mob::mob_status::manual_button);
		EXPECT_STREQ(
			"$INMOB,,M,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*01",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_status(nmea::mob::mob_status::mob_not_in_use);
		EXPECT_STREQ(
			"$INMOB,,V,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*1A",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_status(nmea::mob::mob_status::error);
		EXPECT_STREQ(
			"$INMOB,,E,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*09",
			to_string(mob).c_str());
	}
}

TEST_F(test_nmea_mob, set_mob_position_source_default)
{
	EXPECT_EQ(nmea::mob::mob_position_source::error, nmea::mob{}.get_mob_position_source());
}

TEST_F(test_nmea_mob, set_mob_position_source)
{
	{
		nmea::mob mob;
		mob.set_mob_position_source(nmea::mob::mob_position_source::position_estimated);
		EXPECT_STREQ(
			"$INMOB,,E,000000,0,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*0F",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_position_source(nmea::mob::mob_position_source::position_reported);
		EXPECT_STREQ(
			"$INMOB,,E,000000,1,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*0E",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_position_source(nmea::mob::mob_position_source::reserved);
		EXPECT_STREQ(
			"$INMOB,,E,000000,2,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*0D",
			to_string(mob).c_str());
	}
	{
		nmea::mob mob;
		mob.set_mob_position_source(nmea::mob::mob_position_source::error);
		EXPECT_STREQ(
			"$INMOB,,E,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,000000000,6*09",
			to_string(mob).c_str());
	}
}

TEST_F(test_nmea_mob, parse_mob_position_source)
{
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,0,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*53");
		EXPECT_EQ(
			nmea::mob::mob_position_source::position_estimated, mob.get_mob_position_source());
	}
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,1,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*52");
		EXPECT_EQ(
			nmea::mob::mob_position_source::position_reported, mob.get_mob_position_source());
	}
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,2,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*51");
		EXPECT_EQ(nmea::mob::mob_position_source::reserved, mob.get_mob_position_source());
	}
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,3,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*50");
		EXPECT_EQ(nmea::mob::mob_position_source::reserved, mob.get_mob_position_source());
	}
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,4,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*57");
		EXPECT_EQ(nmea::mob::mob_position_source::reserved, mob.get_mob_position_source());
	}
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,5,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*56");
		EXPECT_EQ(nmea::mob::mob_position_source::reserved, mob.get_mob_position_source());
	}
	{
		const auto mob
			= nmea::create_sentence<nmea::mob>("$INMOB,ABCDE,V,123456.987,6,311219,132456.876,"
											   "12.34,N,123.45,E,12.34,23.45,269104520,0*55");
		EXPECT_EQ(nmea::mob::mob_position_source::error, mob.get_mob_position_source());
	}
}

TEST_F(test_nmea_mob, set_mmsi)
{
	nmea::mob mob;

	mob.set_mmsi(utils::mmsi{269104520});

	EXPECT_STREQ("$INMOB,,E,000000,6,010100,000000,0000.0000,N,00000.0000,E,0,0,269104520,6*06",
		to_string(mob).c_str());
}
}
