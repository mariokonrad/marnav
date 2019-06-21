#ifndef MARNAV__SEATALK__MESSAGE_59__HPP
#define MARNAV__SEATALK__MESSAGE_59__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Countdown Timer
///
/// @code
/// 59 22 SS MM XH
///
/// MM = Minutes (00..3B) (00 .. 63 min), MSB:0 Count up start flag
/// SS = Seconds (00..3B) (00 .. 59 sec)
/// H  = Houres  (0..9)   (00 .. 09 houres)
/// X  = Counter Mode:
///      0 = Count up and start if MSB of MM set
///      4 = Count down
///      8 = Count down and start
/// @endcode
///
/// Example: `59 22 3B 3B 49` -> Set Countdown Timer to `9.59:59`
///
/// `59 22 0A 00 80` : Sent by ST60 in countdown mode when counted down to 10 Seconds.
///
class message_59 : public message
{
public:
	constexpr static const message_id ID = message_id::countdown_timer;
	constexpr static size_t SIZE = 5;

	enum class mode : uint8_t { up_and_start = 0x00, down = 0x04, down_and_start = 0x08 };

	message_59();
	message_59(const message_59 &) = default;
	message_59 & operator=(const message_59 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint8_t hours_;
	uint8_t minutes_;
	uint8_t seconds_;
	mode count_mode_;

public:
	uint8_t get_hours() const { return hours_; }
	uint8_t get_minutes() const { return minutes_; }
	uint8_t get_seconds() const { return seconds_; }
	mode get_mode() const { return count_mode_; }

	void set_timer(uint8_t hours, uint8_t minutes, uint8_t seconds, mode m);
};
}
}

#endif
