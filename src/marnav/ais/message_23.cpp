#include "message_23.hpp"

#include <algorithm>
#include <cmath>

#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_23::message_23()
	: message(ID)
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

/// @todo possible refactoring for name_extension
raw message_23::get_data() const
{
	raw bits{SIZE_BITS};

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
