#include <gtest/gtest.h>
#include <marnav/utils/bitset.hpp>
#include <marnav/utils/bitset_string.hpp>

namespace
{
using namespace marnav::utils;

class Test_utils_bitset : public ::testing::Test
{
};

TEST_F(Test_utils_bitset, to_string)
{
	EXPECT_STREQ("0000", to_string(marnav::utils::bitset<uint8_t>(4)).c_str());
	EXPECT_STREQ("00000000", to_string(marnav::utils::bitset<uint8_t>(8)).c_str());
	EXPECT_STREQ("0000000000000", to_string(marnav::utils::bitset<uint8_t>(13)).c_str());
	EXPECT_STREQ("0000000000000000", to_string(marnav::utils::bitset<uint8_t>(16)).c_str());
	EXPECT_STREQ("00000000000000000000000000000000", to_string(marnav::utils::bitset<uint8_t>(32)).c_str());
}

TEST_F(Test_utils_bitset, to_string_pack)
{
	EXPECT_STREQ("00000000", to_string(marnav::utils::bitset<uint8_t>(8), 0).c_str());
	EXPECT_STREQ("0 0 0 0 0 0 0 0", to_string(marnav::utils::bitset<uint8_t>(8), 1).c_str());
	EXPECT_STREQ("00 00 00 00", to_string(marnav::utils::bitset<uint8_t>(8), 2).c_str());
	EXPECT_STREQ("000 000 00", to_string(marnav::utils::bitset<uint8_t>(8), 3).c_str());
	EXPECT_STREQ("0000 0000", to_string(marnav::utils::bitset<uint8_t>(8), 4).c_str());
	EXPECT_STREQ("00000 000", to_string(marnav::utils::bitset<uint8_t>(8), 5).c_str());
	EXPECT_STREQ("000000 00", to_string(marnav::utils::bitset<uint8_t>(8), 6).c_str());
	EXPECT_STREQ("0000000 0", to_string(marnav::utils::bitset<uint8_t>(8), 7).c_str());
	EXPECT_STREQ("00000000", to_string(marnav::utils::bitset<uint8_t>(8), 8).c_str());
	EXPECT_STREQ("00000000", to_string(marnav::utils::bitset<uint8_t>(8), 9).c_str());

	EXPECT_STREQ("0000 0000 0000", to_string(marnav::utils::bitset<uint8_t>(12), 4).c_str());
	EXPECT_STREQ("0000 0000 0000 0000", to_string(marnav::utils::bitset<uint8_t>(16), 4).c_str());
	EXPECT_STREQ("0000 0000 0000 0000 0000", to_string(marnav::utils::bitset<uint8_t>(20), 4).c_str());
	EXPECT_STREQ("0000 0000 0000 0000 0000 0000", to_string(marnav::utils::bitset<uint8_t>(24), 4).c_str());

	EXPECT_STREQ("000000000000", to_string(marnav::utils::bitset<uint8_t>(12), 0, ':').c_str());
	EXPECT_STREQ("0000:0000:0000", to_string(marnav::utils::bitset<uint8_t>(12), 4, ':').c_str());
	EXPECT_STREQ("0000:0000:0000:0000", to_string(marnav::utils::bitset<uint8_t>(16), 4, ':').c_str());
	EXPECT_STREQ("0000:0000:0000:0000:0000", to_string(marnav::utils::bitset<uint8_t>(20), 4, ':').c_str());
	EXPECT_STREQ(
		"0000:0000:0000:0000:0000:0000", to_string(marnav::utils::bitset<uint8_t>(24), 4, ':').c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_bit_size)
{
	marnav::utils::bitset<uint8_t> b(16);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("0000000000000000", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_container_iterator)
{
	using namespace std;

	vector<uint8_t> v{0xaa, 0x55};
	marnav::utils::bitset<uint8_t> b(begin(v), end(v));

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1010101001010101", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_container_move)
{
	marnav::utils::bitset<uint8_t> b(std::vector<uint8_t>{0xaa, 0x55});

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1010101001010101", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_bitset_move)
{
	marnav::utils::bitset<uint8_t> t;
	t.append(0xaa55, 16);

	marnav::utils::bitset<uint8_t> b(std::move(t));

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1010101001010101", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_range)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xf0f0, 16);
	ASSERT_STREQ("1111000011110000", to_string(b).c_str());

	marnav::utils::bitset<uint8_t> c{b.begin() + 4, b.end() - 4};
	EXPECT_STREQ("00001111", to_string(c).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_reverse_range)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xf0f0, 16);
	ASSERT_STREQ("1111000011110000", to_string(b).c_str());

	marnav::utils::bitset<uint8_t> c{b.end(), b.begin() + 4};
	EXPECT_EQ(0u, c.size());
}

TEST_F(Test_utils_bitset, uint8__construction_range_invalid_iterator)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xf0f0, 16);
	ASSERT_STREQ("1111000011110000", to_string(b).c_str());

	marnav::utils::bitset<uint8_t> c{marnav::utils::bitset<uint8_t>::const_iterator(), b.end()};
	EXPECT_EQ(0u, c.size());
}

TEST_F(Test_utils_bitset, uint8__construction_initializer_list)
{
	marnav::utils::bitset<uint8_t> b{0xaa, 0x55, 0xaa, 0x55};
	EXPECT_STREQ("10101010010101011010101001010101", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__reserve)
{
	marnav::utils::bitset<uint8_t>::container c;
	c.reserve(1);

	marnav::utils::bitset<uint8_t> b;

	EXPECT_EQ(0u, b.capacity());
	b.reserve(1);
	EXPECT_EQ(c.capacity() * marnav::utils::bitset<uint8_t>::bits_per_block, b.capacity());
}

TEST_F(Test_utils_bitset, uint8__clear)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	ASSERT_STREQ("10101010", to_string(b).c_str());
	b.clear();
	EXPECT_EQ(0u, b.size());
	EXPECT_STREQ("", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_to_self)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	ASSERT_STREQ("10101010", to_string(b).c_str());
	b.append(b);
	EXPECT_STREQ("10101010", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_zero_bits)
{
	marnav::utils::bitset<uint8_t> b;
	ASSERT_STREQ("", to_string(b).c_str());
	b.append(0xaa, 0);
	EXPECT_STREQ("", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_into_self)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	ASSERT_STREQ("10101010", to_string(b).c_str());
	b.set(b, 1);
	EXPECT_STREQ("10101010", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__test_bit)
{
	marnav::utils::bitset<uint8_t> b;

	b.append(0xaa, 8);
	ASSERT_STREQ("10101010", to_string(b).c_str());

	EXPECT_EQ(true, b.test(0));
	EXPECT_EQ(false, b.test(1));
	EXPECT_EQ(true, b.test(2));
	EXPECT_EQ(false, b.test(3));
	EXPECT_EQ(true, b.test(4));
	EXPECT_EQ(false, b.test(5));
	EXPECT_EQ(true, b.test(6));
	EXPECT_EQ(false, b.test(7));
}

TEST_F(Test_utils_bitset, uint8__get)
{
	marnav::utils::bitset<uint8_t> b;

	b.append(0xaa, 8);
	ASSERT_STREQ("10101010", to_string(b).c_str());

	EXPECT_EQ(true, b.get(0));
	EXPECT_EQ(false, b.get(1));
	EXPECT_EQ(true, b.get(2));
	EXPECT_EQ(false, b.get(3));
	EXPECT_EQ(true, b.get(4));
	EXPECT_EQ(false, b.get(5));
	EXPECT_EQ(true, b.get(6));
	EXPECT_EQ(false, b.get(7));
}

TEST_F(Test_utils_bitset, uint8__get_enum)
{
	enum foo { abc = 0, bcd = 1, cde = 2 };

	marnav::utils::bitset<uint8_t> b;

	b.append(abc, 8);

	EXPECT_EQ(abc, b.get<foo>(0, 8));
}

TEST_F(Test_utils_bitset, uint8__index_operator)
{
	marnav::utils::bitset<uint8_t> b;

	b.append(0xaa, 8);
	ASSERT_STREQ("10101010", to_string(b).c_str());

	EXPECT_EQ(true, b[0]);
	EXPECT_EQ(false, b[1]);
	EXPECT_EQ(true, b[2]);
	EXPECT_EQ(false, b[3]);
	EXPECT_EQ(true, b[4]);
	EXPECT_EQ(false, b[5]);
	EXPECT_EQ(true, b[6]);
	EXPECT_EQ(false, b[7]);
}

TEST_F(Test_utils_bitset, const_iterator__default_construction)
{
	marnav::utils::bitset<uint8_t>::const_iterator i;

	EXPECT_EQ(0u, i.get_pos());
}

TEST_F(Test_utils_bitset, const_iterator_begin)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	const marnav::utils::bitset<uint8_t> & c = b;

	EXPECT_EQ(c.begin(), b.cbegin());
}

TEST_F(Test_utils_bitset, const_iterator_end)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	const marnav::utils::bitset<uint8_t> & c = b;

	EXPECT_EQ(c.end(), b.cend());
}

TEST_F(Test_utils_bitset, const_iterator_comparison_less)
{
	marnav::utils::bitset<uint8_t> b(16);

	auto i = b.begin();
	auto j = b.begin();
	auto k = b.begin();
	++k;

	EXPECT_FALSE(i < j);
	EXPECT_TRUE(i < k);
}

TEST_F(Test_utils_bitset, const_iterator_comparison_less_or_equal)
{
	marnav::utils::bitset<uint8_t> b(16);

	auto i = b.begin();
	auto j = b.begin();
	auto k = b.begin();
	++k;

	EXPECT_TRUE(i <= j);
	EXPECT_TRUE(i <= k);
}

TEST_F(Test_utils_bitset, const_iterator_comparison_greater)
{
	marnav::utils::bitset<uint8_t> b(16);

	auto i = b.begin();
	auto j = b.begin();
	auto k = b.begin();
	++k;

	EXPECT_FALSE(i > j);
	EXPECT_TRUE(k > i);
}

TEST_F(Test_utils_bitset, const_iterator_comparison_greater_or_equal)
{
	marnav::utils::bitset<uint8_t> b(16);

	auto i = b.begin();
	auto j = b.begin();
	auto k = b.begin();
	++k;

	EXPECT_TRUE(i >= j);
	EXPECT_TRUE(k >= i);
}

TEST_F(Test_utils_bitset, uint8__append_single_bits)
{
	{
		marnav::utils::bitset<uint8_t> bits;
		bits.append(1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits;
		bits.append(1, 1);
		bits.append(0, 1);
		bits.append(0, 1);
		bits.append(1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1001", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(8);
		bits.append(1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("000000001", to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__append_block_size_plus_one)
{
	marnav::utils::bitset<uint8_t> bits;
	bits.append(0x00000001, 9);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("000000001", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_multiple_bits)
{
	{
		marnav::utils::bitset<uint8_t> bits;
		bits.append(0x00000001, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("01", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits;
		bits.append(0x00000001, 1);
		bits.append(0x00000001, 2);
		bits.append(0x00000001, 3);
		bits.append(0x00000001, 4);
		bits.append(0x00000001, 5);
		bits.append(0x00000001, 6);
		bits.append(0x00000001, 7);
		bits.append(0x00000001, 8);
		bits.append(0x00000001, 9);
		bits.append(0x00000001, 10);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ(
			"1010010001000010000010000001000000010000000010000000001", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits;

		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		//            111010011110101011001111111111
		const uint32_t value = 981119999; // 30 bits of information

		bits.append(value, 32);

		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("00111010011110101011001111111111", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits;

		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		//            111010011110101011001111111111
		const uint32_t value = 981119999; // 30 bits of information

		bits.append(value, 30);

		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("111010011110101011001111111111", to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__set_single_bits)
{
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(1, 0, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1000000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(1, 1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0100000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(1, 15, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000001000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(1, 16, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000100000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__set_block_size_plus_one)
{
	marnav::utils::bitset<uint8_t> bits(32);
	bits.set(0x00000001, 0, 9);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("00000000100000000000000000000000", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_multiple_bits)
{
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(0x00000001, 0, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0100000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(0x00000001, 1, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0010000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(0x00000001, 15, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000100000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);
		bits.set(0x00000001, 16, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000010000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits(64);

		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		//            111010011110101011001111111111
		const uint32_t value = 981119999; // 30 bits of information

		bits.set(value, 8, 30);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000011101001111010101100111111111100000000000000000000000000",
			to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__get_multiple_bits_ending_on_block_boundary)
{
	marnav::utils::bitset<uint8_t> bits(64);
	bits.set(0x7, 5, 3);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000011100000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 0, 6);
	EXPECT_EQ(1u, value);
}

TEST_F(Test_utils_bitset, uint8__get_multiple_bits_completely_within_block)
{
	marnav::utils::bitset<uint8_t> bits(64);
	bits.set(0xff, 4, 3);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000111000000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 0, 6);
	EXPECT_EQ(3u, value);
}

TEST_F(Test_utils_bitset, uint8__get_multiple_bits_fractions_of_two_blocks)
{
	marnav::utils::bitset<uint8_t> bits(64);
	bits.set(0xff, 4, 6);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000111111000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 0, 6);
	EXPECT_EQ(3u, value);
}

TEST_F(Test_utils_bitset, uint8__get_multiple_bits_using_three_blocks)
{
	marnav::utils::bitset<uint8_t> bits(64);
	bits.set(0xffff, 4, 14);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000111111111111110000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 2, 6);
	EXPECT_EQ(15u, value);
}

TEST_F(Test_utils_bitset, uint8__set_enum)
{
	enum class ids : uint8_t { A = 1, B, C };

	marnav::utils::bitset<uint8_t> bits(64);
	bits.set(ids::A, 4, 6);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000000001000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint16__get_multiple_bits_ending_on_block_boundary)
{
	marnav::utils::bitset<uint16_t> bits(64);
	bits.set(0xff, 13, 3);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000000000000111000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 8, 6);
	EXPECT_EQ(1u, value);
}

TEST_F(Test_utils_bitset, uint16__get_multiple_bits_completely_within_block)
{
	marnav::utils::bitset<uint16_t> bits(64);
	bits.set(0x7, 4, 3);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000111000000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 0, 6);
	EXPECT_EQ(3u, value);
}

TEST_F(Test_utils_bitset, uint16__get_multiple_bits_fractions_of_two_blocks)
{
	marnav::utils::bitset<uint16_t> bits(64);
	bits.set(0xffff, 4, 6);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000111111000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 0, 6);
	EXPECT_EQ(3u, value);
}

TEST_F(Test_utils_bitset, uint16__get_multiple_bits_using_three_blocks)
{
	marnav::utils::bitset<uint16_t> bits(64);
	uint64_t val = -1;
	bits.set(val, 4, 40);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000111111111111111111111111111111111111111100000000000000000000",
		to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 2, 6);
	EXPECT_EQ(15u, value);
}

TEST_F(Test_utils_bitset, uint8__copy_constructor)
{
	marnav::utils::bitset<uint8_t> bits(32);
	bits.set(1, 0, 6);

	marnav::utils::bitset<uint8_t> copy(bits);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+
	ASSERT_STREQ("00000100000000000000000000000000", to_string(bits).c_str());
	EXPECT_STREQ("00000100000000000000000000000000", to_string(copy).c_str());
}

TEST_F(Test_utils_bitset, uint8__assignment)
{
	marnav::utils::bitset<uint8_t> bits(32);
	bits.set(1, 0, 6);

	marnav::utils::bitset<uint8_t> copy(16);
	ASSERT_STREQ("0000000000000000", to_string(copy).c_str());
	copy = bits;

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+
	ASSERT_STREQ("00000100000000000000000000000000", to_string(bits).c_str());
	EXPECT_STREQ("00000100000000000000000000000000", to_string(copy).c_str());
}

template <class T> marnav::utils::bitset<uint8_t> get_test_data(unsigned int size)
{
	marnav::utils::bitset<T> result(size);

	result.set(1, 0, 6);

	return result;
}

TEST_F(Test_utils_bitset, uint8__as_return_value_small)
{
	auto bits = get_test_data<uint8_t>(32);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+
	ASSERT_STREQ("00000100000000000000000000000000", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__as_return_value_medium)
{
	auto bits = get_test_data<uint8_t>(168);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+
	ASSERT_STREQ("00000100000000000000000000000000000000000000000000000000000000000000000000000"
				 "00000000000000000000000000000000000000000000000000000000000000000000000000000"
				 "00000000000000",
		to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_multiple_values)
{
	marnav::utils::bitset<uint8_t> bits(64);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000000000000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	bits.set(1, 0, 6);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000010000000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	bits.set(1, 6, 2);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000010100000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__flip)
{
	marnav::utils::bitset<uint8_t> bits(64);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("0000000000000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	bits.flip(0);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1000000000000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	bits.flip(10);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1000000000100000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());

	bits.flip(32);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1000000000100000000000000000000010000000000000000000000000000000",
		to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_bitset_to_empty_bitset)
{
	marnav::utils::bitset<uint8_t> b0;
	marnav::utils::bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.append(b0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_bitset_to_nonempty_bitset)
{
	marnav::utils::bitset<uint8_t> b0;
	marnav::utils::bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.append(0xaa, 8);
	b1.append(b0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("1010101001010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_empty_bitset)
{
	marnav::utils::bitset<uint8_t> b0;
	marnav::utils::bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_empty_bitset_mixed_type_bitsets_8_to_16)
{
	marnav::utils::bitset<uint8_t> b0;
	marnav::utils::bitset<uint16_t> b1;

	b0.append(0x55, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_empty_bitset_mixed_type_bitsets_16_to_8)
{
	marnav::utils::bitset<uint16_t> b0;
	marnav::utils::bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_nonempty_bitset)
{
	marnav::utils::bitset<uint8_t> b0;
	marnav::utils::bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.append(0xaa, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bit)
{
	marnav::utils::bitset<uint8_t> b(8);

	EXPECT_STREQ("00000000", to_string(b).c_str());
	b.set_bit(0, true);
	EXPECT_STREQ("10000000", to_string(b).c_str());
	b.set_bit(7, true);
	EXPECT_STREQ("10000001", to_string(b).c_str());
	b.set_bit(0, false);
	EXPECT_STREQ("00000001", to_string(b).c_str());
	b.set_bit(7, false);
	EXPECT_STREQ("00000000", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__reset_all)
{
	marnav::utils::bitset<uint8_t> b(8);
	b.set(0xaa, 0, 8);

	EXPECT_STREQ("10101010", to_string(b).c_str());
	b.reset();
	EXPECT_STREQ("00000000", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__reset__invalid_index)
{
	marnav::utils::bitset<uint8_t> b(8);
	b.set(0xff, 0, 8);

	EXPECT_ANY_THROW(b.reset(8));
}

TEST_F(Test_utils_bitset, uint8__reset)
{
	marnav::utils::bitset<uint8_t> b(8);
	b.set(0xff, 0, 8);

	EXPECT_STREQ("11111111", to_string(b).c_str());
	b.reset(0);
	EXPECT_STREQ("01111111", to_string(b).c_str());
	b.reset(1);
	EXPECT_STREQ("00111111", to_string(b).c_str());
	b.reset(2);
	EXPECT_STREQ("00011111", to_string(b).c_str());
	b.reset(3);
	EXPECT_STREQ("00001111", to_string(b).c_str());
	b.reset(4);
	EXPECT_STREQ("00000111", to_string(b).c_str());
	b.reset(5);
	EXPECT_STREQ("00000011", to_string(b).c_str());
	b.reset(6);
	EXPECT_STREQ("00000001", to_string(b).c_str());
	b.reset(7);
	EXPECT_STREQ("00000000", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__all)
{
	{
		marnav::utils::bitset<uint8_t> b(8);
		EXPECT_FALSE(b.all());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xaa, 0, 8);
		EXPECT_FALSE(b.all());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(1, 0, 8);
		EXPECT_FALSE(b.all());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xff, 0, 8);
		EXPECT_TRUE(b.all());
	}
}

TEST_F(Test_utils_bitset, uint8__any)
{
	{
		marnav::utils::bitset<uint8_t> b(8);
		EXPECT_FALSE(b.any());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xaa, 0, 8);
		EXPECT_TRUE(b.any());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(1, 0, 8);
		EXPECT_TRUE(b.any());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xff, 0, 8);
		EXPECT_TRUE(b.any());
	}
}

TEST_F(Test_utils_bitset, uint8__count__between)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0x55aa, 16);

	EXPECT_EQ(b.count(), b.count(b.begin(), b.end()));
	EXPECT_EQ(8u, b.count(b.begin(), b.end()));
	EXPECT_EQ(0u, b.count(b.begin(), b.begin() + 1));
	EXPECT_EQ(1u, b.count(b.begin(), b.begin() + 2));
	EXPECT_EQ(1u, b.count(b.begin(), b.begin() + 3));
	EXPECT_EQ(2u, b.count(b.begin(), b.begin() + 4));
	EXPECT_EQ(2u, b.count(b.begin(), b.begin() + 5));
}

TEST_F(Test_utils_bitset, uint8__none)
{
	{
		marnav::utils::bitset<uint8_t> b(8);
		EXPECT_TRUE(b.none());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xaa, 0, 8);
		EXPECT_FALSE(b.none());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(1, 0, 8);
		EXPECT_FALSE(b.none());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xff, 0, 8);
		EXPECT_FALSE(b.none());
	}
}

TEST_F(Test_utils_bitset, uint8__count)
{
	{
		marnav::utils::bitset<uint8_t> b(8);
		EXPECT_EQ(0u, b.count());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xaa, 0, 8);
		EXPECT_EQ(4u, b.count());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(1, 0, 8);
		EXPECT_EQ(1u, b.count());
	}
	{
		marnav::utils::bitset<uint8_t> b(8);
		b.set(0xff, 0, 8);
		EXPECT_EQ(8u, b.count());
	}
}

TEST_F(Test_utils_bitset, uint8__comparison_equal)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0x55, 8);

	EXPECT_TRUE(a == a);
	EXPECT_TRUE(b == b);
	EXPECT_TRUE(c == c);

	EXPECT_TRUE(a == b);
	EXPECT_TRUE(b == a);

	EXPECT_FALSE(a == c);
	EXPECT_FALSE(c == a);
	EXPECT_FALSE(b == c);
	EXPECT_FALSE(c == b);
}

TEST_F(Test_utils_bitset, uint8__uint16__comparison_equal)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint16_t> b;
	marnav::utils::bitset<uint16_t> c;
	marnav::utils::bitset<uint16_t> d;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0xaaaa, 16);
	d.append(0xa8, 8);

	EXPECT_TRUE(a == a);
	EXPECT_TRUE(b == b);
	EXPECT_TRUE(c == c);
	EXPECT_TRUE(d == d);

	EXPECT_TRUE(a == b);
	EXPECT_TRUE(b == a);

	EXPECT_FALSE(a == c);
	EXPECT_FALSE(c == a);
	EXPECT_FALSE(b == c);
	EXPECT_FALSE(c == b);
	EXPECT_FALSE(a == d);
}

TEST_F(Test_utils_bitset, uint8__comparison_not_equal)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0x55, 8);

	EXPECT_FALSE(a != a);
	EXPECT_FALSE(b != b);
	EXPECT_FALSE(c != c);

	EXPECT_FALSE(a != b);
	EXPECT_FALSE(b != a);

	EXPECT_TRUE(a != c);
	EXPECT_TRUE(c != a);
	EXPECT_TRUE(b != c);
	EXPECT_TRUE(c != b);
}

TEST_F(Test_utils_bitset, uint8__uint16__comparison_not_equal)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint16_t> b;
	marnav::utils::bitset<uint16_t> c;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0xaaaa, 16);

	EXPECT_FALSE(a != a);
	EXPECT_FALSE(b != b);
	EXPECT_FALSE(c != c);

	EXPECT_FALSE(a != b);
	EXPECT_FALSE(b != a);

	EXPECT_TRUE(a != c);
	EXPECT_TRUE(c != a);
	EXPECT_TRUE(b != c);
	EXPECT_TRUE(c != b);
}

TEST_F(Test_utils_bitset, uint8__comparison_less)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;
	marnav::utils::bitset<uint8_t> d;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0x55, 8);
	d.append(0x1111, 16);

	EXPECT_FALSE(a < a);
	EXPECT_FALSE(a < b);
	EXPECT_FALSE(a < c);
	EXPECT_TRUE(a < d);

	EXPECT_FALSE(b < a);
	EXPECT_FALSE(b < b);
	EXPECT_FALSE(b < c);
	EXPECT_TRUE(b < d);

	EXPECT_TRUE(c < a);
	EXPECT_TRUE(c < b);
	EXPECT_FALSE(c < c);
	EXPECT_TRUE(c < d);

	EXPECT_FALSE(d < a);
	EXPECT_FALSE(d < b);
	EXPECT_FALSE(d < c);
	EXPECT_FALSE(d < d);
}

TEST_F(Test_utils_bitset, uint8__comparison_less_or_equal)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;
	marnav::utils::bitset<uint8_t> d;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0x55, 8);
	d.append(0x1111, 16);

	EXPECT_TRUE(a <= a);
	EXPECT_TRUE(a <= b);
	EXPECT_FALSE(a <= c);
	EXPECT_TRUE(a <= d);

	EXPECT_TRUE(b <= a);
	EXPECT_TRUE(b <= b);
	EXPECT_FALSE(b <= c);
	EXPECT_TRUE(b <= d);

	EXPECT_TRUE(c <= a);
	EXPECT_TRUE(c <= b);
	EXPECT_TRUE(c <= c);
	EXPECT_TRUE(c <= d);

	EXPECT_FALSE(d <= a);
	EXPECT_FALSE(d <= b);
	EXPECT_FALSE(d <= c);
	EXPECT_TRUE(d <= d);
}

TEST_F(Test_utils_bitset, uint8__comparison_greater)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;
	marnav::utils::bitset<uint8_t> d;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0x55, 8);
	d.append(0x1111, 16);

	EXPECT_FALSE(a > a);
	EXPECT_FALSE(a > b);
	EXPECT_TRUE(a > c);
	EXPECT_FALSE(a > d);

	EXPECT_FALSE(b > a);
	EXPECT_FALSE(b > b);
	EXPECT_TRUE(b > c);
	EXPECT_FALSE(b > d);

	EXPECT_FALSE(c > a);
	EXPECT_FALSE(c > b);
	EXPECT_FALSE(c > c);
	EXPECT_FALSE(c > d);

	EXPECT_TRUE(d > a);
	EXPECT_TRUE(d > b);
	EXPECT_TRUE(d > c);
	EXPECT_FALSE(d > d);
}

TEST_F(Test_utils_bitset, uint8__comparison_greater_or_equal)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;
	marnav::utils::bitset<uint8_t> d;

	a.append(0xaa, 8);
	b.append(0xaa, 8);
	c.append(0x55, 8);
	d.append(0x1111, 16);

	EXPECT_TRUE(a >= a);
	EXPECT_TRUE(a >= b);
	EXPECT_TRUE(a >= c);
	EXPECT_FALSE(a >= d);

	EXPECT_TRUE(b >= a);
	EXPECT_TRUE(b >= b);
	EXPECT_TRUE(b >= c);
	EXPECT_FALSE(b >= d);

	EXPECT_FALSE(c >= a);
	EXPECT_FALSE(c >= b);
	EXPECT_TRUE(c >= c);
	EXPECT_FALSE(c >= d);

	EXPECT_TRUE(d >= a);
	EXPECT_TRUE(d >= b);
	EXPECT_TRUE(d >= c);
	EXPECT_TRUE(d >= d);
}

TEST_F(Test_utils_bitset, uint8__append_bits_exceeds_type)
{
	marnav::utils::bitset<uint8_t> b(32);
	const uint8_t data = 0xff;
	EXPECT_ANY_THROW(b.append(data, 16));
}

TEST_F(Test_utils_bitset, uint8__set_bits_exceeds_type)
{
	marnav::utils::bitset<uint8_t> b(32);
	const uint8_t data = 0xff;
	EXPECT_ANY_THROW(b.set(data, 0, 16));
}

TEST_F(Test_utils_bitset, uint8__get_bits_out_of_range)
{
	marnav::utils::bitset<uint8_t> b(32);
	uint8_t data;
	EXPECT_ANY_THROW(b.get(data, 0, 16));
	EXPECT_ANY_THROW(b.get(data, 28, 8));
	EXPECT_NO_THROW(b.get(data, 0, 0));
}

TEST_F(Test_utils_bitset, uint8__get_uint32)
{
	marnav::utils::bitset<uint8_t> b(64);
	b.set(0xaaaaaaaa, 0, 32);
	b.set(0xaaaaaaaa, 32, 32);
	const uint32_t expected = 0xaaaaaaaa;
	uint32_t data = 0;
	b.get(data, 4);
	EXPECT_EQ(expected, data);
}

TEST_F(Test_utils_bitset, uint8__get_bit_out_of_range)
{
	marnav::utils::bitset<uint8_t> b(32);

	EXPECT_ANY_THROW(b.get_bit(64));
}

TEST_F(Test_utils_bitset, uint8__set_bit_out_of_range)
{
	marnav::utils::bitset<uint8_t> b(32);

	EXPECT_ANY_THROW(b.set_bit(64, 1));
}

TEST_F(Test_utils_bitset, uint8__const_iterator__plus_equal)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaaaaaaaa, 32);

