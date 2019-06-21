#ifndef MARNAV__SEATALK__MESSAGE_51__HPP
#define MARNAV__SEATALK__MESSAGE_51__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Position Longitude
///
/// @code
/// 51  Z2  XX  YY  YY
///
/// LON position:
///   XX degrees, (YYYY & 0x7FFF)/100 minutes
///   MSB of Y = YYYY & 0x8000 = East if set, West if cleared
///   Z = 0xA or 0x0 (reported for Raystar 120 GPS),
///                  meaning unknown Stable filtered position, for raw data use command 58
/// @endcode
///
/// Corresponding NMEA sentences: RMC, GAA, GLL
///
class message_51 : public message
{
public:
	constexpr static const message_id ID = message_id::position_longitude;
	constexpr static size_t SIZE = 5;

	message_51();
	message_51(const message_51 &) = default;
	message_51 & operator=(const message_51 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	geo::longitude lon_;

public:
	const geo::longitude & get_lon() const noexcept { return lon_; }

	void set_lon(const geo::longitude & t) noexcept { lon_ = t; }
};
}
}

#endif
