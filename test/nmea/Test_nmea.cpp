#include <gtest/gtest.h>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea : public ::testing::Test
{
};

TEST_F(Test_nmea, make_sentence_empty_string) { EXPECT_ANY_THROW(nmea::make_sentence("")); }

TEST_F(Test_nmea, checksum_error_construction)
{
	nmea::checksum_error e(0x12, 0x34);
}

TEST_F(Test_nmea, make_sentence_no_start_token)
{
	EXPECT_ANY_THROW(nmea::make_sentence("1234567890"));
}

TEST_F(Test_nmea, make_sentence_to_short) { EXPECT_ANY_THROW(nmea::make_sentence("12")); }

TEST_F(Test_nmea, make_sentence_no_end_token)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPMTW,,1E"));
}

TEST_F(Test_nmea, make_sentence_invalid_checksum)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$GPMTW,,*1E"));
}

TEST_F(Test_nmea, make_sentence_minimal_possible_sentence)
{
	try {
		nmea::make_sentence("$XXYYY*59");
	} catch (std::exception & e) {
		EXPECT_STREQ("unknown sentence in nmea/instantiate_sentence: YYY", e.what());
	}
}

TEST_F(Test_nmea, make_sentence_vendor_extension)
{
	try {
		nmea::make_sentence("$PXXX*08");
	} catch (std::exception & e) {
		EXPECT_STREQ("unknown sentence in nmea/instantiate_sentence: PXXX", e.what());
	}
}

TEST_F(Test_nmea, make_sentence_invalid_checksum_what)
{
	try {
		nmea::make_sentence("$GPMTW,,*1E");
	} catch (nmea::checksum_error & e) {
		EXPECT_STREQ("checksum error (actual:59, expected:1E)", e.what());
	}
}

TEST_F(Test_nmea, make_sentence_unknown_sentence)
{
	EXPECT_ANY_THROW(nmea::make_sentence("$XX???,1,2,3*23"));
}

TEST_F(Test_nmea, get_supported_sentences_str)
{
	auto v = nmea::get_supported_sentences_str();

	EXPECT_EQ(61u, v.size());
}

TEST_F(Test_nmea, get_supported_sentences_id)
{
	auto v = nmea::get_supported_sentences_id();

	EXPECT_EQ(61u, v.size());
}

TEST_F(Test_nmea, tag_to_id)
{
	auto id = nmea::tag_to_id("BOD");

	EXPECT_EQ(nmea::sentence_id::BOD, id);
}

TEST_F(Test_nmea, tag_to_id_invalid_tag)
{
	EXPECT_ANY_THROW(nmea::tag_to_id("???"));
}

TEST_F(Test_nmea, to_string_sentence_id)
{
	auto tag = nmea::to_string(nmea::sentence_id::BOD);

	EXPECT_STREQ("BOD", tag.c_str());
}

TEST_F(Test_nmea, to_string_sentence_id_invalid_id)
{
	EXPECT_ANY_THROW(nmea::to_string(static_cast<nmea::sentence_id>(-1)));
}

}
