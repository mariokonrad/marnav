#include "vtg.hpp"
#include <utils/unique.hpp>
#include "io.hpp"

namespace nmea
{

vtg::vtg()
	: sentence(ID, "VTG", talker_id::global_positioning_system)
{
}

void vtg::set_speed_kn(double t)
{
	speed_kn = t;
	unit_speed_kn = unit::KNOT;
}

void vtg::set_speed_kmh(double t)
{
	speed_kmh = t;
	unit_speed_kmh = unit::KMH;
}

void vtg::set_track_magn(double t)
{
	track_magn = t;
	type_magn = reference::MAGNETIC;
}

void vtg::set_track_true(double t)
{
	track_true = t;
	type_true = reference::TRUE;
}

std::unique_ptr<sentence>
vtg::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	// before and after NMEA 2.3
	if ((fields.size() < 8) || (fields.size() > 9))
		throw std::invalid_argument{"invalid number of fields in vtg::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vtg>();
	result->set_talker(talker);
	vtg& detail = static_cast<vtg&>(*result);

	read(fields[0], detail.track_true);
	read(fields[1], detail.type_true);
	read(fields[2], detail.track_magn);
	read(fields[3], detail.type_magn);
	read(fields[4], detail.speed_kn);
	read(fields[5], detail.unit_speed_kn);
	read(fields[6], detail.speed_kmh);
	read(fields[7], detail.unit_speed_kmh);

	// NMEA 2.3 or newer
	if (fields.size() > 8)
		read(fields[8], detail.faa_mode_indicator);

	return result;
}

std::vector<std::string> vtg::get_data() const
{
	return {to_string(track_true), to_string(type_true),	  to_string(track_magn),
			to_string(type_magn),  to_string(speed_kn),		  to_string(unit_speed_kn),
			to_string(speed_kmh),  to_string(unit_speed_kmh), to_string(faa_mode_indicator)};
}

}

