#include <gtest/gtest.h>
#include <marnav/nmea/glc.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_glc : public ::testing::Test
{
};

TEST_F(Test_nmea_glc, contruction) { EXPECT_NO_THROW(nmea::glc glc); }

TEST_F(Test_nmea_glc, properties) { nmea_sentence_traits<nmea::glc>(); }

TEST_F(Test_nmea_glc, parse)
{
	auto s = nmea::make_sentence("$GPGLC,1,1,A,1,A,2,A,3,A,4,V,,*21");
	ASSERT_NE(nullptr, s);

	auto glc = nmea::sentence_cast<nmea::glc>(s);
	ASSERT_NE(nullptr, glc);
}

TEST_F(Test_nmea_glc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::glc::parse("@@", {12, "@"}));
	EXPECT_ANY_THROW(nmea::glc::parse("@@", {14, "@"}));
}

TEST_F(Test_nmea_glc, empty_to_string)
{
	nmea::glc glc;

	EXPECT_STREQ("$GPGLC,0,0,V,,,,,,,,,,*25", nmea::to_string(glc).c_str());
}

TEST_F(Test_nmea_glc, set_time_diff_invalid_index)
{
	nmea::glc glc;

	EXPECT_ANY_THROW(glc.set_time_diff(-1, {0.0, nmea::status::ok}));
	EXPECT_ANY_THROW(glc.set_time_diff(5, {0.0, nmea::status::ok}));
}

TEST_F(Test_nmea_glc, get_time_diff_invalid_index)
{
	nmea::glc glc;

	EXPECT_ANY_THROW(glc.get_time_diff(-1));
	EXPECT_ANY_THROW(glc.get_time_diff(5));
}

TEST_F(Test_nmea_glc, set_time_diff)
{
	{
		nmea::glc glc;
		glc.set_time_diff(0, {1.0, nmea::status::ok});
		EXPECT_STREQ("$GPGLC,0,0,V,1,A,,,,,,,,*55", nmea::to_string(glc).c_str());
	}
	{
		nmea::glc glc;
		glc.set_time_diff(1, {1.0, nmea::status::ok});
		EXPECT_STREQ("$GPGLC,0,0,V,,,1,A,,,,,,*55", nmea::to_string(glc).c_str());
	}
	{
		nmea::glc glc;
		glc.set_time_diff(2, {1.0, nmea::status::ok});
		EXPECT_STREQ("$GPGLC,0,0,V,,,,,1,A,,,,*55", nmea::to_string(glc).c_str());
	}
	{
		nmea::glc glc;
		glc.set_time_diff(3, {1.0, nmea::status::ok});
		EXPECT_STREQ("$GPGLC,0,0,V,,,,,,,1,A,,*55", nmea::to_string(glc).c_str());
	}
	{
		nmea::glc glc;
		glc.set_time_diff(4, {1.0, nmea::status::ok});
		EXPECT_STREQ("$GPGLC,0,0,V,,,,,,,,,1,A*55", nmea::to_string(glc).c_str());
	}
}

TEST_F(Test_nmea_glc, get_time_diff)
{
	auto s = nmea::make_sentence("$GPGLC,1,1,A,1,A,2,A,3,A,4,V,,*21");
	ASSERT_NE(nullptr, s);

	auto glc = nmea::sentence_cast<nmea::glc>(s);
	ASSERT_NE(nullptr, glc);

	auto const t = glc->get_time_diff(0);
	EXPECT_TRUE(static_cast<bool>(t));
	EXPECT_NEAR(1.0, t->diff, 1e-8);
	EXPECT_EQ(nmea::status::ok, t->status);
}
}