	auto i = b.begin();

	EXPECT_EQ(0u, i.get_pos());
	i += 1;
	EXPECT_EQ(1u, i.get_pos());
	i += 1;
	EXPECT_EQ(2u, i.get_pos());
	i += 1;
	EXPECT_EQ(3u, i.get_pos());
	i += 1;
	EXPECT_EQ(4u, i.get_pos());
	i += 2;
	EXPECT_EQ(6u, i.get_pos());
	i += 3;
	EXPECT_EQ(9u, i.get_pos());

	i += b.size() + 1;
	EXPECT_EQ(32u, i.get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__increment)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaaaaaaaa, 32);

	auto i = b.begin();

	EXPECT_EQ(0u, i.get_pos());
	++i;
	EXPECT_EQ(1u, i.get_pos());
	++i;
	EXPECT_EQ(2u, i.get_pos());
	i++;
	EXPECT_EQ(3u, i.get_pos());
	i++;
	EXPECT_EQ(4u, i.get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__plus)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaaaaaaaa, 32);

	auto i = b.begin();

	ASSERT_EQ(0u, i.get_pos());

	EXPECT_EQ(1u, (i + 1).get_pos());
	EXPECT_EQ(2u, (i + 2).get_pos());
	EXPECT_EQ(3u, (i + 3).get_pos());
	EXPECT_EQ(4u, (i + 4).get_pos());
	EXPECT_EQ(6u, (i + 6).get_pos());
	EXPECT_EQ(9u, (i + 9).get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__minus_equal)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaaaaaaaa, 32);

	auto i = b.end();

	EXPECT_EQ(32u, i.get_pos());
	i -= 1;
	EXPECT_EQ(31u, i.get_pos());
	i -= 1;
	EXPECT_EQ(30u, i.get_pos());
	i -= 1;
	EXPECT_EQ(29u, i.get_pos());
	i -= 1;
	EXPECT_EQ(28u, i.get_pos());
	i -= 2;
	EXPECT_EQ(26u, i.get_pos());
	i -= 3;
	EXPECT_EQ(23u, i.get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__decrement)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaaaaaaaa, 32);

	auto i = b.end();

	EXPECT_EQ(32u, i.get_pos());
	--i;
	EXPECT_EQ(31u, i.get_pos());
	--i;
	EXPECT_EQ(30u, i.get_pos());
	i--;
	EXPECT_EQ(29u, i.get_pos());
	i--;
	EXPECT_EQ(28u, i.get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__minus)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaaaaaaaa, 32);

	auto i = b.end();

	ASSERT_EQ(32u, i.get_pos());

	EXPECT_EQ(31u, (i - 1).get_pos());
	EXPECT_EQ(30u, (i - 2).get_pos());
	EXPECT_EQ(29u, (i - 3).get_pos());
	EXPECT_EQ(28u, (i - 4).get_pos());
	EXPECT_EQ(26u, (i - 6).get_pos());
	EXPECT_EQ(23u, (i - 9).get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__read)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	uint8_t v;

	auto i = b.begin();
	ASSERT_EQ(0u, i.get_pos());

	i.read(v, 2);
	EXPECT_EQ(2u, v);
	EXPECT_EQ(2u, i.get_pos());

	i.read(v, 3);
	EXPECT_EQ(5u, v);
	EXPECT_EQ(5u, i.get_pos());
}

