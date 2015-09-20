#include "message_23.hpp"

#include <algorithm>

#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_23::message_23()
	: message(ID)
	, repeat_indicator(0)
	, mmsi(0)
	, ne_lon(0)
	, ne_lat(0)
	, sw_lon(0)
	, sw_lat(0)
	, station_type(0)
	, shiptype(ship_type::not_available)
	, txrx_mode(0)
	, interval(report_interval::autonomous_mode)
	, quiet_time(0)
{
}

std::unique_ptr<message> message_23::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_23::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_23>();
	message_23 & msg = static_cast<message_23 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_23::read_data(const raw & bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	// spare: 38 - 39
	bits.get(ne_lon, 40, 18);
	bits.get(ne_lat, 58, 17);
	bits.get(sw_lon, 75, 18);
	bits.get(sw_lat, 93, 17);
	bits.get(station_type, 110, 4);
	bits.get(shiptype, 114, 8);
	// spare: 122 - 143
	bits.get(txrx_mode, 144, 2);
	bits.get(interval, 146, 4);
	bits.get(quiet_time, 150, 4);
	// spare: 154 - 159
}

/// @todo possible refactoring for name_extension
raw message_23::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(mmsi, 8, 30);
	// spare: 38 - 39
	bits.set(ne_lon, 40, 18);
	bits.set(ne_lat, 58, 17);
	bits.set(sw_lon, 75, 18);
	bits.set(sw_lat, 93, 17);
	bits.set(station_type, 110, 4);
	bits.set(shiptype, 114, 8);
	bits.set(txrx_mode, 144, 2);
	bits.set(interval, 146, 4);
	bits.set(quiet_time, 150, 4);

	return bits;
}

geo::position message_23::get_position_ne() const noexcept
{
	return {geo::latitude{ne_lat / (60.0 * 10.0)}, geo::longitude{ne_lon / (60.0 * 10.0)}};
}

geo::position message_23::get_position_sw() const noexcept
{
	return {geo::latitude{sw_lat / (60.0 * 10.0)}, geo::longitude{sw_lon / (60.0 * 10.0)}};
}

void message_23::set_position_ne(const geo::position & t) noexcept
{
	ne_lat = std::floor(60.0 * 10.0 * t.lat());
	ne_lon = std::floor(60.0 * 10.0 * t.lon());
}

void message_23::set_position_sw(const geo::position & t) noexcept
{
	sw_lat = std::floor(60.0 * 10.0 * t.lat());
	sw_lon = std::floor(60.0 * 10.0 * t.lon());
}
}
}
