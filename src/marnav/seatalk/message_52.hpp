#ifndef MARNAV__SEATALK__MESSAGE_52__HPP
#define MARNAV__SEATALK__MESSAGE_52__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Speed over Ground
///
/// @code
/// 52 01 XX XX
///
/// Speed over Ground: XXXX/10 Knots
/// @endcode
///
/// Corresponding NMEA sentences: RMC, VTG
///
class message_52 : public message
{
public:
	constexpr static const message_id ID = message_id::speed_over_ground;
	constexpr static size_t SIZE = 4;

	message_52();
	message_52(const message_52 &) = default;
	message_52 & operator=(const message_52 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint16_t sog_;

public:
	double get_sog() const noexcept;

	void set_sog(double t) noexcept;
};
}
}

#endif
