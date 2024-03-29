#ifndef MARNAV_SEATALK_MESSAGE_27_HPP
#define MARNAV_SEATALK_MESSAGE_27_HPP

#include <marnav/seatalk/message.hpp>

namespace marnav::seatalk
{

/// @brief Water temperature
///
/// @code
/// 27 01 XX XX
///
/// Water temperature: (XXXX-100)/10 deg Celsius
/// @endcode
///
/// Corresponding NMEA sentence: MTW
///
class message_27 : public message
{
public:
	constexpr static const message_id ID = message_id::water_temperature_2;
	constexpr static size_t SIZE = 4;

	message_27();
	message_27(const message_27 &) = default;
	message_27 & operator=(const message_27 &) = default;

	raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	int32_t temperature_{0}; // temperature in 1/10th degrees celsius

public:
	int32_t get_temperature() const noexcept { return temperature_; }

	void set_temperature(int32_t t) noexcept { temperature_ = t; }
};
}

#endif
