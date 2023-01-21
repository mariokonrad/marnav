#include <marnav/nmea/checksum.hpp>
#include "hex_digit.hpp"

namespace marnav::nmea
{
checksum_error::checksum_error(uint8_t exp, uint8_t act)
	: expected_(exp)
	, actual_(act)
{
	snprintf(text_, sizeof(text_), "checksum error (actual:%02X, expected:%02X)", actual_,
		expected_);
}

/// Returns the specified checksum as string.
///
/// @param[in] sum The checksum to render as string.
/// @return The checksum as string. This string is always two characters.
///
std::string checksum_to_string(uint8_t sum)
{
	char buf[3]{detail::hex_digit(sum >> 4), detail::hex_digit(sum), '\0'};
	return buf;
}
}
