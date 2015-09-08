#include "message_09.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_09::message_09()
	: message(ID)
	, repeat_indicator(0)
	, mmsi(0)
	, altitude(altitude_not_available)
	, speed(speed_not_available)
	, position_accuracy(false)
	, longitude_minutes(longitude_not_available)
	, latitude_minutes(latitude_not_available)
	, course(0)
	, utc_second(second_not_available)
	, reserved(0)
	, dte(false)
	, assigned(false)
	, raim(0)
	, radio_status(0)
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
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	bits.get(altitude, 38, 12);
	bits.get(speed, 50, 10);
	bits.get(position_accuracy, 60, 1);
	bits.get(longitude_minutes, 61, 28);
	bits.get(latitude_minutes, 89, 27);
	bits.get(course, 116, 12);
	bits.get(utc_second, 128, 6);
	bits.get(reserved, 134, 8);
	bits.get(dte, 142, 1);
	// spare 143 - 145
	bits.get(assigned, 146, 1);
	bits.get(raim, 147, 1);
	bits.get(radio_status, 148, 20);
}

raw message_09::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(mmsi, 8, 30);
	bits.set(altitude, 38, 12);
	bits.set(speed, 50, 10);
	bits.set(position_accuracy, 60, 1);
	bits.set(longitude_minutes, 61, 28);
	bits.set(latitude_minutes, 89, 27);
	bits.set(course, 116, 12);
	bits.set(utc_second, 128, 6);
	bits.set(reserved, 134, 8);
	bits.set(dte, 142, 1);
	bits.set(assigned, 146, 1);
	bits.set(raim, 147, 1);
	bits.set(radio_status, 148, 20);

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
