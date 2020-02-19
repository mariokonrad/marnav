#ifndef MARNAV_UNITS_BASIC_UNIT_CMP_HPP
#define MARNAV_UNITS_BASIC_UNIT_CMP_HPP

#include "basic_unit.hpp"
#include <marnav/math/floatingpoint.hpp>
#include <marnav/math/floatingpoint_ulps.hpp>
#include <limits>
#include <type_traits>

namespace marnav
{
namespace units
{
// basic_unit operator==
//
// Implementations for
// - non-floating point
// - floating point IEEE754
// - floating point non-IEEE754

template <class U, class R,
	typename std::enable_if<!std::is_floating_point<typename U::value_type>::value, int>::type
	= 0>
constexpr bool operator==(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return v1.value() == v2.value();
}

template <class U, class R,
	typename std::enable_if<std::is_floating_point<typename U::value_type>::value
			&& !std::numeric_limits<typename U::value_type>::is_iec559,
		int>::type
	= 0>
constexpr bool operator==(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return math::is_same(v1.value(), v2.value());
}

template <class U, class R,
	typename std::enable_if<std::is_floating_point<typename U::value_type>::value
			&& std::numeric_limits<typename U::value_type>::is_iec559,
		int>::type
	= 0>
constexpr bool operator==(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return math::nearly_equal(v1.value(), v2.value());
}

template <class U, class R>
constexpr bool operator!=(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return !(v1 == v2);
}

template <class U, class R>
constexpr bool operator<(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return v1.value() < v2.value();
}

template <class U, class R>
constexpr bool operator<=(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return (v1 < v2) || (v1 == v2);
}

template <class U, class R>
constexpr bool operator>(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return !(v1 <= v2);
}

template <class U, class R>
constexpr bool operator>=(const basic_unit<U, R> & v1, const basic_unit<U, R> & v2) noexcept
{
	return !(v1 < v2);
}

template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<!std::is_same<U1, U2>::value>::type>
constexpr bool operator==(const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return v1 == basic_unit<U1, R1>(v2);
}

template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<!std::is_same<U1, U2>::value>::type>
constexpr bool operator!=(const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return !(v1 == v2);
}

template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<!std::is_same<U1, U2>::value>::type>
constexpr bool operator<(const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return v1 < basic_unit<U1, R1>(v2);
}

template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<!std::is_same<U1, U2>::value>::type>
constexpr bool operator<=(const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return (v1 < v2) || (v1 == v2);
}

template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<!std::is_same<U1, U2>::value>::type>
constexpr bool operator>(const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return !(v1 <= v2);
}

template <class U1, class R1, class U2, class R2,
	typename = typename std::enable_if<!std::is_same<U1, U2>::value>::type>
constexpr bool operator>=(const basic_unit<U1, R1> & v1, const basic_unit<U2, R2> & v2) noexcept
{
	return !(v1 < v2);
}
}
}

#endif
