#include <marnav/ais/message_17.hpp>
#include <marnav/ais/angle.hpp>
#include <stdexcept>
#include <cmath>

namespace marnav::ais
{
constexpr message_id message_17::ID;
constexpr std::size_t message_17::SIZE_BITS_MIN;
constexpr std::size_t message_17::SIZE_BITS_MAX;

message_17::message_17()
	: message_17(ID)
{
}

message_17::message_17(message_id id)
	: message(id)
{
}

message_17::message_17(const raw & bits)
	: message_17(ID)
{
	if (bits.size() < SIZE_BITS_MIN || bits.size() > SIZE_BITS_MAX)
		throw std::invalid_argument{"invalid number of bits in message_17"};
	read_data(bits);
}

void message_17::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, longitude_minutes_);
	get(bits, latitude_minutes_);

	payload_ = raw{bits.begin() + SIZE_BITS_MIN, bits.end()};
}

raw message_17::get_data() const
{
	raw bits(SIZE_BITS_MIN);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, longitude_minutes_);
	set(bits, latitude_minutes_);

	bits.append(payload_);

	return bits;
}

std::optional<geo::longitude> message_17::get_lon() const
{
	if (longitude_minutes_ == longitude_not_available_short)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes_, longitude_minutes_.count, angle_scale::I1);
}

std::optional<geo::latitude> message_17::get_lat() const
{
	if (latitude_minutes_ == latitude_not_available_short)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes_, latitude_minutes_.count, angle_scale::I1);
}

void message_17::set_lon_unavailable()
{
	longitude_minutes_ = longitude_not_available_short;
}

void message_17::set_lat_unavailable()
{
	latitude_minutes_ = latitude_not_available_short;
}

void message_17::set_lon(const geo::longitude & t)
{
	longitude_minutes_ = to_longitude_minutes(t, longitude_minutes_.count, angle_scale::I1);
}

void message_17::set_lat(const geo::latitude & t)
{
	latitude_minutes_ = to_latitude_minutes(t, latitude_minutes_.count, angle_scale::I1);
}

void message_17::set_payload(const raw & p)
{
	if (p.size() > SIZE_BITS_MAX - SIZE_BITS_MIN)
		throw std::invalid_argument{"invalid size of payload"};
	payload_ = p;
}
}
