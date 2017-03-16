#include <gtest/gtest.h>
#include <marnav/ais/message_14.hpp>
#include <marnav/ais/ais.hpp>

namespace
{
using namespace marnav;

class Test_ais_message_14 : public ::testing::Test
{
};

TEST_F(Test_ais_message_14, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v{{">5?Per18=HB1U:1@E=B0m<L", 2}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_14>(result);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_ais_message_14, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_14>(ais::raw{39}));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_14>(ais::raw{1009}));
}

TEST_F(Test_ais_message_14, encode_default_values)
{
	ais::message_14 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ(">000000", v[0].first.c_str());
	EXPECT_EQ(2u, v[0].second);
}

TEST_F(Test_ais_message_14, set_text_too_large)
{
	ais::message_14 m;
	m.set_text(std::string(ais::message_14::SIZE_TEXT_MAX + 1, '#'));
	EXPECT_EQ(ais::message_14::SIZE_TEXT_MAX, m.get_text().size());
}

static void test_string(
	const char * expected, const std::vector<std::pair<std::string, uint32_t>> & v)
{
	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);
	auto m = ais::message_cast<ais::message_14>(result);
	ASSERT_TRUE(m != nullptr);
	EXPECT_STREQ(expected, m->get_text().c_str());
}

TEST_F(Test_ais_message_14, strings)
{
	test_string("RCVD YR TEST MSG", {{">5?Per18=HB1U:1@E=B0m<L", 2}});

	test_string("EP228 IX48 FG3 DK7 PL56.", {{">3R1p10E3;;R0USCR0HO>0@gN10kGJp", 2}});

	test_string("TEST", {{">4aDT81@E=@", 2}});
}
}
