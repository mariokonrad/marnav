#include <marnav/seatalk/message_11.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_seatalk_message_11 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_11, construction)
{
	seatalk::message_11 m;
}

TEST_F(Test_seatalk_message_11, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_11::parse({3, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_11::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_11, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_11::parse({0x11, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_11::parse({0x11, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_11, parse)
{
	struct test_case {
		seatalk::raw data;
		uint16_t speed;
		char unit;
	};

	std::vector<test_case> cases{
		{{0x11, 0x01, 0x00, 0x00}, 0, seatalk::unit::KNOT}, //  0.0 knotS
		{{0x11, 0x01, 0x00, 0x08}, 8, seatalk::unit::KNOT}, //  0.8 knotS
		{{0x11, 0x01, 0x08, 0x00}, 80, seatalk::unit::KNOT}, //  8.0 knotS
		{{0x11, 0x01, 0x08, 0x08}, 88, seatalk::unit::KNOT}, //  8.8 knotS
		{{0x11, 0x01, 0x0a, 0x00}, 100, seatalk::unit::KNOT}, // 10.0 knotS
		{{0x11, 0x01, 0x08, 0x0a}, 90, seatalk::unit::KNOT}, //  9.0 knotS
		{{0x11, 0x01, 0x08, 0x0b}, 91, seatalk::unit::KNOT}, //  9.1 knotS
		{{0x11, 0x01, 0x80, 0x00}, 0, seatalk::unit::MPS}, //  0.0 m/s
		{{0x11, 0x01, 0x80, 0x08}, 8, seatalk::unit::MPS}, //  0.8 m/s
		{{0x11, 0x01, 0x88, 0x00}, 80, seatalk::unit::MPS}, //  8.0 m/s
		{{0x11, 0x01, 0x88, 0x08}, 88, seatalk::unit::MPS}, //  8.8 m/s
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_11::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_11>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::apparent_wind_speed, m->type());
		EXPECT_EQ(t.speed, m->get_speed());
		EXPECT_EQ(t.unit, m->get_unit());
	}
}

TEST_F(Test_seatalk_message_11, write_default)
{
	const seatalk::raw expected{0x11, 0x01, 0x00, 0x00};
	seatalk::message_11 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_11, write_unit)
{
	const seatalk::raw expected{0x11, 0x01, 0x80, 0x00};
	seatalk::message_11 m;
	m.set_unit(seatalk::unit::MPS);

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_11, write_speed)
{
	const seatalk::raw expected{0x11, 0x01, 0x00, 0x01};
	seatalk::message_11 m;
	m.set_speed(1);

	EXPECT_EQ(expected, m.get_data());
}
}
