#ifndef MARNAV_MATH_FLOATINGPONIT_ULPS_HPP
#define MARNAV_MATH_FLOATINGPONIT_ULPS_HPP

// implementation based on https://bitbashing.io/comparing-floats.html
// by matt <at> bitbashing.io
//
// this file is distributed under following license: CC BY-SA 4.0
// https://creativecommons.org/licenses/by-sa/4.0/

#include <limits>
#include <cstdint>
#include <cmath>
#include <cstring>

namespace marnav
{
namespace math
{
namespace detail
{
// clang-format off
template <class TF> struct corresponding_integer         {};
template <>         struct corresponding_integer<float>  { using type = int32_t; };
template <>         struct corresponding_integer<double> { using type = int64_t; };

template <class TF>
using corresponding_integer_t = typename corresponding_integer<TF>::type;

template <class TF> struct default_ulps         {};
template <>         struct default_ulps<float>  { static constexpr corresponding_integer_t<float>  value = 1e4; };
template <>         struct default_ulps<double> { static constexpr corresponding_integer_t<double> value = 1e6; };
// clang-format on

template <class TF, class TI = corresponding_integer_t<TF>>
TI ulps_distance(const TF a, const TF b)
{
	// save work if the floats are equal, also handles +0 == -0
	if (a == b)
		return 0;

	// max distance for NaN
	if (std::isnan(a) || std::isnan(b))
		return std::numeric_limits<TI>::max();

	// max distance for INF
	if (std::isinf(a) || std::isinf(b))
		return std::numeric_limits<TI>::max();

	TI ia;
	TI ib;
	::memcpy(&ia, &a, sizeof(TF));
	::memcpy(&ib, &b, sizeof(TF));

	// don't compare differently-signed floats.
	if ((ia < 0) != (ib < 0))
		return std::numeric_limits<TI>::max();

	// return the absolute value of the distance in ULPs.
	const TI distance = ia - ib;
	return (distance < 0) ? -distance : distance;
}
}

template <class TF, class TI = detail::corresponding_integer_t<TF>>
bool nearly_equal(TF a, TF b, TF fixed_epsilon = std::numeric_limits<TF>::epsilon(),
	TI ulps_epsilon = detail::default_ulps<TF>::value)
{
	const auto difference = std::abs(a - b);
	if (difference <= fixed_epsilon)
		return true;
	return detail::ulps_distance(a, b) <= ulps_epsilon;
}
}
}

#endif
