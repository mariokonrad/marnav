#include <marnav/units/units.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav::units;

TEST(basic_unit, get_dimension_from_unit)
{
	EXPECT_EQ(1, meters::dimension::len);
	EXPECT_EQ(0, meters::dimension::mas);
	EXPECT_EQ(0, meters::dimension::tim);
	EXPECT_EQ(0, meters::dimension::tem);
	EXPECT_EQ(0, meters::dimension::cur);
	EXPECT_EQ(0, meters::dimension::amt);
	EXPECT_EQ(0, meters::dimension::lum);
}

TEST(basic_unit, construct_unit_from_other_unit)
{
	// does not contain any assertion, exists just to compile

	meters a(meters{});
	feet b(meters{});

	// using square_meters = basic_unit<basic_squaremeter<double>>;
	// square_meters c(meters{});
}

TEST(basic_unit, conversion_through_construction)
{
	const auto result = meters{feet{1.0}};

	EXPECT_EQ(0.3048, result.value());
}

TEST(basic_unit, conversion_different_ratio)
{
	using half_meters = basic_unit<basic_meter<double>, std::ratio<1, 2>>;
	using quarter_meters = basic_unit<basic_meter<double>, std::ratio<1, 4>>;

	EXPECT_EQ(1000.0, millimeters{meters{1}}.value());
	EXPECT_EQ(0.001, meters{millimeters{1}}.value());

	EXPECT_EQ(2.0, half_meters{meters{1}}.value());
	EXPECT_EQ(0.5, meters{half_meters{1}}.value());

	EXPECT_EQ(4.0, quarter_meters{meters{1}}.value());
	EXPECT_EQ(0.25, meters{quarter_meters{1}}.value());
}

TEST(basic_unit, scaling_with_value_type)
{
	{
		auto result = meters{1.0};
		result *= 2.0;
		EXPECT_EQ(2.0, result.value());
	}
	{
		auto result = meters{1.0};
		result /= 2.0;
		EXPECT_EQ(0.5, result.value());
	}

	EXPECT_EQ(2.0, (meters{1.0} * 2.0).value());
	EXPECT_EQ(2.0, (2.0 * meters{1.0}).value());
	EXPECT_EQ(0.5, (meters{1.0} / 2.0).value());
}

TEST(basic_unit, unary_minus)
{
	auto l = meters{2.0};
	EXPECT_EQ(-2.0, (-l).value());
}

TEST(basic_unit, scaling_with_convertible_value_type)
{
	{
		auto result = meters{1.0};
		result *= 2.0f;
		EXPECT_EQ(2.0, result.value());
	}
	{
		auto result = meters{1.0};
		result *= 2;
		EXPECT_EQ(2.0, result.value());
	}
	{
		auto result = meters{1.0};
		result /= 2.0f;
		EXPECT_EQ(0.5, result.value());
	}
	{
		auto result = meters{1.0};
		result /= 2;
		EXPECT_EQ(0.5, result.value());
	}

	EXPECT_EQ(2.0, (meters{1.0} * 2.0f).value());
	EXPECT_EQ(2.0, (meters{1.0} * 2).value());
	EXPECT_EQ(2.0, (2 * meters{1.0}).value());
	EXPECT_EQ(0.5, (meters{1.0} / 2.0f).value());
	EXPECT_EQ(0.5, (meters{1.0} / 2).value());

	{
		struct foo {
			operator double() const noexcept { return 2.0; }
		};
		auto result = meters{1.0};
		result *= foo{};
		EXPECT_EQ(2.0, result.value());
	}
	{
		struct bar {
			operator int() const noexcept { return 2; }
		};
		auto result = meters{1.0};
		result *= bar{};
		EXPECT_EQ(2.0, result.value());
	}
}

TEST(basic_unit, add_or_sub_same_unit_to_itself)
{
	{
		auto result = meters{1.0};
		result += meters{1.0};

		EXPECT_EQ(2.0, result.value());
	}
	{
		auto result = meters{2.0};
		result -= meters{1.0};

		EXPECT_EQ(1.0, result.value());
	}
	{
		auto result = meters{1.0};
		result += feet{1.0};

		EXPECT_EQ(1.3048, result.value());
	}
}

TEST(basic_unit, add_or_sub_same_dimension_to_itself)
{
	{
		auto result = meters{1.0};
		result += feet{1.0};

		EXPECT_EQ(1.3048, result.value());
	}
	{
		auto result = meters{1.0};
		result -= feet{1.0};

		EXPECT_EQ(0.6952, result.value());
	}
}

