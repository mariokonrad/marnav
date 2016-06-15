#include "message_22.hpp"

#include <algorithm>
#include <cmath>

#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_22::message_22()
	: message(ID)
{
}

std::unique_ptr<message> message_22::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_22::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_22>();
	message_22 & msg = static_cast<message_22 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_22::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, channel_a);
	get(bits, channel_b);
	get(bits, txrx_mode);
	get(bits, power);
	get(bits, addressed);
	get(bits, band_a);
	get(bits, band_b);
	get(bits, zone_size);

	if (addressed) {
		get(bits, mmsi_1);
		get(bits, mmsi_2);
	} else {
		get(bits, ne_lon);
		get(bits, ne_lat);
		get(bits, sw_lon);
		get(bits, sw_lat);
	}
}

/// @todo possible refactoring for name_extension
raw message_22::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, channel_a);
	set(bits, channel_b);
	set(bits, txrx_mode);
	set(bits, power);
	set(bits, addressed);
	set(bits, band_a);
	set(bits, band_b);
	set(bits, zone_size);

	if (addressed) {
		set(bits, mmsi_1);
		set(bits, mmsi_2);
	} else {
		set(bits, ne_lon);
		set(bits, ne_lat);
		set(bits, sw_lon);
		set(bits, sw_lat);
	}

	return bits;
}

geo::position message_22::get_position_ne() const noexcept
{
	return {geo::latitude{ne_lat / (60.0 * 10.0)}, geo::longitude{ne_lon / (60.0 * 10.0)}};
}

geo::position message_22::get_position_sw() const noexcept
{
	return {geo::latitude{sw_lat / (60.0 * 10.0)}, geo::longitude{sw_lon / (60.0 * 10.0)}};
}

void message_22::set_position_ne(const geo::position & t) noexcept
{
	ne_lat = std::floor(60.0 * 10.0 * t.lat());
	ne_lon = std::floor(60.0 * 10.0 * t.lon());
}

void message_22::set_position_sw(const geo::position & t) noexcept
{
	sw_lat = std::floor(60.0 * 10.0 * t.lat());
	sw_lon = std::floor(60.0 * 10.0 * t.lon());
}
}
}
