#include <gtest/gtest.h>
#include <marnav/utils/bitset.hpp>

namespace
{

using namespace marnav::utils;

class Test_utils_bitset : public ::testing::Test
{
public:
	template <class T> std::string to_string(const bitset<T> & bits)
	{
		std::string result;
		result.reserve(bits.size());
		for (auto const & b : bits)
			result += '0' + b;
		return result;
	}
};

TEST_F(Test_utils_bitset, uint8__construction_bit_size)
{
	bitset<uint8_t> b{16};

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("0000000000000000", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_container_iterator)
{
	using namespace std;

	vector<uint8_t> v{0xaa, 0x55};
	bitset<uint8_t> b(begin(v), end(v));

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1010101001010101", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__construction_container_move)
{
	bitset<uint8_t> b(std::vector<uint8_t>{0xaa, 0x55});

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("1010101001010101", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, const_iterator_comparison_less)
{
	bitset<uint8_t> b{16};

	auto i = b.begin();
	auto j = b.begin();
	auto k = b.begin();
	++k;

	EXPECT_FALSE(i < j);
	EXPECT_TRUE(i < k);
}

TEST_F(Test_utils_bitset, const_iterator_comparison_greater)
{
	bitset<uint8_t> b{16};

	auto i = b.begin();
	auto j = b.begin();
	auto k = b.begin();
	++k;

	EXPECT_FALSE(i > j);
	EXPECT_TRUE(k > i);
}

TEST_F(Test_utils_bitset, uint8__append_single_bits)
{
	{
		bitset<uint8_t> bits;
		bits.append(1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1", to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits;
		bits.append(1, 1);
		bits.append(0, 1);
		bits.append(0, 1);
		bits.append(1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1001", to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{8};
		bits.append(1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("000000001", to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__append_block_size_plus_one)
{
	bitset<uint8_t> bits;
	bits.append(0x00000001, 9);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("000000001", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_multiple_bits)
{
	{
		bitset<uint8_t> bits;
		bits.append(0x00000001, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("01", to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits;
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
		EXPECT_STREQ("1010010001000010000010000001000000010000000010000000001",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits;

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
		bitset<uint8_t> bits;

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
		bitset<uint8_t> bits{64};
		bits.set(1, 0, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1000000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};
		bits.set(1, 1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0100000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};
		bits.set(1, 15, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000001000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};
		bits.set(1, 16, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000100000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__set_block_size_plus_one)
{
	bitset<uint8_t> bits{32};
	bits.set(0x00000001, 0, 9);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("00000000100000000000000000000000", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_multiple_bits)
{
	{
		bitset<uint8_t> bits{64};
		bits.set(0x00000001, 0, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0100000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};
		bits.set(0x00000001, 1, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0010000000000000000000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};
		bits.set(0x00000001, 15, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000100000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};
		bits.set(0x00000001, 16, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000010000000000000000000000000000000000000000000000",
			to_string(bits).c_str());
	}
	{
		bitset<uint8_t> bits{64};

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
	bitset<uint8_t> bits{64};
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
	bitset<uint8_t> bits{64};
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
	bitset<uint8_t> bits{64};
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
	bitset<uint8_t> bits{64};
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

	bitset<uint8_t> bits{64};
	bits.set(ids::A, 4, 6);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000000001000000000000000000000000000000000000000000000000000000",
		to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint16__get_multiple_bits_ending_on_block_boundary)
{
	bitset<uint16_t> bits{64};
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
	bitset<uint16_t> bits{64};
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
	bitset<uint16_t> bits{64};
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
	bitset<uint16_t> bits{64};
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
	bitset<uint8_t> bits{32};
	bits.set(1, 0, 6);

	bitset<uint8_t> copy(bits);

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+
	ASSERT_STREQ("00000100000000000000000000000000", to_string(bits).c_str());
	EXPECT_STREQ("00000100000000000000000000000000", to_string(copy).c_str());
}

TEST_F(Test_utils_bitset, uint8__assignment)
{
	bitset<uint8_t> bits{32};
	bits.set(1, 0, 6);

	bitset<uint8_t> copy{16};
	ASSERT_STREQ("0000000000000000", to_string(copy).c_str());
	copy = bits;

	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+
	ASSERT_STREQ("00000100000000000000000000000000", to_string(bits).c_str());
	EXPECT_STREQ("00000100000000000000000000000000", to_string(copy).c_str());
}

template <class T>
bitset<uint8_t> get_test_data(unsigned int size)
{
	bitset<T> result{size};

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
	ASSERT_STREQ("000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_multiple_values)
{
	bitset<uint8_t> bits{64};

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
	bitset<uint8_t> bits{64};

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
	bitset<uint8_t> b0;
	bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.append(b0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__append_bitset_to_nonempty_bitset)
{
	bitset<uint8_t> b0;
	bitset<uint8_t> b1;

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
	bitset<uint8_t> b0;
	bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_empty_bitset_mixed_type_bitsets_8_to_16)
{
	bitset<uint8_t> b0;
	bitset<uint16_t> b1;

	b0.append(0x55, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_empty_bitset_mixed_type_bitsets_16_to_8)
{
	bitset<uint16_t> b0;
	bitset<uint8_t> b1;

	b0.append(0x55, 8);
	b1.set(b0, 0);

	//            0       8       16      24      32      40      48      56
	//            +-------+
	EXPECT_STREQ("01010101", to_string(b0).c_str());
	EXPECT_STREQ("01010101", to_string(b1).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_bitset_to_nonempty_bitset)
{
	bitset<uint8_t> b0;
	bitset<uint8_t> b1;

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
	bitset<uint8_t> b{8};

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
	bitset<uint8_t> b{8};
	b.set(0xaa, 0, 8);

	EXPECT_STREQ("10101010", to_string(b).c_str());
	b.reset();
	EXPECT_STREQ("00000000", to_string(b).c_str());
}

TEST_F(Test_utils_bitset, uint8__all)
{
	{
		bitset<uint8_t> b{8};
		EXPECT_FALSE(b.all());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xaa, 0, 8);
		EXPECT_FALSE(b.all());
	}
	{
		bitset<uint8_t> b{8};
		b.set(1, 0, 8);
		EXPECT_FALSE(b.all());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xff, 0, 8);
		EXPECT_TRUE(b.all());
	}
}

TEST_F(Test_utils_bitset, uint8__any)
{
	{
		bitset<uint8_t> b{8};
		EXPECT_FALSE(b.any());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xaa, 0, 8);
		EXPECT_TRUE(b.any());
	}
	{
		bitset<uint8_t> b{8};
		b.set(1, 0, 8);
		EXPECT_TRUE(b.any());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xff, 0, 8);
		EXPECT_TRUE(b.any());
	}
}

TEST_F(Test_utils_bitset, uint8__none)
{
	{
		bitset<uint8_t> b{8};
		EXPECT_TRUE(b.none());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xaa, 0, 8);
		EXPECT_FALSE(b.none());
	}
	{
		bitset<uint8_t> b{8};
		b.set(1, 0, 8);
		EXPECT_FALSE(b.none());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xff, 0, 8);
		EXPECT_FALSE(b.none());
	}
}

TEST_F(Test_utils_bitset, uint8__count)
{
	{
		bitset<uint8_t> b{8};
		EXPECT_EQ(0u, b.count());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xaa, 0, 8);
		EXPECT_EQ(4u, b.count());
	}
	{
		bitset<uint8_t> b{8};
		b.set(1, 0, 8);
		EXPECT_EQ(1u, b.count());
	}
	{
		bitset<uint8_t> b{8};
		b.set(0xff, 0, 8);
		EXPECT_EQ(8u, b.count());
	}
}

TEST_F(Test_utils_bitset, uint8__comparison_equal)
{
	bitset<uint8_t> a;
	bitset<uint8_t> b;
	bitset<uint8_t> c;

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

TEST_F(Test_utils_bitset, uint8__comparison_not_equal)
{
	bitset<uint8_t> a;
	bitset<uint8_t> b;
	bitset<uint8_t> c;

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

TEST_F(Test_utils_bitset, uint8__append_bits_exceeds_type)
{
	bitset<uint8_t> b{32};
	const uint8_t data = 0xff;
	EXPECT_ANY_THROW(b.append(data, 16));
}

TEST_F(Test_utils_bitset, uint8__set_bits_exceeds_type)
{
	bitset<uint8_t> b{32};
	const uint8_t data = 0xff;
	EXPECT_ANY_THROW(b.set(data, 0, 16));
}

TEST_F(Test_utils_bitset, uint8__get_bits_out_of_range)
{
	bitset<uint8_t> b{32};
	uint8_t data;
	EXPECT_ANY_THROW(b.get(data, 0, 16));
	EXPECT_ANY_THROW(b.get(data, 28, 8));
	EXPECT_NO_THROW(b.get(data, 0, 0));
}

TEST_F(Test_utils_bitset, uint8__get_uint32)
{
	bitset<uint8_t> b{64};
	b.set(0xaaaaaaaa, 0, 32);
	b.set(0xaaaaaaaa, 32, 32);
	const uint32_t expected = 0xaaaaaaaa;
	uint32_t data = 0;
	b.get(data, 4);
	EXPECT_EQ(expected, data);
}

TEST_F(Test_utils_bitset, uint8__get_bit_out_of_range)
{
	bitset<uint8_t> b{32};

	EXPECT_ANY_THROW(b.get_bit(64));
}

TEST_F(Test_utils_bitset, uint8__set_bit_out_of_range)
{
	bitset<uint8_t> b{32};

	EXPECT_ANY_THROW(b.set_bit(64, 1));
}

}

