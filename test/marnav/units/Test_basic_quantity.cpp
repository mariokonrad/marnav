#include <marnav/units/units.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav::units;

TEST(basic_quantity, get_dimension_from_quantity)
{
	EXPECT_EQ(1, length::dimension::len);
	EXPECT_EQ(0, length::dimension::mas);
	EXPECT_EQ(0, length::dimension::tim);
	EXPECT_EQ(0, length::dimension::tem);
	EXPECT_EQ(0, length::dimension::cur);
	EXPECT_EQ(0, length::dimension::amt);
	EXPECT_EQ(0, length::dimension::lum);
}

TEST(basic_quantity, construct_quantity_from_unit)
{
	const length q1(meters{1});

	EXPECT_EQ(1.0, q1.value());

	// using squaremeters = basic_unit<basic_squaremeter<double>>;
	// length q2(squaremeters{});
}

TEST(basic_quantity, retrieve_units_from_quantity)
{
	const length q1(feet{1.0});
	EXPECT_EQ(0.3048, q1.get<meters>().value());
	EXPECT_EQ(1.0, q1.get<feet>().value());

	// using meter2 = basic_unit<basic_squaremeter<double>>;
	// const meter2 sq = q1.get<meter2>();
}

TEST(basic_quantity, retrieve_units_from_quantity_different_ratio)
{
	const length q1(meters{100.0});
	EXPECT_EQ(0.1, q1.get<kilometers>().value());
	EXPECT_EQ(100000.0, q1.get<millimeters>().value());
}

TEST(basic_quantity, scale_onto_self_with_value_type)
{
	{
		length q{meters{1.0}};
		q *= 2.0;
		EXPECT_EQ(2.0, q.value());
	}
	{
		length q{meters{1.0}};
		q /= 2.0;
		EXPECT_EQ(0.5, q.value());
	}
}

TEST(basic_quantity, scale_onto_self_with_convertible_type)
{
	{
		length q{meters{1.0}};
		q *= 2.0f;
		EXPECT_EQ(2.0, q.value());
	}
	{
		length q{meters{1.0}};
		q *= 2;
		EXPECT_EQ(2.0, q.value());
	}
	{
		length q{meters{1.0}};
		q /= 2.0f;
		EXPECT_EQ(0.5, q.value());
	}
	{
		length q{meters{1.0}};
		q /= 2;
		EXPECT_EQ(0.5, q.value());
	}
	{
		struct foo {
			operator double() const { return 2.0; }
		};

		length q{meters{1.0}};
		q *= foo{};
		EXPECT_EQ(2.0, q.value());
	}
	{
		struct foo {
			operator int() const { return 2; }
		};

		length q{meters{1.0}};
		q *= foo{};
		EXPECT_EQ(2.0, q.value());
	}
}

TEST(basic_quantity, unary_minus)
{
	auto l = length{meters{2.0}};
	EXPECT_EQ(-2.0, (-l).value());
}

TEST(basic_quantity, add_onto_self)
{
	length q{meters{2}};

	q += length{meters{1}};

	EXPECT_EQ(3.0, q.value());
}

TEST(basic_quantity, sub_onto_self)
{
	length q{meters{2}};

	q -= length{meters{1}};

	EXPECT_EQ(1.0, q.value());
}

TEST(basic_quantity, add)
{
	const length q1{meters{2}};
	const length q2{feet{1}};

	const length q = q1 + q2;

	EXPECT_EQ(2.3048, q.value());
}

TEST(basic_quantity, add_units_resulting_quanity)
{
	const auto l1 = meters{2};
	const auto l2 = feet{1};

	const length q = l1 + l2;

	EXPECT_EQ(2.3048, q.value());
}

TEST(basic_quantity, sub)
{
	const length q1{meters{2}};
	const length q2{feet{1}};

	const length q = q1 - q2;

	EXPECT_EQ(1.6952, q.value());
}

