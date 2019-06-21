#ifndef MARNAV__SEATALK__MESSAGE_05__HPP
#define MARNAV__SEATALK__MESSAGE_05__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Engine RPM and PITCH
///
/// @code
/// 05 03 0X YY ZZ PP
///
/// Engine RPM and PITCH:
///    X = 0: RPM & PITCH
///    X = 1: RPM & PITCH  starboard
///    X = 2: PRM & PITCH  port
///    YY*256+ZZ = RPM Value (signed value, example: YYZZ=0x0110=272 RPM, YYZZ=0xfef0= -272 RPM)
///    PP = % Pitch (signed value -128%...+127%, example 0x03=3%, 0xFD= -3%)
/// @endcode
///
class message_05 : public message
{
public:
	constexpr static const message_id ID = message_id::engine_rpm_and_pitch;
	constexpr static size_t SIZE = 6;

	enum class side_id { undefined, starboard, port };

	message_05();
	message_05(const message_05 &) = default;
	message_05 & operator=(const message_05 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	side_id side_;
	int32_t rpm_;
	int8_t percent_pitch_;

public:
	side_id get_side() const noexcept { return side_; }
	int16_t get_rpm() const noexcept { return rpm_; }
	int8_t get_percent_pitch() const noexcept { return percent_pitch_; }

	void set_side(side_id t) noexcept { side_ = t; }
	void set_rpm(int16_t t) noexcept { rpm_ = t; }
	void set_percent_pitch(int8_t t) noexcept { percent_pitch_ = t; }
};
}
}

#endif
