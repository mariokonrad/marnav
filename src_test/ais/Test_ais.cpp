#include <gtest/gtest.h>
#include <ais/ais.hpp>

namespace
{

class Test_ais : public ::testing::Test
{
};

TEST_F(Test_ais, make_message)
{
	std::vector<std::pair<std::string, int>> v;
//	v.push_back(std::make_pair("55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0));
//	v.push_back(std::make_pair("1@0000000000000", 2));
	v.push_back(std::make_pair("177KQJ5000G?tO`K>RA1wUbN0TKH", 0));

	auto result = ais::make_message(v);
}

}