TEST(basic_quantity, sub_units_resulting_quantity)
{
	const auto l1 = meters{2};
	const auto l2 = feet{1};

	const length q = l1 - l2;

	EXPECT_EQ(1.6952, q.value());
}

TEST(basic_quantity, mul)
{
	const auto q = length{meters{2}} * length{meters{3}};

	EXPECT_EQ(6.0, q.value());

	using dim = decltype(q)::dimension;

	EXPECT_EQ(2, dim::len);
	EXPECT_EQ(0, dim::mas);
	EXPECT_EQ(0, dim::tim);
	EXPECT_EQ(0, dim::tem);
	EXPECT_EQ(0, dim::cur);
	EXPECT_EQ(0, dim::amt);
	EXPECT_EQ(0, dim::lum);
}

TEST(basic_quantity, mul_units_resulting_in_quantity)
{
	{
		const auto q = meters{2} * meters{3};

		EXPECT_EQ(6.0, q.value());

		using dim = decltype(q)::dimension;

		EXPECT_EQ(2, dim::len);
		EXPECT_EQ(0, dim::mas);
		EXPECT_EQ(0, dim::tim);
		EXPECT_EQ(0, dim::tem);
		EXPECT_EQ(0, dim::cur);
		EXPECT_EQ(0, dim::amt);
		EXPECT_EQ(0, dim::lum);
	}
	{
		const auto q = meters{2} * feet{3};

		EXPECT_NEAR(1.8288, q.value(), 1e-4);

		using dim = decltype(q)::dimension;

		EXPECT_EQ(2, dim::len);
		EXPECT_EQ(0, dim::mas);
		EXPECT_EQ(0, dim::tim);
		EXPECT_EQ(0, dim::tem);
		EXPECT_EQ(0, dim::cur);
		EXPECT_EQ(0, dim::amt);
		EXPECT_EQ(0, dim::lum);
	}
}

TEST(basic_quantity, div)
{
	const auto q = area{squaremeters{6}} / length{meters{2}};

	EXPECT_EQ(3.0, q.value());

	using dim = decltype(q)::dimension;

	EXPECT_EQ(1, dim::len);
	EXPECT_EQ(0, dim::mas);
	EXPECT_EQ(0, dim::tim);
	EXPECT_EQ(0, dim::tem);
	EXPECT_EQ(0, dim::cur);
	EXPECT_EQ(0, dim::amt);
	EXPECT_EQ(0, dim::lum);
}

TEST(basic_quantity, div_units_resuling_in_quantity)
{
	{
		const auto q = squaremeters{6} / meters{2};

		EXPECT_EQ(3.0, q.value());

		using dim = decltype(q)::dimension;

		EXPECT_EQ(1, dim::len);
		EXPECT_EQ(0, dim::mas);
		EXPECT_EQ(0, dim::tim);
		EXPECT_EQ(0, dim::tem);
		EXPECT_EQ(0, dim::cur);
		EXPECT_EQ(0, dim::amt);
		EXPECT_EQ(0, dim::lum);
	}
	{
		const auto q = squaremeters{6} / feet{2};

		EXPECT_NEAR(9.84252, q.value(), 1e-5);

		using dim = decltype(q)::dimension;

		EXPECT_EQ(1, dim::len);
		EXPECT_EQ(0, dim::mas);
		EXPECT_EQ(0, dim::tim);
		EXPECT_EQ(0, dim::tem);
		EXPECT_EQ(0, dim::cur);
		EXPECT_EQ(0, dim::amt);
		EXPECT_EQ(0, dim::lum);
	}
}

