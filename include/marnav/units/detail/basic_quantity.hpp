#ifndef MARNAV_UNITS_BASIC_QUANTITY_HPP
#define MARNAV_UNITS_BASIC_QUANTITY_HPP

#include "basic_unit.hpp"
#include <type_traits>

namespace marnav
{
namespace units
{
template <class Dimension, class ValueType>
class basic_quantity
{
public:
	using value_type = ValueType;
	using dimension = Dimension;

	constexpr basic_quantity() noexcept = default;

	basic_quantity(const basic_quantity &) = default;
	basic_quantity & operator=(const basic_quantity &) = default;

	basic_quantity(basic_quantity &&) noexcept = default;
	basic_quantity & operator=(basic_quantity &&) noexcept = default;

	// Construction from basic_unit, possible only if dimension and value type match.
	template <class Unit, class Ratio,
		typename
		= typename std::enable_if<std::is_same<dimension, typename Unit::dimension>::value
			&& std::is_same<value_type, typename Unit::value_type>::value>::type>
	constexpr basic_quantity(const basic_unit<Unit, Ratio> & u)
		: value_(detail::scale<Ratio>(Unit::to_base(u.value())))
	{
	}

	// getters
	constexpr const value_type & value() const noexcept { return value_; }

	template <class BasicUnit,
		typename
		= typename std::enable_if<std::is_same<dimension, typename BasicUnit::dimension>::value
			&& std::is_same<value_type, typename BasicUnit::value_type>::value>::type>
	constexpr BasicUnit get() const noexcept
	{
		return BasicUnit(detail::scale<ratio_inv<typename BasicUnit::ratio>>(
			BasicUnit::unit_type::from_base(value_)));
	}

public: // scaling
	basic_quantity & operator*=(value_type s) noexcept
	{
		value_ *= s;
		return *this;
	}

	basic_quantity & operator/=(value_type s) noexcept
	{
		value_ /= s;
		return *this;
	}

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> operator*(
		const basic_quantity<T, VT> & v, const VT & s) noexcept;

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> operator*(
		const VT & s, const basic_quantity<T, VT> & v) noexcept;

public: // unary minus
	constexpr basic_quantity operator-() const noexcept { return basic_quantity(-value_); }

public: // add/sub
	basic_quantity & operator+=(const basic_quantity & v) noexcept
	{
		value_ += v.value_;
		return *this;
	}

	basic_quantity & operator-=(const basic_quantity & v) noexcept
	{
		value_ -= v.value_;
		return *this;
	}

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> operator+(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> operator-(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

public: // mul/div
	template <class VT, class Dimension1, class Dimension2, class ResultDim>
	friend constexpr basic_quantity<ResultDim, VT> operator*(
		const basic_quantity<Dimension1, VT> & v1,
		const basic_quantity<Dimension2, VT> & v2) noexcept;

	template <class VT, class Dimension1, class Dimension2, class ResultDim>
	friend constexpr basic_quantity<ResultDim, VT> operator/(
		const basic_quantity<Dimension1, VT> & v1,
		const basic_quantity<Dimension2, VT> & v2) noexcept;

	template <class Unit1, class Ratio1, class Unit2, class Ratio2, class ResultDim,
		class ResultValueType, typename>
	friend constexpr basic_quantity<ResultDim, ResultValueType> operator*(
		const basic_unit<Unit1, Ratio1> & u1, const basic_unit<Unit2, Ratio2> & u2) noexcept;

	template <class Unit1, class Ratio1, class Unit2, class Ratio2, class ResultDim,
		class ResultValueType, typename>
	friend constexpr basic_quantity<ResultDim, ResultValueType> operator/(
		const basic_unit<Unit1, Ratio1> & u1, const basic_unit<Unit2, Ratio2> & u2) noexcept;

public: // functions
	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> floor(const basic_quantity<T, VT> & v) noexcept;

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> ceil(const basic_quantity<T, VT> & v) noexcept;

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> round(const basic_quantity<T, VT> & v) noexcept;

	template <class T, class VT>
	friend constexpr basic_quantity<T, VT> abs(const basic_quantity<T, VT> & v) noexcept;

public: // comparison
	template <class T, class VT, typename>
	friend constexpr bool operator==(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

	template <class T, class VT>
	friend constexpr bool operator!=(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

	template <class T, class VT>
	friend constexpr bool operator<(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

	template <class T, class VT>
	friend constexpr bool operator<=(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

	template <class T, class VT>
	friend constexpr bool operator>(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

	template <class T, class VT>
	friend constexpr bool operator>=(
		const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept;

private:
	value_type value_ = {};

	constexpr explicit basic_quantity(value_type value) noexcept
		: value_(value)
	{
	}
};
}
}

#endif
