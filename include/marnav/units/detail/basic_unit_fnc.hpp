#ifndef MARNAV_UNITS_BASIC_UNIT_FNC_HPP
#define MARNAV_UNITS_BASIC_UNIT_FNC_HPP

#include "basic_unit.hpp"
#include <cmath>

namespace marnav
{
namespace units
{
template <class U, class R>
constexpr basic_unit<U, R> floor(const basic_unit<U, R> & v) noexcept
{
	using std::floor;
	return basic_unit<U, R>(floor(v.value()));
}

template <class U, class R>
constexpr basic_unit<U, R> ceil(const basic_unit<U, R> & v) noexcept
{
	using std::ceil;
	return basic_unit<U, R>(ceil(v.value()));
}

template <class U, class R>
constexpr basic_unit<U, R> round(const basic_unit<U, R> & v) noexcept
{
	using std::round;
	return basic_unit<U, R>(round(v.value()));
}

template <class U, class R>
constexpr basic_unit<U, R> abs(const basic_unit<U, R> & v) noexcept
{
	using std::abs;
	return basic_unit<U, R>(abs(v.value()));
}
}
}

#endif
