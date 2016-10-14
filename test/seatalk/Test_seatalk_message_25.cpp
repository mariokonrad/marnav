#include <gtest/gtest.h>
#include <marnav/seatalk/message_25.hpp>

namespace
{

using namespace marnav;

class Test_seatalk_message_25 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_25, construction)
{
	seatalk::message_25 m;
}

TEST_F(Test_seatalk_message_25, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_25::parse({6, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_25::parse({8, 0x00}));
}

TEST_F(Test_seatalk_message_25, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_25::parse({0x25, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_25::parse({0x25, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_25, parse)
{
	struct test_case {
		seatalk::raw data;
		uint32_t total;
		uint32_t trip;
	};

	std::vector<test_case> cases{
		{{0x25, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00}, 0, 0},
		{{0x25, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01}, 0, 65536}, // trip
		{{0x25, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10}, 0, 0}, // trip
		{{0x25, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00}, 0, 256}, // trip
		{{0x25, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00}, 0, 4096}, // trip
		{{0x25, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00}, 0, 1}, // trip
		{{0x25, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00}, 0, 16}, // trip
		{{0x25, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00}, 256, 0}, // total
		{{0x25, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00}, 4096, 0}, // total
		{{0x25, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00}, 1, 0}, // total
		{{0x25, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00}, 16, 0}, // total
		{{0x25, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00}, 65536, 0}, // total
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_25::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_25>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::total_and_trip_log, m->type());
		EXPECT_EQ(t.total, m->get_total());
		EXPECT_EQ(t.trip, m->get_trip());
	}
}

TEST_F(Test_seatalk_message_25, write_default)
{
	const seatalk::raw expected{0x25, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};
	seatalk::message_25 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_25, write_total)
{
	const seatalk::raw expected{0x25, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00};
	seatalk::message_25 m;
	m.set_total(1);

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_25, write_trip)
{
	const seatalk::raw expected{0x25, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00};
	seatalk::message_25 m;
	m.set_trip(1);

	EXPECT_EQ(expected, m.get_data());
}
}
