#include "message_04.hpp"
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
message_04::message_04()
	: message_04(ID)
{
}

message_04::message_04(message_id id)
	: message(id)
{
}

message_04::message_04(const raw & bits)
	: message_04(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_04"};
	read_data(bits);
}

void message_04::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, year);
	get(bits, month);
	get(bits, day);
	get(bits, hour);
	get(bits, minute);
	get(bits, second);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, epfd_fix);
	get(bits, raim);
	get(bits, radio_status);
}

raw message_04::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, year);
	set(bits, month);
	set(bits, day);
	set(bits, hour);
	set(bits, minute);
	set(bits, second);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, epfd_fix);
	set(bits, raim);
	set(bits, radio_status);

	return bits;
}

utils::optional<geo::longitude> message_04::get_longitude() const
{
	if (longitude_minutes == longitude_not_available)
		return utils::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes, longitude_minutes.count, angle_scale::I4);
}

utils::optional<geo::latitude> message_04::get_latitude() const
{
	if (latitude_minutes == latitude_not_available)
		return utils::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes, latitude_minutes.count, angle_scale::I4);
}

void message_04::set_longitude(const utils::optional<geo::longitude> & t)
{
	longitude_minutes = t
		? to_longitude_minutes(t.value(), longitude_minutes.count, angle_scale::I4)
		: longitude_not_available;
}

void message_04::set_latitude(const utils::optional<geo::latitude> & t)
{
	latitude_minutes = t
		? to_latitude_minutes(t.value(), latitude_minutes.count, angle_scale::I4)
		: latitude_not_available;
}
}
}
