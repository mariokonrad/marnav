#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/detail.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/vwr.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_nmea : public ::testing::Test
{
};

TEST_F(Test_nmea, checksum_to_string)
{
	EXPECT_STREQ("00", nmea::checksum_to_string(0x00).c_str());
	EXPECT_STREQ("01", nmea::checksum_to_string(0x01).c_str());
	EXPECT_STREQ("02", nmea::checksum_to_string(0x02).c_str());
	EXPECT_STREQ("04", nmea::checksum_to_string(0x04).c_str());
	EXPECT_STREQ("08", nmea::checksum_to_string(0x08).c_str());
	EXPECT_STREQ("10", nmea::checksum_to_string(0x10).c_str());
	EXPECT_STREQ("20", nmea::checksum_to_string(0x20).c_str());
	EXPECT_STREQ("40", nmea::checksum_to_string(0x40).c_str());
	EXPECT_STREQ("80", nmea::checksum_to_string(0x80).c_str());
	EXPECT_STREQ("5A", nmea::checksum_to_string(0x5a).c_str());
	EXPECT_STREQ("A5", nmea::checksum_to_string(0xa5).c_str());
	EXPECT_STREQ("FF", nmea::checksum_to_string(0xff).c_str());
}

TEST_F(Test_nmea, make_sentence_empty_string)
{
	EXPECT_ANY_THROW(nmea::make_sentence(""));
}

TEST_F(Test_nmea, make_sentence_no_start_token)
{
	EXPECT_ANY_THROW(nmea::make_sentence("1234567890"));
}

TEST_F(Test_nmea, make_sentence_to_short)
{
	EXPECT_ANY_THROW(nmea::make_sentence("12"));
}

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
		nmea::make_sentence("$IIYYY*59");
	} catch (std::exception & e) {
		EXPECT_STREQ("unknown regular tag in address: [IIYYY]", e.what());
	}
}

TEST_F(Test_nmea, make_sentence_vendor_extension)
{
	try {
		nmea::make_sentence("$PXXX*08");
	} catch (std::exception & e) {
		EXPECT_STREQ("unknown or malformed address field: [PXXX]", e.what());
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

TEST_F(Test_nmea, make_sentence_ignoring_checksum_ignored)
{
	const std::string raw = "$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*4A";

	auto s = nmea::make_sentence(raw, nmea::checksum_handling::ignore);

	EXPECT_TRUE(s != nullptr);
	EXPECT_TRUE(s->tag() == "VWR");
}

TEST_F(Test_nmea, make_sentence_ignoring_checksum_equal)
{
	const std::string raw_1 = "$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*4A";
	const std::string raw_2 = "$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*00";

	auto s1 = nmea::make_sentence(raw_1, nmea::checksum_handling::check);
	auto s2 = nmea::make_sentence(raw_2, nmea::checksum_handling::ignore);

	ASSERT_TRUE(s1 != nullptr);
	ASSERT_TRUE(s2 != nullptr);
	EXPECT_TRUE(s1->tag() == s2->tag());
}

TEST_F(Test_nmea, get_supported_sentences_str)
{
	auto v = nmea::get_supported_sentences_str();

	EXPECT_EQ(81u, v.size());
}

TEST_F(Test_nmea, get_supported_sentences_id)
{
	auto v = nmea::get_supported_sentences_id();

	EXPECT_EQ(81u, v.size());
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

TEST_F(Test_nmea, extract_id)
{
	EXPECT_EQ(nmea::sentence_id::BOD, nmea::extract_id("$GPBOD,,T,,M,,*47"));
	EXPECT_ANY_THROW(nmea::extract_id(""));
	EXPECT_ANY_THROW(nmea::extract_id("$"));
	EXPECT_ANY_THROW(nmea::extract_id("XGPBOD,,T,,M,,*47"));
	EXPECT_NO_THROW(nmea::extract_id("$GPBOD,,T,,M,,*XX"));
	EXPECT_NO_THROW(nmea::extract_id("!GPBOD,,T,,M,,*XX"));
	EXPECT_NO_THROW(nmea::extract_id("$GPBOD,"));
	EXPECT_ANY_THROW(nmea::extract_id("$GPBOD"));
	EXPECT_ANY_THROW(nmea::extract_id("$TMVTD"));
	EXPECT_ANY_THROW(nmea::extract_id("$TMVTD,,T,,M,,*47"));
}

TEST_F(Test_nmea, extract_id_tag_block)
{
	static const std::string t = "\\g:1-2-73874,n:157036,s:r003669945,c:1241544035*4A\\!AIVDM,"
								 "1,1,,B,15N4cJ`005Jrek0H@9n`DW5608EP,0*13";

	EXPECT_NO_THROW(nmea::extract_id(t));
	EXPECT_EQ(nmea::sentence_id::VDM, nmea::extract_id(t));
}

TEST_F(Test_nmea, make_sentence_tag_block)
{
	static const std::string t = "\\g:1-2-73874,n:157036,s:r003669945,c:1241544035*4A\\!AIVDM,"
								 "1,1,,B,15N4cJ`005Jrek0H@9n`DW5608EP,0*13";

	const auto s = nmea::make_sentence(t);

	EXPECT_TRUE(s != nullptr);
	EXPECT_TRUE(!s->get_tag_block().empty());
	EXPECT_STREQ(
		"g:1-2-73874,n:157036,s:r003669945,c:1241544035*4A", s->get_tag_block().c_str());
}

TEST_F(Test_nmea, parse_address_empty_string)
{
	EXPECT_ANY_THROW(nmea::detail::parse_address(std::string{}));
}

TEST_F(Test_nmea, parse_address_regular)
{
	EXPECT_NO_THROW(nmea::detail::parse_address("GPAAM"));
}

TEST_F(Test_nmea, parse_address_proprietary)
{
	{
		const auto result = nmea::detail::parse_address("PGRMZ");
		EXPECT_EQ(nmea::talker::none, std::get<0>(result));
		EXPECT_STREQ("PGRMZ", std::get<1>(result).c_str());
	}
	{
		const auto result = nmea::detail::parse_address("PGRMM");
		EXPECT_EQ(nmea::talker::none, std::get<0>(result));
		EXPECT_STREQ("PGRMM", std::get<1>(result).c_str());
	}
	{
		EXPECT_ANY_THROW(nmea::detail::parse_address("TMVTD"));
	}
	{
		EXPECT_ANY_THROW(nmea::detail::parse_address("XXYYY"));
	}
}

TEST_F(Test_nmea, parse_address_proprietary_unknown)
{
	try {
		nmea::detail::parse_address("PFOOBAR");
	} catch (std::invalid_argument & e) {
		EXPECT_STREQ("unknown or malformed address field: [PFOOBAR]", e.what());
	}
}

TEST_F(Test_nmea, parse_address_regular_invalid_length)
{
	try {
		nmea::detail::parse_address("GPFOOBAR");
	} catch (std::invalid_argument & e) {
		EXPECT_STREQ("unknown or malformed address field: [GPFOOBAR]", e.what());
	}

	try {
		nmea::detail::parse_address("GPRMZFOO");
	} catch (std::invalid_argument & e) {
		EXPECT_STREQ("unknown or malformed address field: [GPRMZFOO]", e.what());
	}
}

TEST_F(Test_nmea, parse_address_regular_unknown)
{
	try {
		nmea::detail::parse_address("GPXXX");
	} catch (std::invalid_argument & e) {
		EXPECT_STREQ("unknown regular tag in address: [GPXXX]", e.what());
	}
}
}
