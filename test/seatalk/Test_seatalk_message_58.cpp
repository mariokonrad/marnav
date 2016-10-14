#include <gtest/gtest.h>
#include <marnav/seatalk/message_58.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_58 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		marnav::geo::position pos;
	};

	const std::vector<test_case> cases{
		{{0x58, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {{0.0}, {0.0}}},
		{{0x58, 0x25, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}, {{1.0}, {0.0}}},
		{{0x58, 0x25, 0x01, 0x75, 0x30, 0x00, 0x00, 0x00}, {{1.5}, {0.0}}},
		{{0x58, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}, {{2.0}, {0.0}}},
		{{0x58, 0x25, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, {{0.0}, {1.0}}},
		{{0x58, 0x25, 0x00, 0x00, 0x00, 0x01, 0x75, 0x30}, {{0.0}, {1.5}}},
		{{0x58, 0x25, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, {{0.0}, {2.0}}},
	};
};

TEST_F(Test_seatalk_message_58, construction)
{
	EXPECT_NO_THROW(message_58 m);
}

TEST_F(Test_seatalk_message_58, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_58::parse({7, 0x00}));
	EXPECT_ANY_THROW(message_58::parse({9, 0x00}));
}

TEST_F(Test_seatalk_message_58, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_58::parse({0x58, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_58::parse({0x58, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_58, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_58::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_58>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.pos, m->get_pos());
	}
}

TEST_F(Test_seatalk_message_58, write_default)
{
	const raw expected{0x58, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	message_58 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_58, set_position)
{
	for (auto const & t : cases) {
		message_58 m;
		m.set_pos(t.pos);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw);
	}
}
}
