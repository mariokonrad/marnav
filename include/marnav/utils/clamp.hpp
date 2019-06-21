#ifndef MARNAV__UTILS__CLAMP__HPP
#define MARNAV__UTILS__CLAMP__HPP

#include <algorithm>

namespace marnav
{
namespace utils
{
template <class T> constexpr T clamp(const T & value, const T & lo, const T & hi)
{
	return std::max(lo, std::min(hi, value));
}
}
}

#endif