TEST_F(Test_utils_bitset, uint8__const_iterator__peek)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	auto i = b.begin();
	ASSERT_STREQ("10101010", to_string(b).c_str());

	{
		uint8_t v;
		i.peek(v, 8);
		EXPECT_EQ(0xaa, v);
	}
	{
		uint8_t v;
		i.peek(v, 4);
		EXPECT_EQ(0xa, v);
	}
	{
		uint8_t v;
		i.peek(v, 3);
		EXPECT_EQ(5u, v);
	}
}

TEST_F(Test_utils_bitset, uint8__const_iterator__peek_no_bitset)
{
	marnav::utils::bitset<uint8_t>::const_iterator i;

	uint8_t v = 0xff;
	i.peek(v);

	EXPECT_EQ(0xff, v);
}

TEST_F(Test_utils_bitset, uint8__const_iterator__peek_to_large)
{
	marnav::utils::bitset<uint8_t> b;
	b.append(0xaa, 8);

	auto i = b.begin();

	uint32_t v;
	EXPECT_ANY_THROW(i.peek(v));
}

TEST_F(Test_utils_bitset, uint8__logic_xor_assign)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;

	a.append(0x0aaa, 16);
	b.append(0xaaa0, 16);

	a ^= b;

	EXPECT_EQ(0xa00a, a.get<uint16_t>(0));
}

