#ifndef MARNAV_SEATALK_MESSAGE_20_HPP
#define MARNAV_SEATALK_MESSAGE_20_HPP

#include <marnav/seatalk/message.hpp>

namespace marnav::seatalk
{

/// @brief Speed through water
///
/// @code
/// 20 01 XX XX
///
/// Speed through water: XXXX/10 Knots
/// @endcode
///
/// Corresponding NMEA sentence: VHW
///
class message_20 : public message
{
public:
	constexpr static const message_id ID = message_id::speed_through_water;
	constexpr static size_t SIZE = 4;

	message_20();
	message_20(const message_20 &) = default;
	message_20 & operator=(const message_20 &) = default;

	raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint16_t speed_{0}; // speed in 1/10th of knots

public:
	uint16_t get_speed() const noexcept { return speed_; }

	void set_speed(uint16_t t) noexcept { speed_ = t; }
};
}

#endif
