#include "message_01.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
message_01::message_01()
	: message_01(ID)
{
}

message_01::message_01(message_id id)
	: message(id)
{
}

std::unique_ptr<message> message_01::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in ais/message_01::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_01>();
	message_01 & msg = static_cast<message_01 &>(*result);

	msg.read_data(bits);

	return result;
}

geo::longitude message_01::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_01::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_01::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_01::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}

void message_01::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, nav_status);
	get(bits, rot);
	get(bits, sog);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, cog);
	get(bits, hdg);
	get(bits, timestamp);
	get(bits, maneuver_indicator);
	get(bits, raim);
	get(bits, radio_status);
}

raw message_01::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, nav_status);
	set(bits, rot);
	set(bits, sog);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, cog);
	set(bits, hdg);
	set(bits, timestamp);
	set(bits, maneuver_indicator);
	set(bits, raim);
	set(bits, radio_status);

	return bits;
}
}
}
