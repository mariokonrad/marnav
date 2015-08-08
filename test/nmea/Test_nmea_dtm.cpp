#include <gtest/gtest.h>
#include <marnav/nmea/dtm.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_dtm : public ::testing::Test
{
};

TEST_F(Test_nmea_dtm, contruction) { nmea::dtm dtm; }

TEST_F(Test_nmea_dtm, parse)
{
	auto s = nmea::make_sentence("$GPDTM,W84,,0.000000,N,0.000000,E,0.0,W84*6F");
	ASSERT_NE(nullptr, s);

	auto dtm = nmea::sentence_cast<nmea::dtm>(s);
	ASSERT_NE(nullptr, dtm);
}

TEST_F(Test_nmea_dtm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::dtm::parse("@@", {7, "@"}));
	EXPECT_ANY_THROW(nmea::dtm::parse("@@", {9, "@"}));
}

TEST_F(Test_nmea_dtm, empty_to_string)
{
	nmea::dtm dtm;

	EXPECT_STREQ("$GPDTM,W84,,0.0000,N,0.0000,E,0.0,W84*6F", nmea::to_string(dtm).c_str());
}

TEST_F(Test_nmea_dtm, set_lat_offset)
{
	{
		nmea::dtm dtm;
		dtm.set_lat_offset(1.0, nmea::direction::NORTH);
		EXPECT_STREQ("$GPDTM,W84,,1.0000,N,0.0000,E,0.0,W84*6E", nmea::to_string(dtm).c_str());
	}
	{
		nmea::dtm dtm;
		dtm.set_lat_offset(1.0, nmea::direction::SOUTH);
		EXPECT_STREQ("$GPDTM,W84,,1.0000,S,0.0000,E,0.0,W84*73", nmea::to_string(dtm).c_str());
	}
}

TEST_F(Test_nmea_dtm, set_lat_offset_invalid_direction)
{
	nmea::dtm dtm;

	EXPECT_NO_THROW(dtm.set_lat_offset(1.0, nmea::direction::NORTH));
	EXPECT_NO_THROW(dtm.set_lat_offset(1.0, nmea::direction::SOUTH));
	EXPECT_ANY_THROW(dtm.set_lat_offset(1.0, nmea::direction::EAST));
	EXPECT_ANY_THROW(dtm.set_lat_offset(1.0, nmea::direction::WEST));
}

TEST_F(Test_nmea_dtm, set_lon_offset)
{
	{
		nmea::dtm dtm;
		dtm.set_lon_offset(1.0, nmea::direction::EAST);
		EXPECT_STREQ("$GPDTM,W84,,0.0000,N,1.0000,E,0.0,W84*6E", nmea::to_string(dtm).c_str());
	}
	{
		nmea::dtm dtm;
		dtm.set_lon_offset(1.0, nmea::direction::WEST);
		EXPECT_STREQ("$GPDTM,W84,,0.0000,N,1.0000,W,0.0,W84*7C", nmea::to_string(dtm).c_str());
	}
}

TEST_F(Test_nmea_dtm, set_lon_offset_invalid_direction)
{
	nmea::dtm dtm;

	EXPECT_ANY_THROW(dtm.set_lon_offset(1.0, nmea::direction::NORTH));
	EXPECT_ANY_THROW(dtm.set_lon_offset(1.0, nmea::direction::SOUTH));
	EXPECT_NO_THROW(dtm.set_lon_offset(1.0, nmea::direction::EAST));
	EXPECT_NO_THROW(dtm.set_lon_offset(1.0, nmea::direction::WEST));
}

}
