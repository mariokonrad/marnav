#ifndef MARNAV_UNITS_BASIC_UNIT_HPP
#define MARNAV_UNITS_BASIC_UNIT_HPP

#include <ratio>
#include <type_traits>

// TODO: units for angular velocity??
// TODO: units for torque??
// TODO: units for (plane) angle??
// TODO: units for concentration??
// TODO: units for density??

namespace marnav
{
namespace units
{
template <class R>
struct ratio_inv {
	static constexpr const auto num = R::den;
	static constexpr const auto den = R::num;
};

namespace detail
{
template <class Ratio, class ValueType>
constexpr ValueType scale(const ValueType & value) noexcept
{
	return value * ValueType(Ratio::num) / ValueType(Ratio::den);
}
}

template <class Unit, class Ratio = std::ratio<1>>
class basic_unit
{
public:
	using value_type = typename Unit::value_type;
	using dimension = typename Unit::dimension;
	using unit_type = Unit;
	using ratio = Ratio;

	constexpr explicit basic_unit(value_type value) noexcept
		: value_(value)
	{
	}

	constexpr basic_unit() noexcept = default;

	basic_unit(const basic_unit &) = default;
	basic_unit & operator=(const basic_unit &) = default;

	basic_unit(basic_unit &&) noexcept = default;
	basic_unit & operator=(basic_unit &&) noexcept = default;

	// Conversion of one basic unit into another, as long as they
	// are compatible, i.e. have the same dimension.
	template <class U, class R,
		typename
		= typename std::enable_if<std::is_same<dimension, typename U::dimension>::value>::type>
	constexpr explicit basic_unit(const basic_unit<U, R> & other) noexcept
		: value_(detail::scale<ratio_inv<ratio>>(
			unit_type::from_base(detail::scale<R>(U::to_base(other.value())))))
	{
	}

	constexpr const value_type & value() const noexcept { return value_; }

public: // scaling
	basic_unit & operator*=(value_type s) noexcept
	{
		value_ *= s;
		return *this;
	}

	basic_unit & operator/=(value_type s) noexcept
	{
		value_ /= s;
		return *this;
	}

	template <class VT,
		typename = typename std::enable_if<!std::is_same<VT, value_type>::value
			&& std::is_convertible<VT, value_type>::value>::type>
	basic_unit & operator*=(const VT & s) noexcept
	{
		value_ *= s;
		return *this;
	}

	template <class VT,
		typename = typename std::enable_if<!std::is_same<VT, value_type>::value
			&& std::is_convertible<VT, value_type>::value>::type>
	basic_unit & operator/=(const VT & s) noexcept
	{
		value_ /= s;
		return *this;
	}

public: // unary minus
	constexpr basic_unit operator-() const noexcept { return basic_unit(-value_); }

public: // add/sub
	basic_unit & operator+=(const basic_unit & v) noexcept
	{
		value_ += v.value();
		return *this;
	}

	basic_unit & operator-=(const basic_unit & v) noexcept
	{
		value_ -= v.value();
		return *this;
	}

	template <class U, class R,
		typename = typename std::enable_if<std::is_same<dimension, typename U::dimension>::value
			&& std::is_same<value_type, typename U::value_type>::value>::type>
	basic_unit & operator+=(const basic_unit<U, R> & v) noexcept
	{
		return *this += basic_unit(v);
	}

	template <class U, class R,
		typename = typename std::enable_if<std::is_same<dimension, typename U::dimension>::value
			&& std::is_same<value_type, typename U::value_type>::value>::type>
	basic_unit & operator-=(const basic_unit<U, R> & v) noexcept
	{
		return *this -= basic_unit(v);
	}

private:
	value_type value_ = {};
};
}
}

#endif
