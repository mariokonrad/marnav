#ifndef MARNAV__SEATALK__MESSAGE_89__HPP
#define MARNAV__SEATALK__MESSAGE_89__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Compass heading sent by ST40 compass instrument
///
/// @code
/// 89 U2 VW XY 2Z
///
/// Compass heading sent by ST40 compass instrument
/// (it is read as a compass heading by the ST1000(+) or ST2000(+) autopilot)
/// Compass heading in degrees:
///   The two lower bits of  U  *  90   +
///   the six lower bits of VW  *   2   +
///   the two higher bits of U  /   2   =
///
/// The meaning of XY and Z is unknown.
/// @endcode
///
class message_89 : public message
{
public:
	constexpr static const message_id ID = message_id::st40_compass_heading;
	constexpr static size_t SIZE = 5;

	message_89();
	message_89(const message_89 &) = default;
	message_89 & operator=(const message_89 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	double value_;

public:
	/// Returns the heading in degrees, resolution of `0.5` degrees.
	///
	/// This value will always be in the interval `[0.0 .. 359.5]`.
	double get_heading() const noexcept { return value_; }

	void set_heading(double t);
};
}
}

#endif
