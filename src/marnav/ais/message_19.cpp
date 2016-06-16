#include "message_19.hpp"
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DEFINE_MESSAGE_PARSE_FUNC(message_19)

message_19::message_19()
	: message_19(ID)
{
}

message_19::message_19(message_id id)
	: message(id)
	, shipname("@@@@@@@@@@@@@@@@@@@@")
{
}

message_19::message_19(const raw & bits)
	: message_19(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_19"};
	read_data(bits);
}

void message_19::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, sog);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, cog);
	get(bits, hdg);
	get(bits, timestamp);
	get(bits, shipname);
	get(bits, shiptype);
	get(bits, to_bow);
	get(bits, to_stern);
	get(bits, to_port);
	get(bits, to_starboard);
	get(bits, epfd_fix);
	get(bits, raim);
	get(bits, dte);
	get(bits, assigned);
}

raw message_19::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, sog);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, cog);
	set(bits, hdg);
	set(bits, timestamp);
	set(bits, shipname);
	set(bits, shiptype);
	set(bits, to_bow);
	set(bits, to_stern);
	set(bits, to_port);
	set(bits, to_starboard);
	set(bits, epfd_fix);
	set(bits, raim);
	set(bits, dte);
	set(bits, assigned);

	return bits;
}

geo::longitude message_19::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_19::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_19::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_19::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}
}
}
