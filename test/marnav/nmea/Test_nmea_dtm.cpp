#include <marnav/nmea/dtm.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_dtm : public ::testing::Test
{
};

TEST_F(test_nmea_dtm, contruction)
{
	EXPECT_NO_THROW(nmea::dtm dtm);
}

TEST_F(test_nmea_dtm, properties)
{
	nmea_sentence_traits<nmea::dtm>();
}

TEST_F(test_nmea_dtm, parse)
{
	auto s = nmea::make_sentence("$GPDTM,W84,,0.000000,N,0.000000,E,0.0,W84*6F");
	ASSERT_NE(nullptr, s);

	auto dtm = nmea::sentence_cast<nmea::dtm>(s);
	ASSERT_NE(nullptr, dtm);
}

TEST_F(test_nmea_dtm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::dtm>(nmea::talker::none, {7, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::dtm>(nmea::talker::none, {9, "@"}));
}

TEST_F(test_nmea_dtm, empty_to_string)
{
	nmea::dtm dtm;

	EXPECT_STREQ("$GPDTM,W84,,0.0000,N,0.0000,E,0.0,W84*6F", nmea::to_string(dtm).c_str());
}

TEST_F(test_nmea_dtm, set_lat_offset)
{
	{
		nmea::dtm dtm;
		dtm.set_lat_offset(1.0, nmea::direction::north);
		EXPECT_STREQ("$GPDTM,W84,,1.0000,N,0.0000,E,0.0,W84*6E", nmea::to_string(dtm).c_str());
	}
	{
		nmea::dtm dtm;
		dtm.set_lat_offset(1.0, nmea::direction::south);
		EXPECT_STREQ("$GPDTM,W84,,1.0000,S,0.0000,E,0.0,W84*73", nmea::to_string(dtm).c_str());
	}
}

TEST_F(test_nmea_dtm, set_lat_offset_invalid_direction)
{
	nmea::dtm dtm;

	EXPECT_NO_THROW(dtm.set_lat_offset(1.0, nmea::direction::north));
	EXPECT_NO_THROW(dtm.set_lat_offset(1.0, nmea::direction::south));
	EXPECT_ANY_THROW(dtm.set_lat_offset(1.0, nmea::direction::east));
	EXPECT_ANY_THROW(dtm.set_lat_offset(1.0, nmea::direction::west));
}

TEST_F(test_nmea_dtm, set_lon_offset)
{
	{
		nmea::dtm dtm;
		dtm.set_lon_offset(1.0, nmea::direction::east);
		EXPECT_STREQ("$GPDTM,W84,,0.0000,N,1.0000,E,0.0,W84*6E", nmea::to_string(dtm).c_str());
	}
	{
		nmea::dtm dtm;
		dtm.set_lon_offset(1.0, nmea::direction::west);
		EXPECT_STREQ("$GPDTM,W84,,0.0000,N,1.0000,W,0.0,W84*7C", nmea::to_string(dtm).c_str());
	}
}

TEST_F(test_nmea_dtm, set_lon_offset_invalid_direction)
{
	nmea::dtm dtm;

	EXPECT_ANY_THROW(dtm.set_lon_offset(1.0, nmea::direction::north));
	EXPECT_ANY_THROW(dtm.set_lon_offset(1.0, nmea::direction::south));
	EXPECT_NO_THROW(dtm.set_lon_offset(1.0, nmea::direction::east));
	EXPECT_NO_THROW(dtm.set_lon_offset(1.0, nmea::direction::west));
}

TEST_F(test_nmea_dtm, set_ref)
{
	nmea::dtm dtm;
	dtm.set_ref("ABC");
	EXPECT_STREQ("$GPDTM,ABC,,0.0000,N,0.0000,E,0.0,W84*74", nmea::to_string(dtm).c_str());
}

TEST_F(test_nmea_dtm, set_ref_too_large)
{
	nmea::dtm dtm;
	dtm.set_ref("ABCDEFGHI");
	EXPECT_STREQ("$GPDTM,ABCDE,,0.0000,N,0.0000,E,0.0,W84*75", nmea::to_string(dtm).c_str());
}

TEST_F(test_nmea_dtm, set_subcode)
{
	nmea::dtm dtm;
	dtm.set_subcode("ABC");
	EXPECT_STREQ("$GPDTM,W84,ABC,0.0000,N,0.0000,E,0.0,W84*2F", nmea::to_string(dtm).c_str());
}

TEST_F(test_nmea_dtm, set_subcode_too_large)
{
	nmea::dtm dtm;
	dtm.set_subcode("ABCDEFGHI");
	EXPECT_STREQ("$GPDTM,W84,ABCDE,0.0000,N,0.0000,E,0.0,W84*2E", nmea::to_string(dtm).c_str());
}

TEST_F(test_nmea_dtm, set_name)
{
	nmea::dtm dtm;
	dtm.set_name("ABC");
	EXPECT_STREQ("$GPDTM,W84,,0.0000,N,0.0000,E,0.0,ABC*74", nmea::to_string(dtm).c_str());
}

TEST_F(test_nmea_dtm, set_name_too_large)
{
	nmea::dtm dtm;
	dtm.set_name("ABCDEFGHI");
	EXPECT_STREQ("$GPDTM,W84,,0.0000,N,0.0000,E,0.0,ABCDE*75", nmea::to_string(dtm).c_str());
}
}
