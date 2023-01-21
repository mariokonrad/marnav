#include <marnav/ais/message_22.hpp>
#include <marnav/ais/angle.hpp>
#include <algorithm>
#include <cmath>

namespace marnav::ais
{
constexpr message_id message_22::ID;
constexpr std::size_t message_22::SIZE_BITS;

message_22::message_22()
	: message(ID)
{
}

message_22::message_22(const raw & bits)
	: message(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_22"};
	read_data(bits);
}

void message_22::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, channel_a_);
	get(bits, channel_b_);
	get(bits, txrx_mode_);
	get(bits, power_);
	get(bits, addressed_);
	get(bits, band_a_);
	get(bits, band_b_);
	get(bits, zone_size_);

	if (addressed_) {
		get(bits, mmsi_1_);
		get(bits, mmsi_2_);
	} else {
		get(bits, ne_lon_);
		get(bits, ne_lat_);
		get(bits, sw_lon_);
		get(bits, sw_lat_);
	}
}

raw message_22::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, channel_a_);
	set(bits, channel_b_);
	set(bits, txrx_mode_);
	set(bits, power_);
	set(bits, addressed_);
	set(bits, band_a_);
	set(bits, band_b_);
	set(bits, zone_size_);

	if (addressed_) {
		set(bits, mmsi_1_);
		set(bits, mmsi_2_);
	} else {
		set(bits, ne_lon_);
		set(bits, ne_lat_);
		set(bits, sw_lon_);
		set(bits, sw_lat_);
	}

	return bits;
}

std::optional<geo::position> message_22::get_position_ne() const
{
	if ((ne_lat_ == latitude_not_available_short) || (ne_lon_ == longitude_not_available_short))
		return std::make_optional<geo::position>();

	return std::make_optional<geo::position>(
		to_geo_latitude(ne_lat_, ne_lat_.count, angle_scale::I1),
		to_geo_longitude(ne_lon_, ne_lon_.count, angle_scale::I1));
}

std::optional<geo::position> message_22::get_position_sw() const
{
	if ((sw_lat_ == latitude_not_available_short) || (sw_lon_ == longitude_not_available_short))
		return std::make_optional<geo::position>();

	return std::make_optional<geo::position>(
		to_geo_latitude(sw_lat_, sw_lat_.count, angle_scale::I1),
		to_geo_longitude(sw_lon_, sw_lon_.count, angle_scale::I1));
}

void message_22::set_position_ne(const geo::position & t) noexcept
{
	ne_lat_ = to_latitude_minutes(t.lat(), ne_lat_.count, angle_scale::I1);
	ne_lon_ = to_longitude_minutes(t.lon(), ne_lon_.count, angle_scale::I1);
}

void message_22::set_position_sw(const geo::position & t) noexcept
{
	sw_lat_ = to_latitude_minutes(t.lat(), sw_lat_.count, angle_scale::I1);
	sw_lon_ = to_longitude_minutes(t.lon(), sw_lon_.count, angle_scale::I1);
}
}
