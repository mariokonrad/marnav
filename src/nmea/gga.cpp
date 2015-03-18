#include "gga.hpp"
#include <utils/unique.hpp>
#include "io.hpp"

namespace nmea
{

gga::gga()
	: sentence(ID, "GGA", talker_id::global_positioning_system)
{
}

void gga::set_lat(const latitude& t)
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

void gga::set_lon(const longitude& t)
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
gga::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	if (fields.size() != 14)
		throw std::invalid_argument{"invalid number of fields in gga::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gga>();
	result->set_talker(talker);
	gga& detail = static_cast<gga&>(*result);

	read(fields[0], detail.time);
	read(fields[1], detail.lat);
	read(fields[2], detail.lat_hem);
	read(fields[3], detail.lon);
	read(fields[4], detail.lon_hem);
	read(fields[5], detail.quality);
	read(fields[6], detail.n_satellites);
	read(fields[7], detail.hor_dilution);
	read(fields[8], detail.height_antenna);
	read(fields[9], detail.unit_antenna);
	read(fields[10], detail.geodial_separation);
	read(fields[11], detail.unit_geodial_separation);
	read(fields[12], detail.dgps_age);
	read(fields[13], detail.dgps_ref);

	return result;
}

std::vector<std::string> gga::get_data() const
{
	return {
		to_string(time),		 to_string(lat),				to_string(lat_hem),
		to_string(lon),			 to_string(lon_hem),			to_string(quality),
		to_string(n_satellites), to_string(hor_dilution),		to_string(height_antenna),
		to_string(unit_antenna), to_string(geodial_separation), to_string(unit_geodial_separation),
		to_string(dgps_age),	 to_string(dgps_ref),
	};
}

}

