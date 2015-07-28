#include "vtg.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vtg::TAG;

vtg::vtg()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void vtg::set_speed_kn(double t)
{
	speed_kn = t;
	speed_kn_unit = unit::velocity::KNOT;
}

void vtg::set_speed_kmh(double t)
{
	speed_kmh = t;
	speed_kmh_unit = unit::velocity::KMH;
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

std::unique_ptr<sentence> vtg::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	// before and after NMEA 2.3
	if ((fields.size() < 8) || (fields.size() > 9))
		throw std::invalid_argument{"invalid number of fields in vtg::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vtg>();
	result->set_talker(talker);
	vtg & detail = static_cast<vtg &>(*result);

	read(fields[0], detail.track_true);
	read(fields[1], detail.type_true);
	read(fields[2], detail.track_magn);
	read(fields[3], detail.type_magn);
	read(fields[4], detail.speed_kn);
	read(fields[5], detail.speed_kn_unit);
	read(fields[6], detail.speed_kmh);
	read(fields[7], detail.speed_kmh_unit);

	// NMEA 2.3 or newer
	if (fields.size() > 8)
		read(fields[8], detail.mode_indicator);

	return result;
}

std::vector<std::string> vtg::get_data() const
{
	return {to_string(track_true), to_string(type_true), to_string(track_magn),
		to_string(type_magn), to_string(speed_kn), to_string(speed_kn_unit),
		to_string(speed_kmh), to_string(speed_kmh_unit), to_string(mode_indicator)};
}
}
}
