#include "message_04.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

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

std::unique_ptr<message> message_04::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_04::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_04>();
	message_04 & msg = static_cast<message_04 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_04::read_data(const raw & bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	bits.get(year, 38, 14);
	bits.get(month, 52, 4);
	bits.get(day, 56, 5);
	bits.get(hour, 61, 5);
	bits.get(minute, 66, 6);
	bits.get(second, 72, 6);
	bits.get(position_accuracy, 78, 1);
	bits.get(longitude_minutes, 79, 28);
	bits.get(latitude_minutes, 107, 27);
	bits.get(epfd_fix, 134, 4);
	// spare 138..147
	bits.get(raim, 148, 1);
	bits.get(radio_status, 149, 19);
}

raw message_04::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(repeat_indicator, 6, 2);
	bits.set(mmsi, 8, 30);
	bits.set(year, 38, 14);
	bits.set(month, 52, 4);
	bits.set(day, 56, 5);
	bits.set(hour, 61, 5);
	bits.set(minute, 66, 6);
	bits.set(second, 72, 6);
	bits.set(position_accuracy, 78, 1);
	bits.set(longitude_minutes, 79, 28);
	bits.set(latitude_minutes, 107, 27);
	bits.set(epfd_fix, 134, 4);
	bits.set(raim, 148, 1);
	bits.set(radio_status, 149, 19);

	return bits;
}

geo::longitude message_04::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_04::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_04::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_04::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}
}
}
