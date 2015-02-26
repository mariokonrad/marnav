#include "rmc.hpp"
#include "unique.hpp"
#include "io.hpp"
#include "time.hpp"

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
			lat_hem = NORTH;
			break;
		case latitude::hemisphere::SOUTH:
			lat_hem = SOUTH;
			break;
	}
}

void rmc::set_lon(const longitude& t)
{
	lon = t;
	switch (t.hem()) {
		case longitude::hemisphere::EAST:
			lon_hem = EAST;
			break;
		case longitude::hemisphere::WEST:
			lon_hem = WEST;
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

	std::unique_ptr<sentence> result = std::make_unique<rmc>();
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
	std::vector<std::string> v;
	v.reserve(12);
	v.push_back(to_string(time_utc));
	v.push_back(to_string(status));
	v.push_back(to_string(lat));
	v.push_back(to_string(lat_hem));
	v.push_back(to_string(lon));
	v.push_back(to_string(lon_hem));
	v.push_back(to_string(sog));
	v.push_back(to_string(heading));
	v.push_back(to_string(date));
	v.push_back(to_string(mag));
	v.push_back(to_string(mag_hem));
	v.push_back(to_string(faa_mode_indicator));
	return v;
}

}

