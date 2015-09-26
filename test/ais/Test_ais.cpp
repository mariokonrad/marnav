#include <gtest/gtest.h>
#include <marnav/ais/ais.hpp>

namespace
{

using namespace marnav;

class Test_ais : public ::testing::Test
{
};

class message_zero_bits : public ais::message
{
public:
	message_zero_bits()
		: message(ais::message_id::NONE)
	{
	}

	virtual ais::raw get_data() const throw(std::out_of_range) override { return ais::raw{}; }
};

TEST_F(Test_ais, make_message)
{
	using namespace std;

	vector<pair<string, int>> v;

	// v.push_back(make_pair("55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0));
	// v.push_back(make_pair("1@0000000000000", 2));

	// v.push_back(make_pair("177KQJ5000G?tO`K>RA1wUbN0TKH", 0));

	v.push_back(make_pair("133m@ogP00PD;88MD5MTDww@2D7k", 0));

	auto result = ais::make_message(v);
}

TEST_F(Test_ais, encode_message_zero_sized_bits)
{
	message_zero_bits m;
	EXPECT_ANY_THROW(ais::encode_message(m));
}
}
