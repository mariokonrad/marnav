#include <gtest/gtest.h>
#include <marnav/seatalk/message_00.hpp>

namespace
{

using namespace marnav;

class Test_seatalk_message_00 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_00, construction) { seatalk::message_00 m; }

TEST_F(Test_seatalk_message_00, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_00::parse({4, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_00::parse({6, 0x00}));
}

TEST_F(Test_seatalk_message_00, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_00::parse({0x00, 0x01, 0x00, 0x65, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_00::parse({0x00, 0x03, 0x00, 0x65, 0x00}));
}

TEST_F(Test_seatalk_message_00, parse)
{
	struct test_case {
		seatalk::raw data;
		uint16_t depth;
	};

	std::vector<test_case> cases{
		{{0x00, 0x02, 0x00, 0x65, 0x00}, 101}, //  3.1 m, 10.17 feet
		{{0x00, 0x02, 0x00, 0x64, 0x02}, 612}, // 18.7 m, 61.2  feet
		{{0x00, 0x02, 0x00, 0x64, 0x00}, 100}, //  3.0 m, 10.0  feet
		{{0x00, 0x02, 0x00, 0x00, 0x02}, 512}, // 15.6 m, 51.2  feet
		{{0x00, 0x02, 0x00, 0x00, 0x00}, 0}, //  0.0 m,  0.0  feet
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_00::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);

		auto m = seatalk::message_cast<seatalk::message_00>(generic_message);
		ASSERT_TRUE(m != nullptr);

		EXPECT_EQ(seatalk::message_id::depth_below_transducer, m->type());

		EXPECT_FALSE(m->get_anchor_alarm_active());
		EXPECT_FALSE(m->get_metric_display_units());
		EXPECT_FALSE(m->get_transducer_defective());
		EXPECT_FALSE(m->get_depth_alarm_active());
		EXPECT_FALSE(m->get_shallow_depth_alarm_active());
		EXPECT_EQ(t.depth, m->get_depth());
	}
}

TEST_F(Test_seatalk_message_00, parse_anchor_alarm_active)
{
	seatalk::raw data{0x00, 0x02, 0x80, 0x00, 0x00};

	auto generic_message = seatalk::message_00::parse(data);
	ASSERT_TRUE(generic_message != nullptr);

	auto m = seatalk::message_cast<seatalk::message_00>(generic_message);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(seatalk::message_id::depth_below_transducer, m->type());
	EXPECT_TRUE(m->get_anchor_alarm_active());
	EXPECT_FALSE(m->get_metric_display_units());
	EXPECT_FALSE(m->get_transducer_defective());
	EXPECT_FALSE(m->get_depth_alarm_active());
	EXPECT_FALSE(m->get_shallow_depth_alarm_active());
	EXPECT_EQ(0u, m->get_depth());
}

TEST_F(Test_seatalk_message_00, parse_metric_display_units)
{
	seatalk::raw data{0x00, 0x02, 0x40, 0x00, 0x00};

	auto generic_message = seatalk::message_00::parse(data);
	ASSERT_TRUE(generic_message != nullptr);

	auto m = seatalk::message_cast<seatalk::message_00>(generic_message);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(seatalk::message_id::depth_below_transducer, m->type());
	EXPECT_FALSE(m->get_anchor_alarm_active());
	EXPECT_TRUE(m->get_metric_display_units());
	EXPECT_FALSE(m->get_transducer_defective());
	EXPECT_FALSE(m->get_depth_alarm_active());
	EXPECT_FALSE(m->get_shallow_depth_alarm_active());
	EXPECT_EQ(0u, m->get_depth());
}

TEST_F(Test_seatalk_message_00, parse_transducer_defective)
{
	seatalk::raw data{0x00, 0x02, 0x04, 0x00, 0x00};

	auto generic_message = seatalk::message_00::parse(data);
	ASSERT_TRUE(generic_message != nullptr);

	auto m = seatalk::message_cast<seatalk::message_00>(generic_message);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(seatalk::message_id::depth_below_transducer, m->type());
	EXPECT_FALSE(m->get_anchor_alarm_active());
	EXPECT_FALSE(m->get_metric_display_units());
	EXPECT_TRUE(m->get_transducer_defective());
	EXPECT_FALSE(m->get_depth_alarm_active());
	EXPECT_FALSE(m->get_shallow_depth_alarm_active());
	EXPECT_EQ(0u, m->get_depth());
}

TEST_F(Test_seatalk_message_00, parse_depth_alarm_active)
{
	seatalk::raw data{0x00, 0x02, 0x02, 0x00, 0x00};

	auto generic_message = seatalk::message_00::parse(data);
	ASSERT_TRUE(generic_message != nullptr);

	auto m = seatalk::message_cast<seatalk::message_00>(generic_message);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(seatalk::message_id::depth_below_transducer, m->type());
	EXPECT_FALSE(m->get_anchor_alarm_active());
	EXPECT_FALSE(m->get_metric_display_units());
	EXPECT_FALSE(m->get_transducer_defective());
	EXPECT_TRUE(m->get_depth_alarm_active());
	EXPECT_FALSE(m->get_shallow_depth_alarm_active());
	EXPECT_EQ(0u, m->get_depth());
}

TEST_F(Test_seatalk_message_00, parse_shallow_depth_alarm_active)
{
	seatalk::raw data{0x00, 0x02, 0x01, 0x00, 0x00};

	auto generic_message = seatalk::message_00::parse(data);
	ASSERT_TRUE(generic_message != nullptr);

	auto m = seatalk::message_cast<seatalk::message_00>(generic_message);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(seatalk::message_id::depth_below_transducer, m->type());
	EXPECT_FALSE(m->get_anchor_alarm_active());
	EXPECT_FALSE(m->get_metric_display_units());
	EXPECT_FALSE(m->get_transducer_defective());
	EXPECT_FALSE(m->get_depth_alarm_active());
	EXPECT_TRUE(m->get_shallow_depth_alarm_active());
	EXPECT_EQ(0u, m->get_depth());
}

TEST_F(Test_seatalk_message_00, write_default)
{
	const seatalk::raw expected{0x00, 0x02, 0x00, 0x00, 0x00};
	seatalk::message_00 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_00, write_anchor_alarm_active)
{
	const seatalk::raw expected{0x00, 0x02, 0x80, 0x00, 0x00};
	seatalk::message_00 m;
	m.set_anchor_alarm_active(true);

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_00, write_metric_display_units)
{
	const seatalk::raw expected{0x00, 0x02, 0x40, 0x00, 0x00};
	seatalk::message_00 m;
	m.set_metric_display_units(true);

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_00, depth_meters)
{
	struct test_case {
		uint16_t depth;
		double meters;
	};

	std::vector<test_case> cases{
		{0, 0.0000}, {1, 0.32808}, {10, 3.2808}, {20, 6.5616}, {100, 32.808},
	};

	for (auto test : cases) {
		seatalk::message_00 m;
		m.set_depth(test.depth);
		EXPECT_NEAR(test.meters, m.get_depth_meters(), 1e-5);
	}
}
TEST_F(Test_seatalk_message_00, depth_meters_transducer_defective)
{
	std::vector<uint16_t> cases{0, 1, 10, 20, 100};

	for (auto test : cases) {
		seatalk::message_00 m;
		m.set_depth(test);
		m.set_transducer_defective(true);
		EXPECT_NEAR(0.0, m.get_depth_meters(), 1e-5);
	}
}
}
