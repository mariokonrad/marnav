#include <marnav/seatalk/message_54.hpp>
#include <gtest/gtest.h>

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

	const std::vector<test_case> cases{
		{{0x54, 0x01, 0x00, 0x00}, 0, 0, 0},
		{{0x54, 0x01, 0x00, 0x01}, 1, 0, 0},
		{{0x54, 0x01, 0x00, 0x10}, 16, 0, 0},
		{{0x54, 0x01, 0x04, 0x00}, 0, 1, 0},
		{{0x54, 0x01, 0x08, 0x00}, 0, 2, 0},
		{{0x54, 0x01, 0x10, 0x00}, 0, 4, 0},
		{{0x54, 0x01, 0x20, 0x00}, 0, 8, 0},
		{{0x54, 0x01, 0x40, 0x00}, 0, 16, 0},
		{{0x54, 0x01, 0x80, 0x00}, 0, 32, 0},
		{{0x54, 0x11, 0x00, 0x00}, 0, 0, 1},
		{{0x54, 0x21, 0x00, 0x00}, 0, 0, 2},
		{{0x54, 0x41, 0x00, 0x00}, 0, 0, 4},
		{{0x54, 0x81, 0x00, 0x00}, 0, 0, 8},
		{{0x54, 0x01, 0x01, 0x00}, 0, 0, 16},
		{{0x54, 0x01, 0x02, 0x00}, 0, 0, 32},
	};
};

TEST_F(Test_seatalk_message_54, construction)
{
	EXPECT_NO_THROW(message_54 m);
}

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
	for (auto const & t : cases) {
		message_54 m;
		m.set_time(t.h, t.m, t.s);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw);
	}
}
}
