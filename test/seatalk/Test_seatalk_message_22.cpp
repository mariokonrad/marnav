#include <marnav/seatalk/message_22.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_seatalk_message_22 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_22, construction)
{
	seatalk::message_22 m;
}

TEST_F(Test_seatalk_message_22, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_22::parse({4, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_22::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_22, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_22::parse({0x22, 0x01, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_22::parse({0x22, 0x03, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_22, parse)
{
	struct test_case {
		seatalk::raw data;
		uint32_t distance;
	};

	std::vector<test_case> cases{
		{{0x22, 0x02, 0x00, 0x00, 0x00}, 0}, //   0.0 nm
		{{0x22, 0x02, 0x00, 0x00, 0x0f}, 0}, //   0.0 nm
		{{0x22, 0x02, 0x00, 0x00, 0xf0}, 0}, //   0.0 nm
		{{0x22, 0x02, 0x00, 0x01, 0x00}, 1}, //   0.1 nm
		{{0x22, 0x02, 0x00, 0x10, 0x00}, 16}, //   1.6 nm
		{{0x22, 0x02, 0x01, 0x00, 0x00}, 256}, //  25.6 nm
		{{0x22, 0x02, 0x10, 0x00, 0x00}, 4096}, // 409.6 nm
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_22::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_22>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::total_mileage, m->type());
		EXPECT_EQ(t.distance, m->get_distance());
	}
}

TEST_F(Test_seatalk_message_22, write_default)
{
	const seatalk::raw expected{0x22, 0x02, 0x00, 0x00, 0x00};
	seatalk::message_22 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_22, write_distance)
{
	const seatalk::raw expected{0x22, 0x02, 0x00, 0x01, 0x00};
	seatalk::message_22 m;
	m.set_distance(1);

	EXPECT_EQ(expected, m.get_data());
}
}
