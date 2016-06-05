#include "mwd.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(mwd)

constexpr const char * mwd::TAG;

mwd::mwd()
	: sentence(ID, TAG, talker_id::weather_instruments)
{
}

mwd::mwd(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in mwd"};

	read(*(first + 0), direction_true);
	read(*(first + 1), direction_true_ref);
	read(*(first + 2), direction_mag);
	read(*(first + 3), direction_mag_ref);
	read(*(first + 4), speed_kn);
	read(*(first + 5), speed_kn_unit);
	read(*(first + 6), speed_ms);
	read(*(first + 7), speed_ms_unit);
}

void mwd::set_direction_true(double t) noexcept
{
	direction_true = t;
	direction_true_ref = reference::TRUE;
}

void mwd::set_direction_mag(double t) noexcept
{
	direction_mag = t;
	direction_mag_ref = reference::MAGNETIC;
}

void mwd::set_speed_knots(double t) noexcept
{
	speed_kn = t;
	speed_kn_unit = unit::velocity::knot;
}

void mwd::set_speed_mps(double t) noexcept
{
	speed_ms = t;
	speed_ms_unit = unit::velocity::mps;
}

std::vector<std::string> mwd::get_data() const
{
	return {format(direction_true, 1), to_string(direction_true_ref), format(direction_mag, 1),
		to_string(direction_mag_ref), format(speed_kn, 1), to_string(speed_kn_unit),
		format(speed_ms, 1), to_string(speed_ms_unit)};
}
}
}
