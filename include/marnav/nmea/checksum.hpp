#ifndef MARNAV_NMEA_CHECKSUM_HPP
#define MARNAV_NMEA_CHECKSUM_HPP

#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <string>

namespace marnav::nmea
{
/// Exception for cases where the checksum is wrong.
///
/// This exception carries the actual as well as the expected
/// checksum and will provide this information in the explanation.
class checksum_error : public std::exception
{
public:
	checksum_error() = delete;
	explicit checksum_error(uint8_t exp, uint8_t act);
	checksum_error(const checksum_error &) = default;
	checksum_error(checksum_error &&) = default;

	checksum_error & operator=(const checksum_error &) = default;
	checksum_error & operator=(checksum_error &&) = default;

	const char * what() const noexcept override { return text_; }

	uint8_t expected() const noexcept { return expected_; }
	uint8_t actual() const noexcept { return actual_; }

private:
	uint8_t expected_ = 0u;
	uint8_t actual_ = 0u;
	char text_[64];
};

/// Computes and returns the checksum of the specified range.
///
/// @tparam Iterator Iterator type which dereferences to a \c char.
/// @param[in] a The starting point to compute the checksum.
/// @param[in] b The ending point (exclusive) to compute the checksum.
/// @return The computed checksum.
///
template <class Iterator>
uint8_t checksum(Iterator a, Iterator b) noexcept
{
	uint8_t sum = 0x00;
	std::for_each(a, b, [&sum](char c) { sum ^= static_cast<uint8_t>(c); });
	return sum;
}

std::string checksum_to_string(uint8_t sum);
}

#endif
