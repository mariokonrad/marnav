#include <gtest/gtest.h>
#include <marnav/seatalk/message_50.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_50 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_50, construction) { EXPECT_NO_THROW(message_50 m); }

TEST_F(Test_seatalk_message_50, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_50::parse({4, 0x00}));
	EXPECT_ANY_THROW(message_50::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_50, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_50::parse({0x50, 0x01, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_50::parse({0x50, 0x03, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_50, parse)
{
	struct test_case {
		raw data;
	};

	const std::vector<test_case> cases{
		{{0x50, 0x02, 0x00, 0x00, 0x00}},
		{{0x50, 0x02, 0x0a, 0x00, 0x00}},
		{{0x50, 0x02, 0x00, 0x01, 0x00}},
		{{0x50, 0x02, 0x00, 0x00, 0x01}},
	};

	for (auto const & t : cases) {
		auto generic_message = message_50::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_50>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
	}
}

TEST_F(Test_seatalk_message_50, write_default)
{
	const raw expected{0x50, 0x02, 0x00, 0x00, 0x00};
	message_50 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_50, set_lat)
{
	using latitude = marnav::geo::latitude;
	using hemisphere = latitude::hemisphere;

	struct test_case {
		latitude lat;
		raw expected;
	};

	const std::vector<test_case> cases{
		{{0, 0, 0, hemisphere::north}, {0x50, 0x02, 0x00, 0x00, 0x00}},
		{{0, 0, 0, hemisphere::south}, {0x50, 0x02, 0x00, 0x00, 0x00}},
		{{1, 0, 0, hemisphere::north}, {0x50, 0x02, 0x01, 0x00, 0x00}},
		{{1, 0, 0, hemisphere::south}, {0x50, 0x02, 0x01, 0x80, 0x00}},
		{{0, 1, 0, hemisphere::north}, {0x50, 0x02, 0x00, 0x00, 0x64}},
		{{0, 0, 1, hemisphere::north}, {0x50, 0x02, 0x00, 0x00, 0x01}},
		{{0, 0, 2, hemisphere::north}, {0x50, 0x02, 0x00, 0x00, 0x03}},
		{{0, 0, 3, hemisphere::north}, {0x50, 0x02, 0x00, 0x00, 0x05}},
		{{0, 1, 59, hemisphere::north}, {0x50, 0x02, 0x00, 0x00, 0xc6}},
		{{0, 2, 59, hemisphere::north}, {0x50, 0x02, 0x00, 0x01, 0x2a}},
	};

	for (auto const & t : cases) {
		message_50 m;
		m.set_lat(t.lat);
		EXPECT_EQ(t.expected, m.get_data()) << "latitude=" << t.lat;
	}
}

}