TEST_F(Test_utils_bitset, uint8__logic_xor_assign__different_size)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;

	a.append(0x0a, 8);
	b.append(0xaaa0, 16);

	ASSERT_EQ(8u, a.size());

	a ^= b;

	EXPECT_EQ(16u, a.size());
	EXPECT_EQ(0xa0a0, a.get<uint16_t>(0));
}

TEST_F(Test_utils_bitset, uint8__logic_xor)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	a.append(0xaa, 8);
	b.append(0x55, 8);

	auto c = a ^ b;

	EXPECT_EQ(0xff, c.get<uint8_t>(0));
}

TEST_F(Test_utils_bitset, uint8__logic_or_assign)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	marnav::utils::bitset<uint8_t> c;

	a.append(0x00aa, 16);
	b.append(0xaa00, 16);
	c.append(0xaa, 8);

	a |= b;
	c |= b;

	EXPECT_EQ(0xaaaa, a.get<uint16_t>(0, 16));
	EXPECT_EQ(0xaa00, c.get<uint16_t>(0, 16));
}

TEST_F(Test_utils_bitset, uint8__logic_or)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	a.append(0xaa, 8);
	b.append(0x55, 8);

	auto c = a | b;

	EXPECT_EQ(0xff, c.get<uint8_t>(0));
}

