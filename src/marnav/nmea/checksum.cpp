#include "checksum.hpp"

namespace marnav
{
namespace nmea
{
checksum_error::checksum_error(uint8_t expected, uint8_t actual)
	: expected(expected)
	, actual(actual)
{
	snprintf(text, sizeof(text), "checksum error (actual:%02X, expected:%02X)", actual, expected);
}
}
}
