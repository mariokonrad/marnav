#include "message_18.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_18::message_18()
	: message_18(ID)
{
}

message_18::message_18(message_id id)
	: message(id)
	, repeat_indicator(0)
	, mmsi(0)
	, sog(0)
	, position_accuracy(false)
	, longitude_minutes(longitude_not_available)
	, latitude_minutes(latitude_not_available)
	, cog(cog_not_available)
	, hdg(hdg_not_available)
	, timestamp(timestamp_not_available)
	, cs_unit(false)
	, display_flag(false)
	, dsc_flag(false)
	, band_flag(false)
	, message_22_flag(false)
	, assigned(false)
	, raim(0)
	, radio_status(0)
{
}

std::unique_ptr<message> message_18::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_18::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_18>();
	message_18 & msg = static_cast<message_18 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_18::read_data(const raw & bits)
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
	// regional reserved: 139 - 140
	bits.get(cs_unit, 141, 1);
	bits.get(display_flag, 142, 1);
	bits.get(dsc_flag, 143, 1);
	bits.get(band_flag, 144, 1);
	bits.get(message_22_flag, 145, 1);
	bits.get(assigned, 146, 1);
	bits.get(raim, 147, 1);
	bits.get(radio_status, 148, 20);
}

geo::longitude message_18::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_18::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_18::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_18::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}

raw message_18::get_data() const
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
	bits.set(cs_unit, 141, 1);
	bits.set(display_flag, 142, 1);
	bits.set(dsc_flag, 143, 1);
	bits.set(band_flag, 144, 1);
	bits.set(message_22_flag, 145, 1);
	bits.set(assigned, 146, 1);
	bits.set(raim, 147, 1);
	bits.set(radio_status, 148, 20);

	return bits;
}
}
}