TEST_F(Test_utils_bitset, uint8__logic_and_assign)
{
	{
		marnav::utils::bitset<uint8_t> a;
		marnav::utils::bitset<uint8_t> b;
		marnav::utils::bitset<uint8_t> c;

		a.append(0x00aa, 16);
		b.append(0xaa00, 16);
		c.append(0xaa, 8);

		a &= b;
		c &= b;

		EXPECT_EQ(0x0000, a.get<uint16_t>(0, 16));
		EXPECT_EQ(0xaa, c.get<uint16_t>(0, 8));
	}
	{
		marnav::utils::bitset<uint8_t> bs1;
		marnav::utils::bitset<uint8_t> bs2;

		bs1.append(7, 4); //  0111
		bs2.append(25, 5); // 11001

		bs1 &= bs2; // result: 0100

		EXPECT_EQ(4u, bs1.get<uint8_t>(0, 4));
	}
	{
		marnav::utils::bitset<uint8_t> bs1;
		marnav::utils::bitset<uint8_t> bs2;

		bs1.append(25, 5); // 11001
		bs2.append(7, 4); //  0111

		bs1 &= bs2; // result: 0100

		EXPECT_EQ(4u, bs1.get<uint8_t>(0, 4));
	}
}

TEST_F(Test_utils_bitset, uint8__logic_and)
{
	marnav::utils::bitset<uint8_t> a;
	marnav::utils::bitset<uint8_t> b;
	a.append(0xa5, 8);
	b.append(0x55, 8);

	auto c = a & b;

	EXPECT_EQ(0x05, c.get<uint8_t>(0));
}

