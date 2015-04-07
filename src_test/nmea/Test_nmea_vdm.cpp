#include <gtest/gtest.h>
#include <nmea/vdm.hpp>
#include <nmea/mtw.hpp>
#include <nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_vdm : public ::testing::Test
{
};

TEST_F(Test_nmea_vdm, contruction) { nmea::vdm vdm; }

TEST_F(Test_nmea_vdm, size) { EXPECT_EQ(56u, sizeof(nmea::vdm)); }

TEST_F(Test_nmea_vdm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::vdm::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::vdm::parse("@@", {7, "@"}));
}

TEST_F(Test_nmea_vdm, parse_1)
{
	auto s = nmea::make_sentence("!AIVDM,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5C");
	ASSERT_NE(nullptr, s);

	auto vdm = nmea::sentence_cast<nmea::vdm>(s);
	ASSERT_NE(nullptr, vdm);

	auto fragments = vdm->get_n_fragments();
	EXPECT_EQ(1u, fragments);

	auto fragment = vdm->get_fragment();
	EXPECT_EQ(1u, fragment);

	auto payload = vdm->get_payload();
	EXPECT_STREQ("177KQJ5000G?tO`K>RA1wUbN0TKH", payload.c_str());
}

TEST_F(Test_nmea_vdm, parse_2)
{
	auto s0 = nmea::make_sentence(
		"!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E");
	ASSERT_NE(nullptr, s0);

	auto vdm0 = nmea::sentence_cast<nmea::vdm>(s0);
	ASSERT_NE(nullptr, vdm0);

	auto s1 = nmea::make_sentence("!AIVDM,2,2,3,B,1@0000000000000,2*55");
	ASSERT_NE(nullptr, s1);

	auto vdm1 = nmea::sentence_cast<nmea::vdm>(s1);
	ASSERT_NE(nullptr, vdm1);
}

TEST_F(Test_nmea_vdm, empty_to_string)
{
	nmea::vdm vdm;

	EXPECT_STREQ("!AIVDM,0,0,,B,,0*25", nmea::to_string(vdm).c_str());
}

TEST_F(Test_nmea_vdm, collect_payload)
{
	std::vector<std::unique_ptr<nmea::sentence>> v;

	v.push_back(nmea::make_sentence(
		"!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E"));
	v.push_back(nmea::make_sentence("!AIVDM,2,2,3,B,1@0000000000000,2*55"));

	auto result = nmea::collect_payload(v.begin(), v.end());

	ASSERT_EQ(2u, result.size());
	EXPECT_EQ(0, result[0].second);
	EXPECT_EQ(2, result[1].second);
	EXPECT_STREQ(
		"55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", result[0].first.c_str());
	EXPECT_STREQ("1@0000000000000", result[1].first.c_str());
}

TEST_F(Test_nmea_vdm, collect_payload_wrong_sentence)
{
	std::vector<std::unique_ptr<nmea::sentence>> v;
	v.push_back(std::unique_ptr<nmea::sentence>(new nmea::mtw));

	EXPECT_ANY_THROW(nmea::collect_payload(v.begin(), v.end()));
}
}

