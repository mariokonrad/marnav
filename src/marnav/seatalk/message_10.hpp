#ifndef MARNAV__SEATALK__MESSAGE_10__HPP
#define MARNAV__SEATALK__MESSAGE_10__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Apparent Wind Angle
///
/// @code
/// 10  01  XX  YY
///
/// Apparent Wind Angle: XXYY/2 degrees right of bow Used for autopilots
/// Vane Mode (WindTrim)
/// @endcode
///
/// Corresponding NMEA sentence: MWV
///
class message_10 : public message
{
public:
	constexpr static const message_id ID = message_id::apparent_wind_angle;
	constexpr static size_t SIZE = 4;

	message_10();
	message_10(const message_10 &) = default;
	message_10 & operator=(const message_10 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint16_t angle_; // 1/10th of degrees right of bow

public:
	uint16_t get_angle() const noexcept { return angle_; }

	void set_angle(uint16_t t) noexcept { angle_ = t; }
};
}
}

#endif
