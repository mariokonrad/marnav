#include "message_09.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
message_09::message_09()
	: message(ID)
{
}

std::unique_ptr<message> message_09::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_09::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_09>();
	message_09 & msg = static_cast<message_09 &>(*result);

	msg.read_data(bits);

	return result;
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
	raw bits{SIZE_BITS};

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

geo::longitude message_09::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_09::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_09::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_09::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}
}
}
