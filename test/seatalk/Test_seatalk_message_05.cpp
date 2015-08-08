#include <gtest/gtest.h>
#include <marnav/seatalk/message_05.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_05 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_05, construction) { message_05 m; }

TEST_F(Test_seatalk_message_05, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_05::parse({5, 0x00}));
	EXPECT_ANY_THROW(message_05::parse({7, 0x00}));
}

TEST_F(Test_seatalk_message_05, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_05::parse({0x05, 0x02, 0x00, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_05::parse({0x05, 0x04, 0x00, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_05, parse)
{
	struct test_case {
		raw data;
		message_05::side_id side;
		int16_t rpm;
		int8_t percent_pitch;
	};

	std::vector<test_case> cases{
		{{0x05, 0x03, 0x00, 0x00, 0x00, 0x00}, message_05::side_id::undefined, 0, 0},
		{{0x05, 0x03, 0x01, 0x00, 0x00, 0x00}, message_05::side_id::starboard, 0, 0},
		{{0x05, 0x03, 0x02, 0x00, 0x00, 0x00}, message_05::side_id::port, 0, 0},
		{{0x05, 0x03, 0x00, 0x00, 0x00, 0x00}, message_05::side_id::undefined, 0, 0},
		{{0x05, 0x03, 0x00, 0x00, 0x00, 0x01}, message_05::side_id::undefined, 0, 1},
		{{0x05, 0x03, 0x00, 0x00, 0x00, 0xff}, message_05::side_id::undefined, 0, -1},
		{{0x05, 0x03, 0x00, 0x00, 0x01, 0x00}, message_05::side_id::undefined, 1, 0},
		{{0x05, 0x03, 0x01, 0x00, 0x02, 0x00}, message_05::side_id::starboard, 2, 0},
		{{0x05, 0x03, 0x02, 0x00, 0x03, 0x00}, message_05::side_id::port, 3, 0},
	};

	for (auto const & t : cases) {
		auto generic_message = message_05::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);

		if (!generic_message)
			continue;

		auto m = message_cast<message_05>(generic_message);
		EXPECT_TRUE(m != nullptr);

		if (!m)
			continue;

		EXPECT_EQ(message_id::engine_rpm_and_pitch, m->type());
		EXPECT_EQ(t.side, m->get_side());
		EXPECT_EQ(t.rpm, m->get_rpm());
		EXPECT_EQ(t.percent_pitch, m->get_percent_pitch());
	}
}

TEST_F(Test_seatalk_message_05, write_default)
{
	const raw expected{0x05, 0x03, 0x00, 0x00, 0x00, 0x00};
	message_05 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_05, write_different_sides)
{
	{
		const raw expected{0x05, 0x03, 0x00, 0x00, 0x00, 0x00};
		message_05 m;
		m.set_side(message_05::side_id::undefined);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x05, 0x03, 0x01, 0x00, 0x00, 0x00};
		message_05 m;
		m.set_side(message_05::side_id::starboard);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x05, 0x03, 0x02, 0x00, 0x00, 0x00};
		message_05 m;
		m.set_side(message_05::side_id::port);
		EXPECT_EQ(expected, m.get_data());
	}
}

TEST_F(Test_seatalk_message_05, write_percent_pitch)
{
	{
		const raw expected{0x05, 0x03, 0x00, 0x00, 0x00, 0x01};
		message_05 m;
		m.set_percent_pitch(1);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x05, 0x03, 0x00, 0x00, 0x00, 0x02};
		message_05 m;
		m.set_percent_pitch(2);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x05, 0x03, 0x00, 0x00, 0x00, 0xff};
		message_05 m;
		m.set_percent_pitch(-1);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x05, 0x03, 0x00, 0x00, 0x00, 0xfe};
		message_05 m;
		m.set_percent_pitch(-2);
		EXPECT_EQ(expected, m.get_data());
	}
}
}