TEST(basic_unit, add_or_sub_same_dimension_different_ratio_to_itself)
{
	{
		auto result = meters{1.0};
		result += millimeters{1.0};

		EXPECT_EQ(1.001, result.value());
	}
	{
		auto result = meters{1.0};
		result -= millimeters{1.0};

		EXPECT_EQ(0.999, result.value());
	}
}

TEST(basic_unit, comparison_equals_same_unit)
{
	EXPECT_TRUE(meters{1.0} == meters{1.0});
	EXPECT_FALSE(meters{1.0} == meters{2.0});
	EXPECT_FALSE(meters{2.0} == meters{1.0});
}

TEST(basic_unit, comparison_equals_converted_unit)
{
	EXPECT_TRUE(meters{2.4384} == feet{8.0});
	EXPECT_TRUE(feet{8.0} == meters{2.4384});
}

TEST(basic_unit, comparison_less_same_unit)
{
	EXPECT_TRUE(meters{1.0} < meters{2.0});
	EXPECT_FALSE(meters{2.0} < meters{1.0});
}

TEST(basic_unit, comparison_less_converted_unit)
{
	EXPECT_TRUE(meters{1.0} < feet{8.0});
	EXPECT_FALSE(meters{3.0} < feet{8.0});
	EXPECT_FALSE(feet{8.0} < meters{1.0});
}

TEST(basic_unit, floor)
{
	EXPECT_EQ(+1.0, floor(meters{+1.0}).value());
	EXPECT_EQ(+1.0, floor(meters{+1.4}).value());
	EXPECT_EQ(+1.0, floor(meters{+1.5}).value());
	EXPECT_EQ(+1.0, floor(meters{+1.6}).value());
	EXPECT_EQ(+2.0, floor(meters{+2.0}).value());
	EXPECT_EQ(+2.0, floor(meters{+2.5}).value());
	EXPECT_EQ(-1.0, floor(meters{-1.0}).value());
	EXPECT_EQ(-2.0, floor(meters{-1.5}).value());
	EXPECT_EQ(-2.0, floor(meters{-2.0}).value());
	EXPECT_EQ(-3.0, floor(meters{-2.5}).value());
}

TEST(basic_unit, ceil)
{
	EXPECT_EQ(+1.0, ceil(meters{+1.0}).value());
	EXPECT_EQ(+2.0, ceil(meters{+1.4}).value());
	EXPECT_EQ(+2.0, ceil(meters{+1.5}).value());
	EXPECT_EQ(+2.0, ceil(meters{+1.6}).value());
	EXPECT_EQ(+2.0, ceil(meters{+2.0}).value());
	EXPECT_EQ(+3.0, ceil(meters{+2.5}).value());
	EXPECT_EQ(-1.0, ceil(meters{-1.0}).value());
	EXPECT_EQ(-1.0, ceil(meters{-1.5}).value());
	EXPECT_EQ(-2.0, ceil(meters{-2.0}).value());
	EXPECT_EQ(-2.0, ceil(meters{-2.5}).value());
}

TEST(basic_unit, round)
{
	EXPECT_EQ(+1.0, round(meters{+1.0}).value());
	EXPECT_EQ(+1.0, round(meters{+1.4}).value());
	EXPECT_EQ(+2.0, round(meters{+1.5}).value());
	EXPECT_EQ(+2.0, round(meters{+1.6}).value());
	EXPECT_EQ(+2.0, round(meters{+2.0}).value());
	EXPECT_EQ(+3.0, round(meters{+2.5}).value());
	EXPECT_EQ(-1.0, round(meters{-1.0}).value());
	EXPECT_EQ(-2.0, round(meters{-1.5}).value());
	EXPECT_EQ(-2.0, round(meters{-2.0}).value());
	EXPECT_EQ(-3.0, round(meters{-2.5}).value());
}

TEST(basic_unit, abs)
{
	EXPECT_EQ(1.0, abs(meters{+1.0}).value());
	EXPECT_EQ(1.4, abs(meters{+1.4}).value());
	EXPECT_EQ(1.5, abs(meters{+1.5}).value());
	EXPECT_EQ(1.6, abs(meters{+1.6}).value());
	EXPECT_EQ(2.0, abs(meters{+2.0}).value());
	EXPECT_EQ(2.5, abs(meters{+2.5}).value());
	EXPECT_EQ(1.0, abs(meters{-1.0}).value());
	EXPECT_EQ(1.5, abs(meters{-1.5}).value());
	EXPECT_EQ(2.0, abs(meters{-2.0}).value());
	EXPECT_EQ(2.5, abs(meters{-2.5}).value());
}
}
