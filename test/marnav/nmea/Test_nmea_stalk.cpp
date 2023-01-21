#include <marnav/nmea/stalk.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_nmea_stalk : public ::testing::Test
{
};

TEST_F(test_nmea_stalk, contruction)
{
	EXPECT_NO_THROW(nmea::stalk stalk);
}

TEST_F(test_nmea_stalk, properties)
{
	nmea_sentence_traits<nmea::stalk>();
}

TEST_F(test_nmea_stalk, parse)
{
	auto s = nmea::make_sentence("$STALK,00,01,02,03,04,05*40");
	ASSERT_NE(nullptr, s);

	auto stalk = nmea::sentence_cast<nmea::stalk>(s);
	ASSERT_NE(nullptr, stalk);

	auto data = stalk->get_data();
	EXPECT_EQ(6u, data.size());
}

TEST_F(test_nmea_stalk, parse_minimum_bytes)
{
	auto s = nmea::make_sentence("$STALK,ff*6D");
	ASSERT_NE(nullptr, s);

	auto stalk = nmea::sentence_cast<nmea::stalk>(s);
	ASSERT_NE(nullptr, stalk);

	auto data = stalk->get_data();
	EXPECT_EQ(nmea::stalk::MIN_FIELDS, data.size());
}

TEST_F(test_nmea_stalk, parse_maximum_bytes)
{
	auto s = nmea::make_sentence(
		"$STALK,00,01,02,03,04,05,06,07,08,09,0a,0b,0c,0d,0e,0f,10,11,12,13,14,15,16,17*47");
	ASSERT_NE(nullptr, s);

	auto stalk = nmea::sentence_cast<nmea::stalk>(s);
	ASSERT_NE(nullptr, stalk);

	auto data = stalk->get_data();
	EXPECT_EQ(nmea::stalk::MAX_FIELDS, data.size());
}

TEST_F(test_nmea_stalk, parse_less_than_minimum_bytes)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$STALK*41"));
}

TEST_F(test_nmea_stalk, parse_more_than_maximum_bytes)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$STALK,00,01,02,03,04,05,06,07,08,09,0a,0b,0c,0d,0e,"
										 "0f,10,11,12,13,14,15,16,17,18*7E"));
}

TEST_F(test_nmea_stalk, invalid_data_bytes)
{
	EXPECT_THROW(nmea::make_sentence("$STALK,0*5D"), std::invalid_argument);
	EXPECT_THROW(nmea::make_sentence("$STALK,f*0B"), std::invalid_argument);
	EXPECT_THROW(nmea::make_sentence("$STALK,000*5D"), std::invalid_argument);
	EXPECT_THROW(nmea::make_sentence("$STALK,fff*0B"), std::invalid_argument);
}

TEST_F(test_nmea_stalk, empty_to_string)
{
	nmea::stalk s;
	EXPECT_THROW(nmea::to_string(s), std::runtime_error);
}

TEST_F(test_nmea_stalk, minimum_data_to_string)
{
	nmea::stalk s;
	nmea::stalk::raw data;
	data.push_back(0);
	s.set_data(data);

	EXPECT_STREQ("$STALK,00*6D", nmea::to_string(s).c_str());
}

TEST_F(test_nmea_stalk, maximum_data_to_string)
{
	nmea::stalk s;
	nmea::stalk::raw data;
	for (auto i = 0u; i < nmea::stalk::MAX_FIELDS; ++i)
		data.push_back(i);
	s.set_data(data);

	EXPECT_STREQ(
		"$STALK,00,01,02,03,04,05,06,07,08,09,0a,0b,0c,0d,0e,0f,10,11,12,13,14,15,16,17*47",
		nmea::to_string(s).c_str());
}
}
