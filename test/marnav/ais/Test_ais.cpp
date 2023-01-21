#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_ais : public ::testing::Test
{
public:
	struct entry {
		uint8_t value;
		char c;
	};

	static const std::vector<entry> ARMORING_ENTRIES;
};

const std::vector<test_ais::entry> test_ais::ARMORING_ENTRIES = {
	{0, '0'},
	{1, '1'},
	{2, '2'},
	{3, '3'},
	{4, '4'},
	{5, '5'},
	{6, '6'},
	{7, '7'},
	{8, '8'},
	{9, '9'},
	{10, ':'},
	{11, ';'},
	{12, '<'},
	{13, '='},
	{14, '>'},
	{15, '?'},
	{16, '@'},
	{17, 'A'},
	{18, 'B'},
	{19, 'C'},
	{20, 'D'},
	{21, 'E'},
	{22, 'F'},
	{23, 'G'},
	{24, 'H'},
	{25, 'I'},
	{26, 'J'},
	{27, 'K'},
	{28, 'L'},
	{29, 'M'},
	{30, 'N'},
	{31, 'O'},
	{32, 'P'},
	{33, 'Q'},
	{34, 'R'},
	{35, 'S'},
	{36, 'T'},
	{37, 'U'},
	{38, 'V'},
	{39, 'W'},
	{40, '`'},
	{41, 'a'},
	{42, 'b'},
	{43, 'c'},
	{44, 'd'},
	{45, 'e'},
	{46, 'f'},
	{47, 'g'},
	{48, 'h'},
	{49, 'i'},
	{50, 'j'},
	{51, 'k'},
	{52, 'l'},
	{53, 'm'},
	{54, 'n'},
	{55, 'o'},
	{56, 'p'},
	{57, 'q'},
	{58, 'r'},
	{59, 's'},
	{60, 't'},
	{61, 'u'},
	{62, 'v'},
	{63, 'w'},
};

class message_zero_bits : public ais::message
{
public:
	message_zero_bits()
		: message(ais::message_id::NONE)
	{
	}

	ais::raw get_data() const override { return ais::raw{}; }
};

TEST_F(test_ais, make_message)
{
	using namespace std;

	vector<pair<string, uint32_t>> v;

	// v.push_back(make_pair("55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0));
	// v.push_back(make_pair("1@0000000000000", 2));

	// v.push_back(make_pair("177KQJ5000G?tO`K>RA1wUbN0TKH", 0));

	v.emplace_back("133m@ogP00PD;88MD5MTDww@2D7k", 0);

	auto result = ais::make_message(v);
}

TEST_F(test_ais, encode_message_zero_sized_bits)
{
	message_zero_bits m;
	EXPECT_ANY_THROW(ais::encode_message(m));
}

TEST_F(test_ais, decode_armoring)
{
	for (auto const & e : ARMORING_ENTRIES) {
		EXPECT_EQ(e.value, ais::decode_armoring(e.c));
	}
}

TEST_F(test_ais, encode_armoring)
{
	for (auto const & e : ARMORING_ENTRIES) {
		EXPECT_EQ(e.c, ais::encode_armoring(e.value));
	}
}
}
