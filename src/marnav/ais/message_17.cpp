#include <marnav/ais/message_17.hpp>
#include <marnav/ais/angle.hpp>
#include <stdexcept>
#include <cmath>

namespace marnav
{
namespace ais
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
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);

	payload = raw{bits.begin() + SIZE_BITS_MIN, bits.end()};
}

raw message_17::get_data() const
{
	raw bits(SIZE_BITS_MIN);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);

	bits.append(payload);

	return bits;
}

std::optional<geo::longitude> message_17::get_lon() const
{
	if (longitude_minutes == longitude_not_available_short)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes, longitude_minutes.count, angle_scale::I1);
}

std::optional<geo::latitude> message_17::get_lat() const
{
	if (latitude_minutes == latitude_not_available_short)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes, latitude_minutes.count, angle_scale::I1);
}

void message_17::set_lon_unavailable()
{
	longitude_minutes = longitude_not_available_short;
}

void message_17::set_lat_unavailable()
{
	latitude_minutes = latitude_not_available_short;
}

void message_17::set_lon(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t, longitude_minutes.count, angle_scale::I1);
}

void message_17::set_lat(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t, latitude_minutes.count, angle_scale::I1);
}

void message_17::set_payload(const raw & p)
{
	if (p.size() > SIZE_BITS_MAX - SIZE_BITS_MIN)
		throw std::invalid_argument{"invalid size of payload"};
	payload = p;
}
}
}
