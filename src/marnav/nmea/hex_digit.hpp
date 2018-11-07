#ifndef MARNAV__NMEA__HEX_DIGIT__HPP
#define MARNAV__NMEA__HEX_DIGIT__HPP

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace detail
{
inline constexpr char hex_digit(unsigned int t) noexcept
{
	return "0123456789ABCDEF"[t & 0xf];
}
}
/// @endcond
}
}

#endif
