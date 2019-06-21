#ifndef MARNAV__SEATALK__MESSAGE_50__HPP
#define MARNAV__SEATALK__MESSAGE_50__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Position Latitude
///
/// @code
/// 50  Z2  XX  YY  YY
///
/// LAT position:
///   XX degrees, (YYYY & 0x7FFF)/100 minutes
///   MSB of Y = YYYY & 0x8000 = South if set, North if cleared
///   Z = 0xA or 0x0 (reported for Raystar 120 GPS),
///                  meaning unknown Stable filtered position, for raw data use command 58
/// @endcode
///
/// Corresponding NMEA sentences: RMC, GAA, GLL
///
class message_50 : public message
{
public:
	constexpr static const message_id ID = message_id::position_latitude;
	constexpr static size_t SIZE = 5;

	message_50();
	message_50(const message_50 &) = default;
	message_50 & operator=(const message_50 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	geo::latitude lat_;

public:
	const geo::latitude & get_lat() const noexcept { return lat_; }

	void set_lat(const geo::latitude & t) noexcept { lat_ = t; }
};
}
}

#endif
