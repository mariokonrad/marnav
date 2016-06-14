#include "message_19.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_19::message_19()
	: message_19(ID)
{
}

message_19::message_19(message_id id)
	: message(id)
	, shipname("@@@@@@@@@@@@@@@@@@@@")
{
}

std::unique_ptr<message> message_19::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_19::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_19>();
	message_19 & msg = static_cast<message_19 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_19::read_data(const raw & bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	// regional reserved: 38 - 45
	bits.get(sog, 46, 10);
	bits.get(position_accuracy, 56, 1);
	bits.get(longitude_minutes, 57, 28);
	bits.get(latitude_minutes, 85, 27);
	bits.get(cog, 112, 12);
	bits.get(hdg, 124, 9);
	bits.get(timestamp, 133, 6);
	// regional reserved: 139 - 142
	shipname = read_string(bits, 143, 20);
	bits.get(shiptype, 263, 8);
	bits.get(to_bow, 271, 9);
	bits.get(to_stern, 280, 9);
	bits.get(to_port, 289, 6);
	bits.get(to_starboard, 295, 6);
	bits.get(epfd_fix, 301, 4);
	bits.get(raim, 305, 1);
	bits.get(dte, 306, 1);
	bits.get(assigned, 307, 1);
	// spare: 308 - 311
}

raw message_19::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(repeat_indicator, 6, 2);
	bits.set(mmsi, 8, 30);
	bits.set(sog, 46, 10);
	bits.set(position_accuracy, 56, 1);
	bits.set(longitude_minutes, 57, 28);
	bits.set(latitude_minutes, 85, 27);
	bits.set(cog, 112, 12);
	bits.set(hdg, 124, 9);
	bits.set(timestamp, 133, 6);
	write_string(bits, 143, 20, shipname);
	bits.set(shiptype, 263, 8);
	bits.set(to_bow, 271, 9);
	bits.set(to_stern, 280, 9);
	bits.set(to_port, 289, 6);
	bits.set(to_starboard, 295, 6);
	bits.set(epfd_fix, 301, 4);
	bits.set(raim, 305, 1);
	bits.set(dte, 306, 1);
	bits.set(assigned, 307, 1);

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
