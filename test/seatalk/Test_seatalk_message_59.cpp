#include <gtest/gtest.h>
#include <marnav/seatalk/message_59.hpp>

namespace
{
using namespace marnav::seatalk;

using mode = marnav::seatalk::message_59::mode;

class Test_seatalk_message_59 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		uint8_t hours;
		uint8_t minutes;
		uint8_t seconds;
		mode m;
	};

	const std::vector<test_case> cases{
		{{0x59, 0x22, 0x00, 0x00, 0x00}, 0, 0, 0, mode::up_and_start},
		{{0x59, 0x22, 0x01, 0x00, 0x00}, 0, 0, 1, mode::up_and_start},
		{{0x59, 0x22, 0x00, 0x01, 0x00}, 0, 1, 0, mode::up_and_start},
		{{0x59, 0x22, 0x00, 0x00, 0x01}, 1, 0, 0, mode::up_and_start},
		{{0x59, 0x22, 0x00, 0x00, 0x40}, 0, 0, 0, mode::down},
		{{0x59, 0x22, 0x00, 0x00, 0x80}, 0, 0, 0, mode::down_and_start},
	};
};

TEST_F(Test_seatalk_message_59, construction)
{
	EXPECT_NO_THROW(message_59 m);
}

TEST_F(Test_seatalk_message_59, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_59::parse({4, 0x00}));
	EXPECT_ANY_THROW(message_59::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_59, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_59::parse({0x59, 0x21, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_59::parse({0x59, 0x23, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_59, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_59::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_59>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.hours, m->get_hours());
		EXPECT_EQ(t.minutes, m->get_minutes());
		EXPECT_EQ(t.seconds, m->get_seconds());
		EXPECT_EQ(t.m, m->get_mode());
	}
}

TEST_F(Test_seatalk_message_59, write_default)
{
	const raw expected{0x59, 0x22, 0x00, 0x00, 0x00};
	message_59 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_59, set_timer)
{
	for (auto const & t : cases) {
		message_59 m;
		m.set_timer(t.hours, t.minutes, t.seconds, t.m);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw);
	}
}

TEST_F(Test_seatalk_message_59, set_timer_boundaries)
{
	{
		message_59 m;
		m.set_timer(10, 0, 0, mode::up_and_start);
		EXPECT_EQ(9u, m.get_hours());
	}
	{
		message_59 m;
		m.set_timer(0, 60, 0, mode::up_and_start);
		EXPECT_EQ(59u, m.get_minutes());
	}
	{
		message_59 m;
		m.set_timer(0, 0, 60, mode::up_and_start);
		EXPECT_EQ(59u, m.get_seconds());
	}
}
}
