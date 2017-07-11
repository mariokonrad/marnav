#ifndef MARNAV__SEATALK__MESSAGE_11__HPP
#define MARNAV__SEATALK__MESSAGE_11__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Apparent Wind Speed
///
/// @code
/// 11  01  XX  0Y
///
/// Apparent Wind Speed: (XX & 0x7F) + Y/10 Knots
/// Units flag: XX&0x80=0    => Display value in Knots
///             XX&0x80=0x80 => Display value in Meter/Second
/// @endcode
///
/// Corresponding NMEA sentence: MWV
///
class message_11 : public message
{
public:
	constexpr static const message_id ID = message_id::apparent_wind_speed;
	constexpr static size_t SIZE = 4;

	message_11();
	message_11(const message_11 &) = default;
	message_11 & operator=(const message_11 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint8_t unit_; // unit of value
	uint16_t speed_; // wind speed in 1/10th of unit

public:
	uint8_t get_unit() const noexcept { return unit_; }
	uint16_t get_speed() const noexcept { return speed_; }

	void set_unit(uint8_t t) noexcept { unit_ = t; }
	void set_speed(uint16_t t) noexcept { speed_ = t; }
};
}
}

#endif
