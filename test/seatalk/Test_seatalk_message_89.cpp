#include <gtest/gtest.h>
#include <marnav/seatalk/message_89.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_89 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		double heading;
	};

	// clang-format off
	const std::vector<test_case> cases{
		// testing lower parts of 'u'
		{{0x89, 0x02, 0x00, 0x00, 0x20}, 0.0},
		{{0x89, 0x12, 0x00, 0x00, 0x20}, 90.0},
		{{0x89, 0x22, 0x00, 0x00, 0x20}, 180.0},
		{{0x89, 0x32, 0x00, 0x00, 0x20}, 270.0},
		// testing 'vw'
		{{0x89, 0x02, 0x01, 0x00, 0x20}, 2.0},
		{{0x89, 0x02, 0x02, 0x00, 0x20}, 4.0},
		{{0x89, 0x02, 0x03, 0x00, 0x20}, 6.0},
		{{0x89, 0x02, 0x04, 0x00, 0x20}, 8.0},
		{{0x89, 0x02, 0x05, 0x00, 0x20}, 10.0},
		{{0x89, 0x02, 0x06, 0x00, 0x20}, 12.0},
		{{0x89, 0x02, 0x07, 0x00, 0x20}, 14.0},
		{{0x89, 0x02, 0x08, 0x00, 0x20}, 16.0},
		{{0x89, 0x02, 0x09, 0x00, 0x20}, 18.0},
		{{0x89, 0x02, 0x0a, 0x00, 0x20}, 20.0},
		{{0x89, 0x02, 0x0b, 0x00, 0x20}, 22.0},
		{{0x89, 0x02, 0x0c, 0x00, 0x20}, 24.0},
		{{0x89, 0x02, 0x0d, 0x00, 0x20}, 26.0},
		{{0x89, 0x02, 0x0e, 0x00, 0x20}, 28.0},
		{{0x89, 0x02, 0x0f, 0x00, 0x20}, 30.0},
		{{0x89, 0x02, 0x10, 0x00, 0x20}, 32.0},
		{{0x89, 0x02, 0x20, 0x00, 0x20}, 64.0},
		{{0x89, 0x02, 0x30, 0x00, 0x20}, 96.0},
		{{0x89, 0x02, 0x40, 0x00, 0x20}, 0.0},
		{{0x89, 0x02, 0x50, 0x00, 0x20}, 32.0},
		{{0x89, 0x02, 0x60, 0x00, 0x20}, 64.0},
		{{0x89, 0x02, 0x70, 0x00, 0x20}, 96.0},
		{{0x89, 0x02, 0x80, 0x00, 0x20}, 0.0},
		// testing upper parts of 'u'
		{{0x89, 0x02, 0x00, 0x00, 0x20}, 0.0},
		{{0x89, 0x42, 0x00, 0x00, 0x20}, 0.5},
		{{0x89, 0x82, 0x00, 0x00, 0x20}, 1.0},
		{{0x89, 0xc2, 0x00, 0x00, 0x20}, 1.5},
	};
	// clang-format on
};

TEST_F(Test_seatalk_message_89, construction)
{
	EXPECT_NO_THROW(message_89 m);
}

TEST_F(Test_seatalk_message_89, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_89::parse({4, 0x00}));
	EXPECT_ANY_THROW(message_89::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_89, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_89::parse({0x89, 0x01, 0x00, 0x00, 0x20}));
	EXPECT_ANY_THROW(message_89::parse({0x89, 0x03, 0x00, 0x00, 0x20}));
}

TEST_F(Test_seatalk_message_89, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_89::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_89>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_NEAR(t.heading, m->get_heading(), 1e-3);
	}
}

TEST_F(Test_seatalk_message_89, write_default)
{
	const raw expected{0x89, 0x02, 0x00, 0x00, 0x20};
	message_89 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_89, set_heading_get_data)
{
	for (auto const & t : cases) {

		// this cases are not possible to test because the upper two
		// bits of 'vw' will never be set this way.
		if (t.data[2] & 0xc0)
			continue;

		// this case does not make sense in setting heading and getting
		// the data, because it is not unique. it makes sense to be able
		// to parse it, but it is not necessary to generate it.
		if (t.data[2] == 0x30)
			continue;

		message_89 msg;
		msg.set_heading(t.heading);

		const auto raw = msg.get_data();
		EXPECT_EQ(t.data, raw) << "heading: " << t.heading;
	}
}

TEST_F(Test_seatalk_message_89, set_heading_interval)
{
	{
		message_89 m;
		m.set_heading(0.0);
		EXPECT_NEAR(0.0, m.get_heading(), 1e-3);
	}
	{
		message_89 m;
		m.set_heading(-1.0);
		EXPECT_NEAR(1.0, m.get_heading(), 1e-3);
	}
	{
		message_89 m;
		m.set_heading(360.0);
		EXPECT_NEAR(0.0, m.get_heading(), 1e-3);
	}
	{
		message_89 m;
		m.set_heading(361.0);
		EXPECT_NEAR(1.0, m.get_heading(), 1e-3);
	}
	{
		message_89 m;
		m.set_heading(-361.0);
		EXPECT_NEAR(1.0, m.get_heading(), 1e-3);
	}
}
}
