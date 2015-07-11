#include <gtest/gtest.h>
#include <marnav/utils/bitset.hpp>

namespace
{

class Test_utils_bitset : public ::testing::Test
{
public:
	template <class T>
	std::string to_string(const marnav::utils::bitset<T> & bits)
	{
		std::string result;
		result.reserve(bits.size());
		for (auto const & b : bits)
			result += '0' + b;
		return result;
	}
};

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
		marnav::utils::bitset<uint8_t> bits{8};
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
		EXPECT_STREQ("1010010001000010000010000001000000010000000010000000001", to_string(bits).c_str());
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
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(1, 0, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("1000000000000000000000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(1, 1, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0100000000000000000000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(1, 15, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000001000000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(1, 16, 1);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000100000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__set_block_size_plus_one)
{
	marnav::utils::bitset<uint8_t> bits{32};
	bits.set(0x00000001, 0, 9);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	EXPECT_STREQ("00000000100000000000000000000000", to_string(bits).c_str());
}

TEST_F(Test_utils_bitset, uint8__set_multiple_bits)
{
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(0x00000001, 0, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0100000000000000000000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(0x00000001, 1, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0010000000000000000000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(0x00000001, 15, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000100000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};
		bits.set(0x00000001, 16, 2);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000000000000010000000000000000000000000000000000000000000000", to_string(bits).c_str());
	}
	{
		marnav::utils::bitset<uint8_t> bits{64};

		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		//            111010011110101011001111111111
		const uint32_t value = 981119999; // 30 bits of information

		bits.set(value, 8, 30);
		//            0       8       16      24      32      40      48      56
		//            +-------+-------+-------+-------+-------+-------+-------+-------
		EXPECT_STREQ("0000000011101001111010101100111111111100000000000000000000000000", to_string(bits).c_str());
	}
}

TEST_F(Test_utils_bitset, uint8__get_multiple_bits)
{
	marnav::utils::bitset<uint8_t> bits{64};
	bits.set(0xff, 5, 3);
	//            0       8       16      24      32      40      48      56
	//            +-------+-------+-------+-------+-------+-------+-------+-------
	ASSERT_STREQ("0000011100000000000000000000000000000000000000000000000000000000", to_string(bits).c_str());

	uint32_t value = 0xffffffff;
	bits.get(value, 0, 6);
	EXPECT_EQ(1u, value);
}

}

