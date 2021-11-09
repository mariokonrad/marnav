#ifndef MARNAV_UNITS_BASIC_QUANTITY_CMP_HPP
#define MARNAV_UNITS_BASIC_QUANTITY_CMP_HPP

#include "basic_quantity.hpp"
#include <marnav/math/floatingpoint.hpp>
#include <marnav/math/floatingpoint_ulps.hpp>
#include <limits>
#include <type_traits>

namespace marnav
{
namespace units
{
template <class T, class VT,
	typename std::enable_if<!std::is_floating_point<VT>::value, int>::type = 0>
constexpr bool operator==(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return v1.value() == v2.value();
}

template <class T, class VT,
	typename std::enable_if<
		std::is_floating_point<VT>::value && !std::numeric_limits<VT>::is_iec559, int>::type
	= 0>
constexpr bool operator==(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return math::is_same(v1.value(), v2.value());
}

template <class T, class VT,
	typename std::enable_if<
		std::is_floating_point<VT>::value && std::numeric_limits<VT>::is_iec559, int>::type
	= 0>
constexpr bool operator==(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return math::nearly_equal(v1.value(), v2.value());
}

template <class T, class VT>
constexpr bool operator!=(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return !(v1 == v2);
}

template <class T, class VT>
constexpr bool operator<(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return v1.value() < v2.value();
}

template <class T, class VT>
constexpr bool operator<=(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return (v1 < v2) || (v1 == v2);
}

template <class T, class VT>
constexpr bool operator>(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return !(v1 <= v2);
}

template <class T, class VT>
constexpr bool operator>=(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return !(v1 < v2);
}
}
}

#endif
