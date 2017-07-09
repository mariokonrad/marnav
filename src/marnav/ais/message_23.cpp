#include "message_23.hpp"
#include <algorithm>
#include <cmath>
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
message_23::message_23()
	: message(ID)
{
}

message_23::message_23(const raw & bits)
	: message(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_23"};
	read_data(bits);
}

void message_23::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, ne_lon);
	get(bits, ne_lat);
	get(bits, sw_lon);
	get(bits, sw_lat);
	get(bits, station_type);
	get(bits, shiptype);
	get(bits, txrx_mode);
	get(bits, interval);
	get(bits, quiet_time);
}

raw message_23::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, ne_lon);
	set(bits, ne_lat);
	set(bits, sw_lon);
	set(bits, sw_lat);
	set(bits, station_type);
	set(bits, shiptype);
	set(bits, txrx_mode);
	set(bits, interval);
	set(bits, quiet_time);

	return bits;
}

utils::optional<geo::position> message_23::get_position_ne() const
{
	if ((ne_lat == latitude_not_available_short) || (ne_lon == longitude_not_available_short))
		return utils::make_optional<geo::position>();

	return utils::make_optional<geo::position>(
		to_geo_latitude(ne_lat, ne_lat.count, angle_scale::I1),
		to_geo_longitude(ne_lon, ne_lon.count, angle_scale::I1));
}

utils::optional<geo::position> message_23::get_position_sw() const
{
	if ((sw_lat == latitude_not_available_short) || (sw_lon == longitude_not_available_short))
		return utils::make_optional<geo::position>();

	return utils::make_optional<geo::position>(
		to_geo_latitude(sw_lat, sw_lat.count, angle_scale::I1),
		to_geo_longitude(sw_lon, sw_lon.count, angle_scale::I1));
}

void message_23::set_position_ne(const geo::position & t) noexcept
{
	ne_lat = to_latitude_minutes(t.lat(), ne_lat.count, angle_scale::I1);
	ne_lon = to_longitude_minutes(t.lon(), ne_lon.count, angle_scale::I1);
}

void message_23::set_position_sw(const geo::position & t) noexcept
{
	sw_lat = to_latitude_minutes(t.lat(), sw_lat.count, angle_scale::I1);
	sw_lon = to_longitude_minutes(t.lon(), sw_lon.count, angle_scale::I1);
}
}
}
