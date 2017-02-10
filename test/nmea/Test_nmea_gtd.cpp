#include <gtest/gtest.h>
#include <marnav/nmea/gtd.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_gtd : public ::testing::Test
{
};

TEST_F(Test_nmea_gtd, contruction)
{
	EXPECT_NO_THROW(nmea::gtd gtd);
}

TEST_F(Test_nmea_gtd, properties)
{
	nmea_sentence_traits<nmea::gtd>();
}

TEST_F(Test_nmea_gtd, parse)
{
	auto s = nmea::make_sentence("$GPGTD,1.0,2.0,3.0,4.0,5.0*43");
	ASSERT_NE(nullptr, s);

	auto gtd = nmea::sentence_cast<nmea::gtd>(s);
	ASSERT_NE(nullptr, gtd);
}

TEST_F(Test_nmea_gtd, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::gtd>(nmea::talker_id::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::gtd>(nmea::talker_id::none, {6, "@"}));
}

TEST_F(Test_nmea_gtd, empty_to_string)
{
	nmea::gtd gtd;

	EXPECT_STREQ("$GPGTD,0,0,0,0,0*5C", nmea::to_string(gtd).c_str());
}

TEST_F(Test_nmea_gtd, set_time_diff)
{
	nmea::gtd gtd;
	gtd.set_time_diff(0, 1.0);
	gtd.set_time_diff(1, 2.0);
	gtd.set_time_diff(2, 3.0);
	gtd.set_time_diff(3, 4.0);
	gtd.set_time_diff(4, 5.0);

	EXPECT_STREQ("$GPGTD,1,2,3,4,5*5D", nmea::to_string(gtd).c_str());
}

TEST_F(Test_nmea_gtd, set_time_diff_invalid_index)
{
	nmea::gtd gtd;

	EXPECT_ANY_THROW(gtd.set_time_diff(-1, 0.0));
	EXPECT_ANY_THROW(gtd.set_time_diff(5, 0.0));
	EXPECT_ANY_THROW(gtd.set_time_diff(nmea::gtd::max_time_diffs, 0.0));
}

TEST_F(Test_nmea_gtd, get_time_diff)
{
	auto s = nmea::make_sentence("$GPGTD,1.0,2.0,3.0,4.0,5.0*43");
	ASSERT_NE(nullptr, s);

	auto gtd = nmea::sentence_cast<nmea::gtd>(s);
	ASSERT_NE(nullptr, gtd);

	EXPECT_NEAR(1.0, gtd->get_time_diff(0), 1e-8);
	EXPECT_NEAR(2.0, gtd->get_time_diff(1), 1e-8);
	EXPECT_NEAR(3.0, gtd->get_time_diff(2), 1e-8);
	EXPECT_NEAR(4.0, gtd->get_time_diff(3), 1e-8);
	EXPECT_NEAR(5.0, gtd->get_time_diff(4), 1e-8);
}

TEST_F(Test_nmea_gtd, get_time_diff_invalid_index)
{
	nmea::gtd gtd;

	EXPECT_ANY_THROW(gtd.get_time_diff(-1));
	EXPECT_ANY_THROW(gtd.get_time_diff(5));
	EXPECT_ANY_THROW(gtd.get_time_diff(nmea::gtd::max_time_diffs));
}
}
