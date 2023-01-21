#include <marnav/ais/message_12.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_ais_message_12 : public ::testing::Test
{
};

TEST_F(test_ais_message_12, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.emplace_back("<02:oP0kKcv0@<51C5PB5@?BDPD?P:?2?EB7PDB16693P381>>5<PikP", 0);

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_12>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(test_ais_message_12, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_12>(ais::raw(71)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_12>(ais::raw(1009)));
}

TEST_F(test_ais_message_12, encode_default_values)
{
	ais::message_12 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("<00000000000", v[0].first.c_str());
	EXPECT_EQ(0u, v[0].second);
}

TEST_F(test_ais_message_12, set_seqno_valid)
{
	for (auto i = 0u; i < 4u; ++i) {
		ais::message_12 m;
		m.set_seqno(i);
		EXPECT_EQ(i, m.get_seqno());
	}
}

TEST_F(test_ais_message_12, set_seqno_invalid)
{
	ais::message_12 m;
	EXPECT_ANY_THROW(m.set_seqno(4u));
}

TEST_F(test_ais_message_12, set_text_too_large)
{
	ais::message_12 m;
	m.set_text(std::string(ais::message_12::SIZE_TEXT_MAX + 1, '#'));
	EXPECT_EQ(ais::message_12::SIZE_TEXT_MAX, m.get_text().size());
}

static void test_string(
	const char * expected, const std::vector<std::pair<std::string, uint32_t>> & v)
{
	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);
	auto m = ais::message_cast<ais::message_12>(result);
	ASSERT_TRUE(m != nullptr);
	EXPECT_STREQ(expected, m->get_text().c_str());
}

TEST_F(test_ais_message_12, strings)
{
	test_string("PLEASE REPORT TO JOBOURG TRAFFIC CHANNEL 13 ",
		{{"<02:oP0kKcv0@<51C5PB5@?BDPD?P:?2?EB7PDB16693P381>>5<PikP", 0}});

	test_string("GOOD", {{"<5?SIj1;GbD07??4", 0}});

	test_string("THANX", {{"<5?SIj5Cp;NPD81>H0", 4}});

	test_string("MSG FROM 271002099", {{"<42Lati0W:Ov=C7P6B?=Pjoihhjhqq0", 2}});

	test_string("EP 531 CARS 80 TRACKS 103 MOTO 5 CREW 86",
		{{"<CR3B@<0TO3j5@PmkiP31BCPphPDB13;CPihkP=?D?PmP3B5GPpn", 0}});

	test_string("NI HAO.CALL TEST", {{"<9NS8O1ROcS0>9P81?f31<<PD5CD", 0}});

	test_string("GUD PM 2U N HAPI NEW YIR OL D BES FRM AL FUJAIRAH",
		{{"<39KdV8jIGtP7E4P@=PjEP>P81@9P>5GPI9BP?<P4P25CP6B=P1<P6E:19B1", 0}, {"80", 4}});
}
}
