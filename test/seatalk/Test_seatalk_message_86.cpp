#include <gtest/gtest.h>
#include <marnav/seatalk/message_86.hpp>

namespace
{
using namespace marnav::seatalk;

class Test_seatalk_message_86 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		message_86::origin org;
		key k;
	};

	const std::vector<test_case> cases{
		{{0x86, 0x01, 0x02, 0xfd}, message_86::origin::st1000, key::key_standby},
		{{0x86, 0x01, 0x05, 0xfa}, message_86::origin::st1000, key::key_m1},
		{{0x86, 0x01, 0x06, 0xf9}, message_86::origin::st1000, key::key_m10},
		{{0x86, 0x01, 0x07, 0xf8}, message_86::origin::st1000, key::key_p1},
		{{0x86, 0x01, 0x08, 0xf7}, message_86::origin::st1000, key::key_p10},
	};
};

TEST_F(Test_seatalk_message_86, construction)
{
	EXPECT_NO_THROW(message_86 m);
}

TEST_F(Test_seatalk_message_86, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_86::parse({3, 0x00}));
	EXPECT_ANY_THROW(message_86::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_86, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_86::parse({0x86, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_86::parse({0x86, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_86, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_86::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_86>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.org, m->get_org());
		EXPECT_EQ(t.k, m->get_key());
	}
}

TEST_F(Test_seatalk_message_86, parse_invalid_code)
{
	const raw data{0x86, 0x01, 0x02, 0xfc};

	EXPECT_ANY_THROW(message_86::parse(data));
}

TEST_F(Test_seatalk_message_86, write_default)
{
	const raw expected{0x86, 0x01, 0x02, 0xfd};
	message_86 m;

	EXPECT_EQ(expected, m.get_data());
}
}
