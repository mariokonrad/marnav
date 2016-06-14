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
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	// spare: 38 - 39
	bits.get(channel_a, 40, 12);
	bits.get(channel_b, 52, 12);
	bits.get(txrx_mode, 64, 4);
	bits.get(power, 68, 1);
	bits.get(addressed, 139, 1);
	if (addressed) {
		bits.get(mmsi_1, 69, 30);
		bits.get(mmsi_2, 104, 30);
	} else {
		bits.get(ne_lon, 69, 18);
		bits.get(ne_lat, 87, 17);
		bits.get(sw_lon, 104, 18);
		bits.get(sw_lat, 122, 17);
	}
	bits.get(band_a, 140, 1);
	bits.get(band_b, 141, 1);
	bits.get(zone_size, 142, 3);
	// spare: 145 - 167
}

/// @todo possible refactoring for name_extension
raw message_22::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(mmsi, 8, 30);
	bits.set(channel_a, 40, 12);
	bits.set(channel_b, 52, 12);
	bits.set(txrx_mode, 64, 4);
	bits.set(power, 68, 1);
	if (addressed) {
		bits.set(mmsi_1, 69, 30);
		bits.set(mmsi_2, 104, 30);
	} else {
		bits.set(ne_lon, 69, 18);
		bits.set(ne_lat, 87, 17);
		bits.set(sw_lon, 104, 18);
		bits.set(sw_lat, 122, 17);
	}
	bits.set(addressed, 139, 1);
	bits.set(band_a, 140, 1);
	bits.set(band_b, 141, 1);
	bits.set(zone_size, 142, 3);

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
