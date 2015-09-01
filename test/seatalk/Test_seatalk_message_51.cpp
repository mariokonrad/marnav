#include <gtest/gtest.h>
#include <marnav/seatalk/message_51.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_51 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_51, construction) { EXPECT_NO_THROW(message_51 m); }

TEST_F(Test_seatalk_message_51, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_51::parse({4, 0x00}));
	EXPECT_ANY_THROW(message_51::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_51, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_51::parse({0x51, 0x01, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_51::parse({0x51, 0x03, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_51, parse)
{
	struct test_case {
		raw data;
	};

	const std::vector<test_case> cases{
		{{0x51, 0x02, 0x00, 0x00, 0x00}},
		{{0x51, 0x02, 0x0a, 0x00, 0x00}},
		{{0x51, 0x02, 0x00, 0x01, 0x00}},
		{{0x51, 0x02, 0x00, 0x00, 0x01}},
	};

	for (auto const & t : cases) {
		auto generic_message = message_51::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_51>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
	}
}

TEST_F(Test_seatalk_message_51, write_default)
{
	const raw expected{0x51, 0x02, 0x00, 0x80, 0x00};
	message_51 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_51, set_lon)
{
	using longitude = marnav::geo::longitude;
	using hemisphere = longitude::hemisphere;

	struct test_case {
		longitude lon;
		raw expected;
	};

	const std::vector<test_case> cases{
		{{0, 0, 0, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x80, 0x00}},
		{{0, 0, 0, hemisphere::EAST}, {0x51, 0x02, 0x00, 0x80, 0x00}},
		{{1, 0, 0, hemisphere::WEST}, {0x51, 0x02, 0x01, 0x00, 0x00}},
		{{1, 0, 0, hemisphere::EAST}, {0x51, 0x02, 0x01, 0x80, 0x00}},
		{{0, 1, 0, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x00, 0x64}},
		{{0, 0, 1, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x00, 0x01}},
		{{0, 0, 2, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x00, 0x03}},
		{{0, 0, 3, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x00, 0x05}},
		{{0, 1, 59, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x00, 0xc6}},
		{{0, 2, 59, hemisphere::WEST}, {0x51, 0x02, 0x00, 0x01, 0x2a}},
	};

	for (auto const & t : cases) {
		message_51 m;
		m.set_lon(t.lon);
		EXPECT_EQ(t.expected, m.get_data()) << "longitude=" << t.lon;
	}
}

}
