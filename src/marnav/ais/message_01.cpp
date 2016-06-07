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

void message_01::read_data(const raw & bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	bits.get(nav_status, 38, 4);
	bits.get(rot, 42, 8);
	bits.get(sog, 50, 10);
	bits.get(position_accuracy, 60, 1);
	bits.get(longitude_minutes, 61, 28);
	bits.get(latitude_minutes, 89, 27);
	bits.get(cog, 116, 12);
	bits.get(hdg, 128, 9);
	bits.get(timestamp, 136, 6);
	bits.get(maneuver_indicator, 143, 2);
	// spare: 145 - 147
	bits.get(raim, 148, 1);
	bits.get(radio_status, 149, 19);
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

raw message_01::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(repeat_indicator, 6, 2);
	bits.set(mmsi, 8, 30);
	bits.set(nav_status, 38, 4);
	bits.set(rot, 42, 8);
	bits.set(sog, 50, 10);
	bits.set(position_accuracy, 60, 1);
	bits.set(longitude_minutes, 61, 28);
	bits.set(latitude_minutes, 89, 27);
	bits.set(cog, 116, 12);
	bits.set(hdg, 128, 9);
	bits.set(timestamp, 136, 6);
	bits.set(maneuver_indicator, 143, 2);
	bits.set(raim, 148, 1);
	bits.set(radio_status, 149, 19);

	return bits;
}
}
}
