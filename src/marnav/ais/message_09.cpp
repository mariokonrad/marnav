#include <marnav/ais/message_09.hpp>
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
constexpr message_id message_09::ID;
constexpr std::size_t message_09::SIZE_BITS;

constexpr uint32_t message_09::altitude_not_available;

message_09::message_09()
	: message(ID)
{
}

message_09::message_09(const raw & bits)
	: message(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_09"};
	read_data(bits);
}

void message_09::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, altitude);
	get(bits, speed);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, course);
	get(bits, utc_second);
	get(bits, reserved);
	get(bits, dte);
	get(bits, assigned);
	get(bits, raim);
	get(bits, radio_status);
}

raw message_09::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, altitude);
	set(bits, speed);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, course);
	set(bits, utc_second);
	set(bits, reserved);
	set(bits, dte);
	set(bits, assigned);
	set(bits, raim);
	set(bits, radio_status);

	return bits;
}

utils::optional<geo::longitude> message_09::get_lon() const
{
	if (longitude_minutes == longitude_not_available)
		return utils::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes, longitude_minutes.count, angle_scale::I4);
}

utils::optional<geo::latitude> message_09::get_lat() const
{
	if (latitude_minutes == latitude_not_available)
		return utils::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes, latitude_minutes.count, angle_scale::I4);
}

void message_09::set_lon(const utils::optional<geo::longitude> & t)
{
	longitude_minutes = t
		? to_longitude_minutes(t.value(), longitude_minutes.count, angle_scale::I4)
		: longitude_not_available;
}

void message_09::set_lat(const utils::optional<geo::latitude> & t)
{
	latitude_minutes = t
		? to_latitude_minutes(t.value(), latitude_minutes.count, angle_scale::I4)
		: latitude_not_available;
}
}
}
