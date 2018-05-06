#ifndef MARNAV__NMEA__CHECKSUM__HPP
#define MARNAV__NMEA__CHECKSUM__HPP

#include <string>
#include <stdexcept>
#include <algorithm>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// Exception for cases where the checksum is wrong.
///
/// This exception carries the actual as well as the expected
/// checksum and will provide this information in the explanation.
class checksum_error : public std::exception
{
public:
	MARNAV_EXPORT checksum_error() = delete;
	MARNAV_EXPORT explicit checksum_error(uint8_t exp, uint8_t act);
	MARNAV_EXPORT checksum_error(const checksum_error &) = default;
	MARNAV_EXPORT checksum_error(checksum_error &&) = default;

	MARNAV_EXPORT checksum_error & operator=(const checksum_error &) = default;
	MARNAV_EXPORT checksum_error & operator=(checksum_error &&) = default;

	MARNAV_EXPORT virtual const char * what() const noexcept override { return text_; }

	const uint8_t expected;
	const uint8_t actual;

private:
	char text_[64];
};

/// Computes and returns the checksum of the specified range.
///
/// @tparam Iterator Iterator type which dereferences to a \c char.
/// @param[in] a The starting point to compute the checksum.
/// @param[in] b The ending point (exclusive) to compute the checksum.
/// @return The computed checksum.
///
template <class Iterator> uint8_t checksum(Iterator a, Iterator b) noexcept
{
	uint8_t sum = 0x00;
	std::for_each(a, b, [&sum](char c) { sum ^= static_cast<uint8_t>(c); });
	return sum;
}

MARNAV_EXPORT std::string checksum_to_string(uint8_t sum);
}
}

#endif
