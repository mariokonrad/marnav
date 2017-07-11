#ifndef MARNAV__SEATALK__MESSAGE_53__HPP
#define MARNAV__SEATALK__MESSAGE_53__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Magnetic Course
///
/// @code
/// 53 U0 VW
///
/// Magnetic Course in degrees:
///     The two lower  bits of  U * 90 +
///     the six lower  bits of VW *  2 +
///     the two higher bits of  U /  2 =
///     (U & 0x3) * 90 + (VW & 0x3F) * 2 + (U & 0xC) / 8
/// @endcode
///
/// The Magnetic Course may be offset by the Compass Variation (see datagram 99)
/// to get the Course Over Ground (COG).
///
/// Corresponding NMEA sentences: RMC, VTG
///
class message_53 : public message
{
public:
	constexpr static const message_id ID = message_id::magnetic_course;
	constexpr static size_t SIZE = 3;

	message_53();
	message_53(const message_53 &) = default;
	message_53 & operator=(const message_53 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	double cog_;

public:
	/// Returns the COG in degrees.
	double get_cog() const noexcept { return cog_; }

	void set_cog(double t) noexcept;
};
}
}

#endif
