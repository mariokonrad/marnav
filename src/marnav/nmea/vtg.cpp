#include "vtg.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vtg::TAG;

vtg::vtg()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

vtg::vtg(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 8) || (size > 9))
		throw std::invalid_argument{"invalid number of fields in vtg"};

	read(*(first + 0), track_true);
	read(*(first + 1), type_true);
	read(*(first + 2), track_magn);
	read(*(first + 3), type_magn);
	read(*(first + 4), speed_kn);
	read(*(first + 5), speed_kn_unit);
	read(*(first + 6), speed_kmh);
	read(*(first + 7), speed_kmh_unit);

	// NMEA 2.3 or newer
	if (size > 8)
		read(*(first + 8), mode_indicator);
}

void vtg::set_speed_kn(double t) noexcept
{
	speed_kn = t;
	speed_kn_unit = unit::velocity::knot;
}

void vtg::set_speed_kmh(double t) noexcept
{
	speed_kmh = t;
	speed_kmh_unit = unit::velocity::kmh;
}

void vtg::set_track_magn(double t) noexcept
{
	track_magn = t;
	type_magn = reference::MAGNETIC;
}

void vtg::set_track_true(double t) noexcept
{
	track_true = t;
	type_true = reference::TRUE;
}

std::unique_ptr<sentence> vtg::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<vtg>(new vtg(talker, first, last));
}

std::vector<std::string> vtg::get_data() const
{
	return {to_string(track_true), to_string(type_true), to_string(track_magn),
		to_string(type_magn), to_string(speed_kn), to_string(speed_kn_unit),
		to_string(speed_kmh), to_string(speed_kmh_unit), to_string(mode_indicator)};
}
}
}
