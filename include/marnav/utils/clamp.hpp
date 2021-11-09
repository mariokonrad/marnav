#ifndef MARNAV_UTILS_CLAMP_HPP
#define MARNAV_UTILS_CLAMP_HPP

#include <algorithm>

namespace marnav
{
namespace utils
{
template <class T>
constexpr T clamp(const T & value, const T & lo, const T & hi)
{
	return std::max(lo, std::min(hi, value));
}
}
}

#endif
