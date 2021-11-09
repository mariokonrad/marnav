#ifndef MARNAV_MATH_FLOATINGPOINT_HPP
#define MARNAV_MATH_FLOATINGPOINT_HPP

#include <limits>
#include <stdexcept>
#include <type_traits>
#include <cmath>

namespace marnav
{
namespace math
{
/// Returns true if the specified value is epsilon arround zero.
///
/// @tparam T A floating point type.
/// @param[in] t The value to check.
/// @param[in] epsilon The epsilon to test the proximity of zero.
/// @retval true Absolute value of t is smaller than epsilon
/// @retval false Absolute value of t is larger than epsilon
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
inline bool is_zero(T t, T epsilon = std::numeric_limits<T>::epsilon()) noexcept
{
	return std::abs(t) <= epsilon;
}

/// Returns true if the specified values are the same, regarding epsilon.
///
/// @tparam T A floating point type.
/// @param[in] a The first value to check.
/// @param[in] b The second value to check.
/// @param[in] epsilon The epsilon to test the proximity of the values.
/// @retval true Both values are the same or at most epsilon() away.
/// @retval false Both values are sufficiently different (larger than epsilon).
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
inline bool is_same(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) noexcept
{
	return std::abs(a - b) <= epsilon;
}

/// Returns the converted integral value from the specified floating point value.
/// This function checks for convertability and throws an exception
/// if no non-narrowing conversion is possible.
///
/// @tparam IntType Integral type to convert to.
/// @tparam FloatType Floating point type to convert from.
/// @param[in] value Floating point value to convert.
/// @return Value converted to the configured integral type.
template <typename IntType, typename FloatType,
	typename = typename std::enable_if<std::is_integral<IntType>::value
		&& std::is_floating_point<FloatType>::value>::type>
inline IntType float_cast(FloatType value)
{
	if ((std::numeric_limits<IntType>::digits < std::numeric_limits<FloatType>::digits)
		&& (value > static_cast<FloatType>(std::numeric_limits<IntType>::max())
			|| value < static_cast<FloatType>(std::numeric_limits<IntType>::min())))
		throw std::range_error{"invalid conversion from floating point to integral type"};

	return static_cast<IntType>(value);
}
}
}

#endif
