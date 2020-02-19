#include <marnav/units/units.hpp>
#include <gtest/gtest.h>
#include <cmath>

namespace custom
{
template <class T> class basic_number
{
public:
	using value_type = T;

public: // construction and assignment
	// `explicit` on purpose
	constexpr explicit basic_number(const value_type & value) noexcept
		: value_(value)
	{
	}

	constexpr basic_number() = default;

	basic_number(const basic_number &) noexcept = default;
	basic_number & operator=(const basic_number &) noexcept = default;

	basic_number(basic_number &&) noexcept = default;
	basic_number & operator=(basic_number &&) noexcept = default;

public: // comparison
	// clang-format off
	template <class U> friend constexpr bool operator==(const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr bool operator!=(const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr bool operator< (const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr bool operator<=(const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr bool operator> (const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr bool operator>=(const basic_number<U> &, const basic_number<U> &) noexcept;
	// clang-format on

public: // basic functions
	// clang-format off
	template <class U> friend constexpr basic_number<U> floor(const basic_number<U> &) noexcept;
	template <class U> friend constexpr basic_number<U> ceil (const basic_number<U> &) noexcept;
	template <class U> friend constexpr basic_number<U> round(const basic_number<U> &) noexcept;
	template <class U> friend constexpr basic_number<U> abs  (const basic_number<U> &) noexcept;
	// clang-format on

public: // basic math operators
	// clang-format off
	basic_number & operator+=(const basic_number & n) noexcept { value_ += n.value_; return *this; }
	basic_number & operator-=(const basic_number & n) noexcept { value_ -= n.value_; return *this; }
	basic_number & operator*=(const basic_number & n) noexcept { value_ *= n.value_; return *this; }
	basic_number & operator/=(const basic_number & n) noexcept { value_ /= n.value_; return *this; }

	template <class U> friend constexpr basic_number<U> operator+(const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr basic_number<U> operator-(const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr basic_number<U> operator*(const basic_number<U> &, const basic_number<U> &) noexcept;
	template <class U> friend constexpr basic_number<U> operator/(const basic_number<U> &, const basic_number<U> &) noexcept;
	// clang-format on

private:
	value_type value_ = 0.0;
};

template <class U>
constexpr bool operator==(const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return std::abs(a.value_ - b.value_) < 1e-8;
}

template <class U>
constexpr bool operator!=(const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return !(a == b);
}

template <class U>
constexpr bool operator<(const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return a.value_ < b.value_;
}

template <class U>
constexpr bool operator<=(const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return (a < b) || (a == b);
}

template <class U>
constexpr bool operator>(const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return !(a <= b);
}

template <class U>
constexpr bool operator>=(const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return !(a < b);
}

template <class U> constexpr basic_number<U> floor(const basic_number<U> & n) noexcept
{
	return basic_number<U>(::floor(n.value_));
}

template <class U> constexpr basic_number<U> ceil(const basic_number<U> & n) noexcept
{
	return basic_number<U>(::ceil(n.value_));
}

template <class U> constexpr basic_number<U> round(const basic_number<U> & n) noexcept
{
	return basic_number<U>(::round(n.value_));
}

template <class U> constexpr basic_number<U> abs(const basic_number<U> & n) noexcept
{
	return basic_number<U>(std::abs(n.value_));
}

template <class U>
constexpr basic_number<U> operator+(
	const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return basic_number<U>{a.value_ + b.value_};
}

template <class U>
constexpr basic_number<U> operator-(
	const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return basic_number<U>{a.value_ - b.value_};
}

template <class U>
constexpr basic_number<U> operator*(
	const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return basic_number<U>{a.value_ * b.value_};
}

template <class U>
constexpr basic_number<U> operator/(
	const basic_number<U> & a, const basic_number<U> & b) noexcept
{
	return basic_number<U>{a.value_ / b.value_};
}

template <class U>
constexpr basic_number<U> operator*(
	const basic_number<U> & n, const typename basic_number<U>::value_type & v) noexcept
{
	return basic_number<U>{n.value_ * v};
}

template <class U>
constexpr basic_number<U> operator*(
	const typename basic_number<U>::value_type & v, const basic_number<U> & n) noexcept
{
	return basic_number<U>{n.value_ * v};
}

template <class U>
constexpr basic_number<U> operator/(
	const basic_number<U> & n, const typename basic_number<U>::value_type & v) noexcept
{
	return basic_number<U>{n.value_ / v};
}

// clang-format off
using number = basic_number<double>;

using meters         = marnav::units::basic_unit<marnav::units::basic_meter        <number>>;
using inches         = marnav::units::basic_unit<marnav::units::basic_inch         <number>>;
using yards          = marnav::units::basic_unit<marnav::units::basic_yard         <number>>;
using feet           = marnav::units::basic_unit<marnav::units::basic_foot         <number>>;
using imperial_miles = marnav::units::basic_unit<marnav::units::basic_imperial_mile<number>>;
using nautical_miles = marnav::units::basic_unit<marnav::units::basic_nautical_mile<number>>;
using fathoms        = marnav::units::basic_unit<marnav::units::basic_fathom       <number>>;
using millimeters    = marnav::units::basic_unit<marnav::units::basic_meter        <number>, std::milli>;
using kilometers     = marnav::units::basic_unit<marnav::units::basic_meter        <number>, std::kilo>;
// clang-format on
}

namespace
{
TEST(custom_numeric_type, construct_unit)
{
	custom::meters m(custom::number(1.0));

	EXPECT_EQ(custom::number(1.0), m.value());
}

TEST(custom_numeric_type, conversion_through_construction)
{
	const auto result = custom::meters{custom::feet{custom::number(1.0)}};

	EXPECT_EQ(custom::number(0.3048), result.value());
}

TEST(basic_unit, conversion_different_ratio)
{
	using half_meters = marnav::units::basic_unit<marnav::units::basic_meter<custom::number>,
		std::ratio<1, 2>>;
	using quarter_meters = marnav::units::basic_unit<marnav::units::basic_meter<custom::number>,
		std::ratio<1, 4>>;

	EXPECT_EQ(
		custom::number(1000.0), custom::millimeters{custom::meters{custom::number(1)}}.value());
	EXPECT_EQ(
		custom::number(0.001), custom::meters{custom::millimeters{custom::number(1)}}.value());

	EXPECT_EQ(custom::number(2.0), half_meters{custom::meters{custom::number(1)}}.value());
	EXPECT_EQ(custom::number(0.5), custom::meters{half_meters{custom::number(1)}}.value());

	EXPECT_EQ(custom::number(4.0), quarter_meters{custom::meters{custom::number(1)}}.value());
	EXPECT_EQ(custom::number(0.25), custom::meters{quarter_meters{custom::number(1)}}.value());
}

TEST(custom_numeric_type, scaling_with_value_type)
{
	{
		auto result = custom::meters{custom::number(1.0)};
		result *= custom::number(2.0);
		EXPECT_EQ(custom::number(2.0), result.value());
	}
	{
		auto result = custom::meters{custom::number(1.0)};
		result /= custom::number(2.0);
		EXPECT_EQ(custom::number(0.5), result.value());
	}

	EXPECT_EQ(custom::number(2.0),
		(custom::meters{custom::number(1.0)} * custom::number(2.0)).value());
	EXPECT_EQ(custom::number(2.0),
		(custom::number(2.0) * custom::meters{custom::number(1.0)}).value());
	EXPECT_EQ(custom::number(0.5),
		(custom::meters{custom::number(1.0)} / custom::number(2.0)).value());
}

TEST(custom_numeric_type, add_or_sub_same_unit_to_itself)
{
	{
		auto result = custom::meters{custom::number(1.0)};
		result += custom::meters{custom::number(1.0)};

		EXPECT_EQ(custom::number(2.0), result.value());
	}
	{
		auto result = custom::meters{custom::number(2.0)};
		result -= custom::meters{custom::number(1.0)};

		EXPECT_EQ(custom::number(1.0), result.value());
	}
	{
		auto result = custom::meters{custom::number(1.0)};
		result += custom::feet{custom::number(1.0)};

		EXPECT_EQ(custom::number(1.3048), result.value());
	}
}

TEST(custom_numeric_type, add_or_sub_same_dimension_to_itself)
{
	{
		auto result = custom::meters{custom::number(1.0)};
		result += custom::feet{custom::number(1.0)};

		EXPECT_EQ(custom::number(1.3048), result.value());
	}
	{
		auto result = custom::meters{custom::number(1.0)};
		result -= custom::feet{custom::number(1.0)};

		EXPECT_EQ(custom::number(0.6952), result.value());
	}
}

TEST(custom_numeric_type, add_or_sub_same_dimension_different_ratio_to_itself)
{
	{
		auto result = custom::meters{custom::number(1.0)};
		result += custom::millimeters{custom::number(1.0)};

		EXPECT_EQ(custom::number(1.001), result.value());
	}
	{
		auto result = custom::meters{custom::number(1.0)};
		result -= custom::millimeters{custom::number(1.0)};

		EXPECT_EQ(custom::number(0.999), result.value());
	}
}

TEST(custom_numeric_type, comparison_equals_same_unit)
{
	EXPECT_TRUE(custom::meters{custom::number(1.0)} == custom::meters{custom::number(1.0)});
	EXPECT_FALSE(custom::meters{custom::number(1.0)} == custom::meters{custom::number(2.0)});
	EXPECT_FALSE(custom::meters{custom::number(2.0)} == custom::meters{custom::number(1.0)});
}

TEST(custom_numeric_type, comparison_equals_converted_unit)
{
	EXPECT_TRUE(custom::meters{custom::number(2.4384)} == custom::feet{custom::number(8.0)});
	EXPECT_TRUE(custom::feet{custom::number(8.0)} == custom::meters{custom::number(2.4384)});
}

TEST(custom_numeric_type, comparison_less_same_unit)
{
	EXPECT_TRUE(custom::meters{custom::number(1.0)} < custom::meters{custom::number(2.0)});
	EXPECT_FALSE(custom::meters{custom::number(2.0)} < custom::meters{custom::number(1.0)});
}

TEST(custom_numeric_type, comparison_less_converted_unit)
{
	EXPECT_TRUE(custom::meters{custom::number(1.0)} < custom::feet{custom::number(8.0)});
	EXPECT_FALSE(custom::meters{custom::number(3.0)} < custom::feet{custom::number(8.0)});
	EXPECT_FALSE(custom::feet{custom::number(8.0)} < custom::meters{custom::number(1.0)});
}

TEST(custom_numeric_type, floor)
{
	EXPECT_EQ(custom::number(+1.0), floor(custom::meters{custom::number(+1.0)}).value());
	EXPECT_EQ(custom::number(+1.0), floor(custom::meters{custom::number(+1.4)}).value());
	EXPECT_EQ(custom::number(+1.0), floor(custom::meters{custom::number(+1.5)}).value());
	EXPECT_EQ(custom::number(+1.0), floor(custom::meters{custom::number(+1.6)}).value());
	EXPECT_EQ(custom::number(+2.0), floor(custom::meters{custom::number(+2.0)}).value());
	EXPECT_EQ(custom::number(+2.0), floor(custom::meters{custom::number(+2.5)}).value());
	EXPECT_EQ(custom::number(-1.0), floor(custom::meters{custom::number(-1.0)}).value());
	EXPECT_EQ(custom::number(-2.0), floor(custom::meters{custom::number(-1.5)}).value());
	EXPECT_EQ(custom::number(-2.0), floor(custom::meters{custom::number(-2.0)}).value());
	EXPECT_EQ(custom::number(-3.0), floor(custom::meters{custom::number(-2.5)}).value());
}

TEST(custom_numeric_type, ceil)
{
	EXPECT_EQ(custom::number(+1.0), ceil(custom::meters{custom::number(+1.0)}).value());
	EXPECT_EQ(custom::number(+2.0), ceil(custom::meters{custom::number(+1.4)}).value());
	EXPECT_EQ(custom::number(+2.0), ceil(custom::meters{custom::number(+1.5)}).value());
	EXPECT_EQ(custom::number(+2.0), ceil(custom::meters{custom::number(+1.6)}).value());
	EXPECT_EQ(custom::number(+2.0), ceil(custom::meters{custom::number(+2.0)}).value());
	EXPECT_EQ(custom::number(+3.0), ceil(custom::meters{custom::number(+2.5)}).value());
	EXPECT_EQ(custom::number(-1.0), ceil(custom::meters{custom::number(-1.0)}).value());
	EXPECT_EQ(custom::number(-1.0), ceil(custom::meters{custom::number(-1.5)}).value());
	EXPECT_EQ(custom::number(-2.0), ceil(custom::meters{custom::number(-2.0)}).value());
	EXPECT_EQ(custom::number(-2.0), ceil(custom::meters{custom::number(-2.5)}).value());
}

TEST(custom_numeric_type, round)
{
	EXPECT_EQ(custom::number(+1.0), round(custom::meters{custom::number(+1.0)}).value());
	EXPECT_EQ(custom::number(+1.0), round(custom::meters{custom::number(+1.4)}).value());
	EXPECT_EQ(custom::number(+2.0), round(custom::meters{custom::number(+1.5)}).value());
	EXPECT_EQ(custom::number(+2.0), round(custom::meters{custom::number(+1.6)}).value());
	EXPECT_EQ(custom::number(+2.0), round(custom::meters{custom::number(+2.0)}).value());
	EXPECT_EQ(custom::number(+3.0), round(custom::meters{custom::number(+2.5)}).value());
	EXPECT_EQ(custom::number(-1.0), round(custom::meters{custom::number(-1.0)}).value());
	EXPECT_EQ(custom::number(-2.0), round(custom::meters{custom::number(-1.5)}).value());
	EXPECT_EQ(custom::number(-2.0), round(custom::meters{custom::number(-2.0)}).value());
	EXPECT_EQ(custom::number(-3.0), round(custom::meters{custom::number(-2.5)}).value());
}

TEST(basic_unit, abs)
{
	EXPECT_EQ(custom::number(1.0), abs(custom::meters{custom::number(+1.0)}).value());
	EXPECT_EQ(custom::number(1.4), abs(custom::meters{custom::number(+1.4)}).value());
	EXPECT_EQ(custom::number(1.5), abs(custom::meters{custom::number(+1.5)}).value());
	EXPECT_EQ(custom::number(1.6), abs(custom::meters{custom::number(+1.6)}).value());
	EXPECT_EQ(custom::number(2.0), abs(custom::meters{custom::number(+2.0)}).value());
	EXPECT_EQ(custom::number(2.5), abs(custom::meters{custom::number(+2.5)}).value());
	EXPECT_EQ(custom::number(1.0), abs(custom::meters{custom::number(-1.0)}).value());
	EXPECT_EQ(custom::number(1.5), abs(custom::meters{custom::number(-1.5)}).value());
	EXPECT_EQ(custom::number(2.0), abs(custom::meters{custom::number(-2.0)}).value());
	EXPECT_EQ(custom::number(2.5), abs(custom::meters{custom::number(-2.5)}).value());
}
}
