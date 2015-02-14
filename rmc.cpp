#include "rmc.hpp"
#include "unique.hpp"

namespace nmea
{

rmc::rmc()
	: sentence(ID, "RMC", "GP")
{
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

void rmc::append_data(std::ostream& os, const std::string& delimiter) const
{
	os << delimiter;
	os << time_utc;
	os << delimiter;
	os << status;
	os << delimiter;
	os << lat;
	os << delimiter;
	os << lat_hem;
	os << delimiter;
	os << lon;
	os << delimiter;
	os << lon_hem;
	os << delimiter;
	os << sog;
	os << delimiter;
	os << heading;
	os << delimiter;
	os << date;
	os << delimiter;
	os << mag;
	os << delimiter;
	os << mag_hem;
	os << delimiter;
	os << faa_mode_indicator;
}

}

