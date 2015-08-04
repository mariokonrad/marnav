#ifndef __MATH__FLOATINGPOINT__HPP__
#define __MATH__FLOATINGPOINT__HPP__

#include <cmath>
#include <limits>

namespace marnav
{
namespace math
{
/// Returns true if the specified value is epsilon arround zero.
///
/// @tparam T A floating point type.
/// @param[in] t The value to check.
/// @retval true Absolute value of t is smaller than epsilon
/// @retval false Absolute value of t is larger than epsilon
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
inline bool is_zero(T t) noexcept
{
	return std::abs(t) <= std::numeric_limits<T>::epsilon();
}

/// Returns true if the specified values are the same, regarding epsilon.
///
/// @tparam T A floating point type.
/// @param[in] a The first value to check.
/// @param[in] b The second value to check.
/// @retval true Both values are the same or at most epsilon() away.
/// @retval false Both values are sufficiently different (larger than epsilon).
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
inline bool is_same(T a, T b) noexcept
{
	return std::abs(std::abs(a) - std::abs(b)) <= std::numeric_limits<T>::epsilon();
}
}
}

#endif
