#ifndef MARNAV_UNITS_BASIC_UNIT_OPS_HPP
#define MARNAV_UNITS_BASIC_UNIT_OPS_HPP

#include "basic_unit.hpp"

namespace marnav
{
namespace units
{
template <class U, class R, class S>
constexpr basic_unit<U, R> operator*(const basic_unit<U, R> & v, const S & s) noexcept
{
	return basic_unit<U, R>(v) *= s;
}

template <class U, class R, class S>
constexpr basic_unit<U, R> operator*(const S & s, const basic_unit<U, R> & v) noexcept
{
	return basic_unit<U, R>(v) *= s;
}

template <class U, class R, class S>
constexpr basic_unit<U, R> operator/(const basic_unit<U, R> & v, const S & s) noexcept
{
	return basic_unit<U, R>(v) /= s;
}

// TODO: shouldn't this return basic_quantity<U1::dimension, U1::value_type>?
template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<
		std::is_same<typename U1::dimension, typename U2::dimension>::value
		&& std::is_same<typename U1::value_type, typename U2::value_type>::value>::type>
constexpr basic_unit<U1, R1> operator+(
	const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return basic_unit<U1, R1>(v1) += basic_unit<U1, R1>(v2);
}

// TODO: shouldn't this return basic_quantity<U1::dimension, U1::value_type>?
template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<
		std::is_same<typename U1::dimension, typename U2::dimension>::value
		&& std::is_same<typename U1::value_type, typename U2::value_type>::value>::type>
constexpr basic_unit<U1, R1> operator-(
	const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return basic_unit<U1, R1>(v1) -= basic_unit<U1, R1>(v2);
}
}
}

#endif
