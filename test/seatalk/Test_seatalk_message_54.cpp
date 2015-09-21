#include <gtest/gtest.h>
#include <marnav/seatalk/message_54.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_54 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		uint8_t h;
		uint8_t m;
		uint8_t s;
	};
};

TEST_F(Test_seatalk_message_54, construction) { EXPECT_NO_THROW(message_54 m); }

TEST_F(Test_seatalk_message_54, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_54::parse({3, 0x00}));
	EXPECT_ANY_THROW(message_54::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_54, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_54::parse({0x54, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_54::parse({0x54, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_54, parse)
{
	const std::vector<test_case> cases{
		{{0x54, 0x01, 0x00, 0x00}, 0, 0, 0},
	};

	for (auto const & t : cases) {
		auto generic_message = message_54::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_54>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.h, m->get_hour());
		EXPECT_EQ(t.m, m->get_minute());
		EXPECT_EQ(t.s, m->get_second());
	}
}

TEST_F(Test_seatalk_message_54, write_default)
{
	const raw expected{0x54, 0x01, 0x00, 0x00};
	message_54 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_54, set_time)
{
	const std::vector<test_case> cases{
		{{0x54, 0x01, 0x00, 0x00}, 0, 0, 0},
	};

	for (auto const & t : cases) {
		message_54 m;
		m.set_time(t.h, t.m, t.s);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw);
	}
}
}
