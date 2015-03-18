#include "rmc.hpp"
#include <utils/unique.hpp>
#include "io.hpp"

namespace nmea
{

rmc::rmc()
	: sentence(ID, "RMC", talker_id::global_positioning_system)
{
}

void rmc::set_lat(const latitude& t)
{
	lat = t;
	switch (t.hem()) {
		case latitude::hemisphere::NORTH:
			lat_hem = direction::NORTH;
			break;
		case latitude::hemisphere::SOUTH:
			lat_hem = direction::SOUTH;
			break;
	}
}

void rmc::set_lon(const longitude& t)
{
	lon = t;
	switch (t.hem()) {
		case longitude::hemisphere::EAST:
			lon_hem = direction::EAST;
			break;
		case longitude::hemisphere::WEST:
			lon_hem = direction::WEST;
			break;
	}
}

std::unique_ptr<sentence>
rmc::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	// before and after NMEA 2.3
	if ((fields.size() < 11) || (fields.size() > 12))
		throw std::invalid_argument{"invalid number of fields in rmc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rmc>();
	result->set_talker(talker);
	rmc& detail = static_cast<rmc&>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.status);
	read(fields[2], detail.lat);
	read(fields[3], detail.lat_hem);
	read(fields[4], detail.lon);
	read(fields[5], detail.lon_hem);
	read(fields[6], detail.sog);
	read(fields[7], detail.heading);
	read(fields[8], detail.date);
	read(fields[9], detail.mag);
	read(fields[10], detail.mag_hem);

	// NMEA 2.3 or newer
	if (fields.size() > 11)
		read(fields[11], detail.faa_mode_indicator);

	return result;
}

std::vector<std::string> rmc::get_data() const
{
	return {
		to_string(time_utc), to_string(status),  to_string(lat),	 to_string(lat_hem),
		to_string(lon),		 to_string(lon_hem), to_string(sog),	 to_string(heading),
		to_string(date),	 to_string(mag),	 to_string(mag_hem), to_string(faa_mode_indicator),
	};
}

}

