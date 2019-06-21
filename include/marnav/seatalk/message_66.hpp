#ifndef MARNAV__SEATALK__MESSAGE_66__HPP
#define MARNAV__SEATALK__MESSAGE_66__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Wind Alarm
///
/// @code
/// 66 00 XX
///
/// Wind alarm as indicated by flags in XY:
///     XX & 0x80 = 0x80: Apparent Wind angle low
///     XX & 0x40 = 0x40: Apparent Wind angle high
///     XX & 0x20 = 0x20: Apparent Wind speed low
///     XX & 0x10 = 0x10: Apparent Wind speed high
///     XX & 0x08 = 0x08: True Wind angle low
///     XX & 0x04 = 0x04: True Wind angle high
///     XX & 0x02 = 0x02: True Wind speed low
///     XX & 0x01 = 0x01: True Wind speed high (causes Wind-High-Alarm on ST40 Wind Instrument)
///     XX        = 0x00: End of wind alarm (only sent once)
/// @endcode
///
class message_66 : public message
{
public:
	constexpr static const message_id ID = message_id::wind_alarm;
	constexpr static size_t SIZE = 3;

	enum alarm : uint8_t {
		no_alarm = 0x00,
		apparent_angle_lo = 0x80,
		apparent_angle_hi = 0x40,
		apparent_speed_lo = 0x20,
		apparent_speed_hi = 0x10,
		true_angle_lo = 0x08,
		true_angle_hi = 0x04,
		true_speed_lo = 0x02,
		true_speed_hi = 0x01,
	};

	message_66();
	message_66(const message_66 &) = default;
	message_66 & operator=(const message_66 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	alarm value_;

public:
	alarm get_alarm() const noexcept { return value_; }

	void set_alarm(alarm t) { value_ = t; }
};

message_66::alarm operator|(message_66::alarm a, message_66::alarm b) noexcept;
message_66::alarm operator&(message_66::alarm a, message_66::alarm b) noexcept;
}
}

#endif