TEST_F(Test_utils_bitset, error_get_block)
{
	marnav::utils::bitset<uint8_t> bs1;
	bs1.append(3, 4); // 0011

	const auto result = bs1.get<uint8_t>(0, 4);

	EXPECT_EQ(3u, result);
}

TEST_F(Test_utils_bitset, uint8__arithmetic__increment)
{
	{
		marnav::utils::bitset<uint8_t> b(8);

		EXPECT_STREQ("00000000", to_string(b).c_str());
		++b;
		EXPECT_STREQ("00000001", to_string(b).c_str());
		b++;
		EXPECT_STREQ("00000010", to_string(b).c_str());

		b.set(0xff, 0, 8);
		EXPECT_STREQ("11111111", to_string(b).c_str());
		++b;
		EXPECT_STREQ("00000000", to_string(b).c_str());

		b.set(0xff, 0, 8);
		EXPECT_STREQ("11111111", to_string(b).c_str());
		b++;
		EXPECT_STREQ("00000000", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b(4);

		b.set(0xf, 0, 4);
		EXPECT_STREQ("1111", to_string(b).c_str());
		++b;
		EXPECT_STREQ("0000", to_string(b).c_str());
		++b;
		EXPECT_STREQ("0001", to_string(b).c_str());
		b++;
		EXPECT_STREQ("0010", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(0xf, 20);
		ASSERT_STREQ("00000000000000001111", to_string(b).c_str());

		++b;
		EXPECT_STREQ("00000000000000010000", to_string(b).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__arithmetic__decrement)
{
	{
		marnav::utils::bitset<uint8_t> b(8);

		b.set(0xff, 0, 8);
		EXPECT_STREQ("11111111", to_string(b).c_str());
		--b;
		EXPECT_STREQ("11111110", to_string(b).c_str());
		b--;
		EXPECT_STREQ("11111101", to_string(b).c_str());

		b.set(0x00, 0, 8);
		EXPECT_STREQ("00000000", to_string(b).c_str());
		--b;
		EXPECT_STREQ("11111111", to_string(b).c_str());

		b.set(0x00, 0, 8);
		EXPECT_STREQ("00000000", to_string(b).c_str());
		b--;
		EXPECT_STREQ("11111111", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b(4);

		EXPECT_STREQ("0000", to_string(b).c_str());
		--b;
		EXPECT_STREQ("1111", to_string(b).c_str());
		--b;
		EXPECT_STREQ("1110", to_string(b).c_str());
		b--;
		EXPECT_STREQ("1101", to_string(b).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__arithmetic__increment_empty)
{
	marnav::utils::bitset<uint8_t> b;

	ASSERT_EQ(0u, b.size());
	++b;
	EXPECT_EQ(0u, b.size());
}

TEST_F(Test_utils_bitset, uint8__arithmetic__decrement_empty)
{
	marnav::utils::bitset<uint8_t> b;

	ASSERT_EQ(0u, b.size());
	--b;
	EXPECT_EQ(0u, b.size());
}

TEST_F(Test_utils_bitset, uint8__shift_left)
{
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(0xaa, 8);
		b.append(0x55, 8);
		b.append(0x0f, 8);
		b.append(0xf0, 8);
		ASSERT_STREQ("10101010010101010000111111110000", to_string(b).c_str());

		b.shl(8);
		EXPECT_STREQ("01010101000011111111000000000000", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(5, 5);
		ASSERT_STREQ("00101", to_string(b).c_str());

		b.shl(2);
		EXPECT_STREQ("10100", to_string(b).c_str());

		b.shl(1);
		EXPECT_STREQ("01000", to_string(b).c_str());

		b.shl(6);
		EXPECT_STREQ("00000", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(5, 5);
		ASSERT_STREQ("00101", to_string(b).c_str());
		b <<= 2;
		EXPECT_STREQ("10100", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(5, 5);
		ASSERT_STREQ("00101", to_string(b).c_str());
		auto t = b << 2;
		EXPECT_STREQ("10100", to_string(t).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__shift_right)
{
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(0xffff, 12);
		ASSERT_STREQ("111111111111", to_string(b).c_str());
		b.shr(5);
		EXPECT_STREQ("000001111111", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(0xf0, 8);
		b.append(0x0f, 8);
		b.append(0x0f, 8);
		b.append(0xf0, 8);
		ASSERT_STREQ("11110000000011110000111111110000", to_string(b).c_str());

		b.shr(8);
		EXPECT_STREQ("00000000111100000000111100001111", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(5, 5);
		ASSERT_STREQ("00101", to_string(b).c_str());

		b.shr(1);
		EXPECT_STREQ("00010", to_string(b).c_str());

		b.shr(1);
		EXPECT_STREQ("00001", to_string(b).c_str());

		b.shr(6);
		EXPECT_STREQ("00000", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(5, 5);
		ASSERT_STREQ("00101", to_string(b).c_str());
		b >>= 1;
		EXPECT_STREQ("00010", to_string(b).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(5, 5);
		ASSERT_STREQ("00101", to_string(b).c_str());
		auto t = b >> 1;
		EXPECT_STREQ("00010", to_string(t).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> b;
		b.append(0xaa, 8);
		ASSERT_STREQ("10101010", to_string(b).c_str());
		b.shr(1);
		EXPECT_STREQ("01010101", to_string(b).c_str());
	}
}
}
