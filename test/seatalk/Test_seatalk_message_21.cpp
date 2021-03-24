#include <marnav/seatalk/message_21.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_seatalk_message_21 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_21, construction)
{
	seatalk::message_21 m;
}

TEST_F(Test_seatalk_message_21, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_21::parse({4, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_21::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_21, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_21::parse({0x21, 0x01, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_21::parse({0x21, 0x03, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_21, parse)
{
	struct test_case {
		seatalk::raw data;
		uint32_t distance;
	};

	std::vector<test_case> cases{
		{{0x21, 0x02, 0x00, 0x00, 0x00}, 0}, //   0.00 nm
		{{0x21, 0x02, 0x00, 0x00, 0x01}, 1}, //   0.01 nm
		{{0x21, 0x02, 0x00, 0x00, 0x10}, 0}, //   0.00 nm
		{{0x21, 0x02, 0x00, 0x00, 0xf0}, 0}, //   0.00 nm
		{{0x21, 0x02, 0x00, 0x01, 0x00}, 16}, //   0.16 nm
		{{0x21, 0x02, 0x00, 0x10, 0x00}, 256}, //   2.56 nm
		{{0x21, 0x02, 0x01, 0x00, 0x00}, 4096}, //  40.96 nm
		{{0x21, 0x02, 0x10, 0x00, 0x00}, 65536}, // 655.36 nm
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_21::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_21>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::trip_mileage, m->type());
		EXPECT_EQ(t.distance, m->get_distance());
	}
}

TEST_F(Test_seatalk_message_21, write_default)
{
	const seatalk::raw expected{0x21, 0x02, 0x00, 0x00, 0x00};
	seatalk::message_21 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_21, write_distance)
{
	const seatalk::raw expected{0x21, 0x02, 0x00, 0x00, 0x01};
	seatalk::message_21 m;
	m.set_distance(1);

	EXPECT_EQ(expected, m.get_data());
}
}
