#include <gtest/gtest.h>
#include <marnav/utils/optional.hpp>

namespace
{
using namespace marnav;

class Test_utils_optional : public ::testing::Test
{
public:
	template <class T> void test()
	{
		using opt = utils::optional<T>;

		EXPECT_TRUE(std::is_constructible<opt>::value);
		// EXPECT_TRUE(std::is_trivially_constructible<opt>::value);
		EXPECT_TRUE(std::is_default_constructible<opt>::value);
		EXPECT_TRUE(std::is_nothrow_constructible<opt>::value);
		EXPECT_TRUE(std::is_copy_constructible<opt>::value);
		// EXPECT_TRUE(std::is_trivially_copy_constructible<opt>::value);
		EXPECT_TRUE(std::is_move_constructible<opt>::value);
		EXPECT_TRUE(std::is_copy_assignable<opt>::value);
		EXPECT_FALSE(std::is_nothrow_copy_assignable<opt>::value);
		// EXPECT_TRUE(std::is_trivially_copy_assignable<opt>::value);
		EXPECT_TRUE(std::is_move_assignable<opt>::value);
		EXPECT_TRUE(std::is_destructible<opt>::value);
	}
};

TEST_F(Test_utils_optional, properties)
{
	test<int>();
	test<double>();
}
}
