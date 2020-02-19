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
}
}

#endif
