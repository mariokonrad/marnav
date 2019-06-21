#ifndef MARNAV__SEATALK__MESSAGE_58__HPP
#define MARNAV__SEATALK__MESSAGE_58__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/geo/position.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Lat/Lon
///
/// @code
/// 58 Z5 LA XX YY LO QQ RR
///
/// LA Degrees LAT
/// LO Degrees LON
/// minutes LAT = (XX*256+YY) / 1000
/// minutes LON = (QQ*256+RR) / 1000
/// Z&1: South (Z&1 = 0: North)
/// Z&2: East  (Z&2 = 0: West)
/// @endcode
///
/// Raw unfiltered position, for filtered data use commands 50&51
///
/// Corresponding NMEA sentences: RMC, GAA, GLL
///
class message_58 : public message
{
public:
	constexpr static const message_id ID = message_id::lat_lon;
	constexpr static size_t SIZE = 8;

	message_58();
	message_58(const message_58 &) = default;
	message_58 & operator=(const message_58 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	geo::position pos_;

public:
	const geo::position & get_pos() const noexcept { return pos_; }

	void set_pos(const geo::position & p) noexcept { pos_ = p; }
};
}
}

#endif