TEST(basic_quantity, floor)
{
	EXPECT_EQ(+1.0, floor(length{meters{+1.0}}).value());
	EXPECT_EQ(+1.0, floor(length{meters{+1.4}}).value());
	EXPECT_EQ(+1.0, floor(length{meters{+1.5}}).value());
	EXPECT_EQ(+1.0, floor(length{meters{+1.6}}).value());
	EXPECT_EQ(+2.0, floor(length{meters{+2.0}}).value());
	EXPECT_EQ(+2.0, floor(length{meters{+2.5}}).value());
	EXPECT_EQ(-1.0, floor(length{meters{-1.0}}).value());
	EXPECT_EQ(-2.0, floor(length{meters{-1.5}}).value());
	EXPECT_EQ(-2.0, floor(length{meters{-2.0}}).value());
	EXPECT_EQ(-3.0, floor(length{meters{-2.5}}).value());
}

TEST(basic_quantity, ceil)
{
	EXPECT_EQ(+1.0, ceil(length{meters{+1.0}}).value());
	EXPECT_EQ(+2.0, ceil(length{meters{+1.4}}).value());
	EXPECT_EQ(+2.0, ceil(length{meters{+1.5}}).value());
	EXPECT_EQ(+2.0, ceil(length{meters{+1.6}}).value());
	EXPECT_EQ(+2.0, ceil(length{meters{+2.0}}).value());
	EXPECT_EQ(+3.0, ceil(length{meters{+2.5}}).value());
	EXPECT_EQ(-1.0, ceil(length{meters{-1.0}}).value());
	EXPECT_EQ(-1.0, ceil(length{meters{-1.5}}).value());
	EXPECT_EQ(-2.0, ceil(length{meters{-2.0}}).value());
	EXPECT_EQ(-2.0, ceil(length{meters{-2.5}}).value());
}

TEST(basic_quantity, round)
{
	EXPECT_EQ(+1.0, round(length{meters{+1.0}}).value());
	EXPECT_EQ(+1.0, round(length{meters{+1.4}}).value());
	EXPECT_EQ(+2.0, round(length{meters{+1.5}}).value());
	EXPECT_EQ(+2.0, round(length{meters{+1.6}}).value());
	EXPECT_EQ(+2.0, round(length{meters{+2.0}}).value());
	EXPECT_EQ(+3.0, round(length{meters{+2.5}}).value());
	EXPECT_EQ(-1.0, round(length{meters{-1.0}}).value());
	EXPECT_EQ(-2.0, round(length{meters{-1.5}}).value());
	EXPECT_EQ(-2.0, round(length{meters{-2.0}}).value());
	EXPECT_EQ(-3.0, round(length{meters{-2.5}}).value());
}

TEST(basic_quantity, abs)
{
	EXPECT_EQ(1.0, abs(length{meters{+1.0}}).value());
	EXPECT_EQ(1.4, abs(length{meters{+1.4}}).value());
	EXPECT_EQ(1.5, abs(length{meters{+1.5}}).value());
	EXPECT_EQ(1.6, abs(length{meters{+1.6}}).value());
	EXPECT_EQ(2.0, abs(length{meters{+2.0}}).value());
	EXPECT_EQ(2.5, abs(length{meters{+2.5}}).value());
	EXPECT_EQ(1.0, abs(length{meters{-1.0}}).value());
	EXPECT_EQ(1.5, abs(length{meters{-1.5}}).value());
	EXPECT_EQ(2.0, abs(length{meters{-2.0}}).value());
	EXPECT_EQ(2.5, abs(length{meters{-2.5}}).value());
}

TEST(basic_quantity, comparison_equal)
{
	EXPECT_TRUE(length{meters{1}} == length{meters{1}});
	EXPECT_FALSE(length{meters{1}} == length{feet{1}});
}

TEST(basic_quantity, comparison_less)
{
	EXPECT_TRUE(length{meters{1}} < length{meters{2}});
	EXPECT_TRUE(length{meters{1}} < length{feet{8}});
	EXPECT_FALSE(length{meters{1}} < length{meters{1}});
	EXPECT_FALSE(length{meters{2}} < length{meters{1}});
	EXPECT_FALSE(length{feet{4}} < length{meters{1}});
}
}
