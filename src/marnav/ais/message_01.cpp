#include "message_01.hpp"
#include <cmath>
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
	, repeat_indicator(0)
	, mmsi(0)
	, nav_status(navigation_status::not_defined)
	, rot(-128)
	, sog(0)
	, position_accuracy(false)
	, longitude_minutes(longitude_not_available)
	, latitude_minutes(latitude_not_available)
	, cog(cog_not_available)
	, hdg(hdg_not_available)
	, timestamp(timestamp_not_available)
	, maneuver_indicator(maneuver_indictor_not_available)
	, raim(0)
	, radio_status(0)
{
}

std::unique_ptr<message> message_01::parse(const raw & bits) throw(
	std::invalid_argument, std::out_of_range)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in ais/message_01::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_01>();
	message_01 & msg = static_cast<message_01 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_01::read_data(const raw & bits) throw(std::out_of_range)
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

geo::longitude message_01::get_longitude() const
{
	return geo::longitude{(0.0001 * longitude_minutes) / 60.0};
}

geo::latitude message_01::get_latitude() const
{
	return geo::latitude{(0.0001 * latitude_minutes) / 60.0};
}

void message_01::set_longitude(const geo::longitude & t)
{
	longitude_minutes = floor(60000.0 * t);
}

void message_01::set_latitude(const geo::latitude & t)
{
	latitude_minutes = floor(60000.0 * t);
}

raw message_01::get_data() const throw(std::out_of_range)
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
