#include <marnav/utils/optional.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_utils_optional : public ::testing::Test
{
public:
	struct struc {
		int value = 0;

		struc() {}

		struc(int v)
			: value(v)
		{
		}

		bool operator==(const struc & other) const noexcept { return value == other.value; }
	};

	struct A {
		using value_type = int;

		utils::optional<value_type> data;

		A() = default;

		A(value_type value)
			: data(value)
		{
		}

		utils::optional<value_type> get() const { return data; }
		utils::optional<value_type> & get_ref() { return data; }
		const utils::optional<value_type> & get_const_ref() const { return data; }
	};

	template <class T>
	void test()
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
		EXPECT_TRUE(std::is_nothrow_copy_assignable<opt>::value);
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

TEST_F(Test_utils_optional, default_constructor)
{
	const auto opt = utils::optional<int>{};

	EXPECT_FALSE(opt.has_value());
	EXPECT_TRUE(static_cast<bool>(opt) == false);
}

TEST_F(Test_utils_optional, const_ref_constructor)
{
	const auto s = struc{99};

	const auto opt = utils::optional<struc>(s);

	EXPECT_TRUE(opt.has_value());
}

TEST_F(Test_utils_optional, ref_ref_constructor)
{
	struc s{99};

	const auto opt = utils::optional<struc>(std::move(s));

	EXPECT_TRUE(opt.has_value());
}

TEST_F(Test_utils_optional, copy_constructor)
{
	const auto opt1 = utils::optional<int>(10);
	ASSERT_TRUE(opt1.has_value());

	const auto opt2(opt1);
	EXPECT_TRUE(opt1.has_value());
	EXPECT_TRUE(opt2.has_value());
}

TEST_F(Test_utils_optional, move_constructor)
{
	auto opt1 = utils::optional<int>(10);
	ASSERT_TRUE(opt1.has_value());

	const auto opt2(std::move(opt1));
	EXPECT_TRUE(opt2.has_value());
}

TEST_F(Test_utils_optional, const_ref_value)
{
	const auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	const auto s = struc{99};
	const auto & r = opt.value();
	EXPECT_EQ(s, r);
}

TEST_F(Test_utils_optional, ref_ref_value)
{
	auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	const auto s = struc{99};
	auto && r = opt.value();
	EXPECT_EQ(s, r);
}

TEST_F(Test_utils_optional, reset)
{
	auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	opt.reset();
	EXPECT_FALSE(opt.has_value());
}

TEST_F(Test_utils_optional, reset_non_initialized)
{
	auto opt = utils::optional<struc>();
	ASSERT_FALSE(opt.has_value());

	opt.reset();
	EXPECT_FALSE(opt.has_value());
}

TEST_F(Test_utils_optional, available)
{
	auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());
	EXPECT_TRUE(opt.available());
}

TEST_F(Test_utils_optional, available_non_intialized)
{
	auto opt = utils::optional<struc>();
	ASSERT_FALSE(opt.has_value());
	EXPECT_FALSE(opt.available());
}

TEST_F(Test_utils_optional, dereference)
{
	auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	const auto expected = struc{99};
	auto & r = *opt;
	EXPECT_EQ(expected, r);
}

TEST_F(Test_utils_optional, dereference_const)
{
	const auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	const auto expected = struc{99};
	const auto & r = *opt;
	EXPECT_EQ(expected, r);
}

TEST_F(Test_utils_optional, pointer_op)
{
	auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	const auto expected = struc{99};
	auto & value = opt->value;
	EXPECT_EQ(expected.value, value);
}

TEST_F(Test_utils_optional, pointer_op_const)
{
	const auto opt = utils::optional<struc>(99);
	ASSERT_TRUE(opt.has_value());

	const auto expected = struc{99};
	EXPECT_EQ(expected.value, opt->value);
}

TEST_F(Test_utils_optional, direct_access_to_value)
{
	auto a = A{10};
	EXPECT_EQ(10, a.get().value());
	EXPECT_EQ(10, a.get_ref().value());
	EXPECT_EQ(10, a.get_const_ref().value());
}

TEST_F(Test_utils_optional, direct_access_to_value_const)
{
	const auto a = A{10};
	EXPECT_EQ(10, a.get().value());
	EXPECT_EQ(10, a.get_const_ref().value());
}

TEST_F(Test_utils_optional, direct_access_to_value_invalid)
{
	auto a = A{};
	const auto expected = A::value_type{};

	EXPECT_EQ(expected, a.get().value());
	EXPECT_EQ(expected, a.get_ref().value());
	EXPECT_EQ(expected, a.get_const_ref().value());
}
}
