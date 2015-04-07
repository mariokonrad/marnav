#include <gtest/gtest.h>
#include <seatalk/message_20.hpp>

namespace
{

using namespace marnav;

class Test_seatalk_message_20 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_20, construction) { seatalk::message_20 m; }

TEST_F(Test_seatalk_message_20, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_20::parse({3, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_20::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_20, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_20::parse({0x20, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_20::parse({0x20, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_20, parse)
{
	struct test_case {
		seatalk::raw data;
		uint16_t speed;
	};

	std::vector<test_case> cases{
		{{0x20, 0x01, 0x00, 0x00}, 0}, //  0.0 kn
		{{0x20, 0x01, 0x00, 0x01}, 1}, //  0.1 kn
		{{0x20, 0x01, 0x00, 0x0a}, 10}, //  1.0 kn
		{{0x20, 0x01, 0x00, 0x10}, 16}, //  1.6 kn
		{{0x20, 0x01, 0x00, 0x20}, 32}, //  3.2 kn
		{{0x20, 0x01, 0x00, 0x40}, 64}, //  6.4 kn
		{{0x20, 0x01, 0x00, 0x80}, 128}, // 12.8 kn
		{{0x20, 0x01, 0x00, 0xa0}, 160}, // 16.0 kn
		{{0x20, 0x01, 0x01, 0x00}, 256}, // 25.6 kn
		{{0x20, 0x01, 0x02, 0x00}, 512}, // 51.2 kn
		{{0x20, 0x01, 0x10, 0x10}, 4112}, // ludricus speed
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_20::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_20>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::speed_through_water, m->type());
		EXPECT_EQ(t.speed, m->get_speed());
	}
}

TEST_F(Test_seatalk_message_20, write_default)
{
	const seatalk::raw expected{0x20, 0x01, 0x00, 0x00};
	seatalk::message_20 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_20, write_speed)
{
	const seatalk::raw expected{0x20, 0x01, 0x00, 0x01};
	seatalk::message_20 m;
	m.set_speed(1);

	EXPECT_EQ(expected, m.get_data());
}
}
