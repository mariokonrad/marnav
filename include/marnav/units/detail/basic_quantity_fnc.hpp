#ifndef MARNAV_UNITS_BASIC_QUANTITY_FNC_HPP
#define MARNAV_UNITS_BASIC_QUANTITY_FNC_HPP

#include "basic_quantity.hpp"
#include <cmath>

namespace marnav
{
namespace units
{
template <class T, class VT>
constexpr basic_quantity<T, VT> floor(const basic_quantity<T, VT> & v) noexcept
{
	using std::floor;
	return basic_quantity<T, VT>(floor(v.value()));
}

template <class T, class VT>
constexpr basic_quantity<T, VT> ceil(const basic_quantity<T, VT> & v) noexcept
{
	using std::ceil;
	return basic_quantity<T, VT>(ceil(v.value()));
}

template <class T, class VT>
constexpr basic_quantity<T, VT> round(const basic_quantity<T, VT> & v) noexcept
{
	using std::round;
	return basic_quantity<T, VT>(round(v.value()));
}

template <class T, class VT>
constexpr basic_quantity<T, VT> abs(const basic_quantity<T, VT> & v) noexcept
{
	using std::abs;
	return basic_quantity<T, VT>(abs(v.value()));
}
}
}

#endif
