#ifndef MARNAV__SEATALK__MESSAGE_86__HPP
#define MARNAV__SEATALK__MESSAGE_86__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/seatalk/key.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Keystroke
///
/// @code
/// 86 X1 YY yy
///
///   X=1: Sent by Z101 remote control to increment/decrement course of autopilot
///      11 05 FA     -1
///      11 06 F9    -10
///      11 07 F8     +1
///      11 08 F7    +10
///      11 20 DF     +1 &  -1
///      11 21 DE     -1 & -10
///      11 22 DD     +1 & +10
///      11 28 D7    +10 & -10
///      11 45 BA     -1        pressed longer than 1 second
///      11 46 B9    -10        pressed longer than 1 second
///      11 47 B8     +1        pressed longer than 1 second
///      11 48 B7    +10        pressed longer than 1 second
///      11 60 DF     +1 &  -1  pressed longer than 1 second
///      11 61 9E     -1 & -10  pressed longer than 1 second
///      11 62 9D     +1 & +10  pressed longer than 1 second
///      11 64 9B    +10 & -10  pressed longer than 1 second (why not 11 68 97 ?)
///
///   Sent by autopilot (X=0: ST 1000+,  X=2: ST4000+ or ST600R)
///      X1 01 FE    Auto
///      X1 02 FD    Standby
///      X1 03 FC    Track
///      X1 04 FB    disp (in display mode or page in auto chapter = advance)
///      X1 05 FA     -1 (in auto mode)
///      X1 06 F9    -10 (in auto mode)
///      X1 07 F8     +1 (in auto mode)
///      X1 08 F7    +10 (in auto mode)
///      X1 09 F6     -1 (in resp or rudder gain mode)
///      X1 0A F5     +1 (in resp or rudder gain mode)
///      X1 21 DE     -1 & -10 (port tack, doesn´t work on ST600R?)
///      X1 22 DD     +1 & +10 (stb tack)
///      X1 23 DC    Standby & Auto (wind mode)
///      X1 28 D7    +10 & -10 (in auto mode)
///      X1 2E D1     +1 & -1 (Response Display)
///      X1 41 BE    Auto pressed longer
///      X1 42 BD    Standby pressed longer
///      X1 43 BC    Track pressed longer
///      X1 44 BB    Disp pressed longer
///      X1 45 BA     -1 pressed longer (in auto mode)
///      X1 46 B9    -10 pressed longer (in auto mode)
///      X1 47 B8     +1 pressed longer (in auto mode)
///      X1 48 B7    +10 pressed longer (in auto mode)
///      X1 63 9C    Standby & Auto pressed longer (previous wind angle)
///      X1 68 97    +10 & -10 pressed longer (in auto mode)
///      X1 6E 91     +1 & -1 pressed longer (Rudder Gain Display)
///      X1 80 7F     -1 pressed (repeated 1x per second)
///      X1 81 7E     +1 pressed (repeated 1x per second)
///      X1 82 7D    -10 pressed (repeated 1x per second)
///      X1 83 7C    +10 pressed (repeated 1x per second)
///      X1 84 7B     +1, -1, +10 or -10 released
/// @endcode
///
class message_86 : public message
{
public:
	constexpr static const message_id ID = message_id::keystroke;
	constexpr static size_t SIZE = 4;

	enum class origin : uint8_t { z101 = 1, st1000 = 0, st4000_or_st600r = 2 };

	message_86();
	message_86(const message_86 &) = default;
	message_86 & operator=(const message_86 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	origin org_;
	key k_;

public:
	origin get_org() const { return org_; }
	key get_key() const { return k_; }

	void set_org(origin t) { org_ = t; }
	void set_key(key t) { k_ = t; }
};
}
}

#endif
